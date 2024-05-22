
#include "hac.h"
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include <iostream>
#include <fstream>


template <size_t N>
ap_uint<LOG_FUNCTION(N)> popcount(ap_uint<N> input) {
    #pragma HLS INLINE OFF
    ap_uint<LOG_FUNCTION(N)> count = 0;
    popcount_loop: for (int i = 0; i < N; i++) {
        #pragma HLS UNROLL
        count += input[i];
    }
    return count;
}

int index(int i, int j) {
    #pragma HLS INLINE
    if (i < j)
    std::swap(i, j);
    return i * (i + 1) / 2 + j;
}


void calculate_distance_matrix_kernel(
bitset_dhv encoded_spectra[MAX_NUM_SPECTRA],
int num_spectra,
distance_t max_cluster_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2],
distance_t original_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2],

int *dist_lt_thres_cnt
) {

    int dist_lt_thres_cnt_tmp = 0;


    calculate_distance: for (int i = 0; i < MAX_NUM_SPECTRA; i++) {
        if (i < num_spectra){

            inner_distance: for (int j = 0; j < i; j++) {
                #pragma HLS loop_tripcount min=1 max=300 avg=150
                #pragma HLS PIPELINE II=1
                bitset_dhv xor_result = encoded_spectra[i] ^ encoded_spectra[j];
                distance_t popcount_result = popcount<Dhv>(xor_result);
                auto idx = index(i, j);
                max_cluster_distances[idx] = popcount_result;
                original_distances[idx] = popcount_result;

                dist_lt_thres_cnt_tmp += (popcount_result <= DISTANCE_THRESHOLD);
            }
        }
    }

    *dist_lt_thres_cnt = dist_lt_thres_cnt_tmp;

}



void update_max_cluster_distances(
distance_t max_cluster_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2],
int i,
int j,
int num_spectra,

int *dist_lt_thres_cnt
) {
    #pragma HLS INLINE

    update_loop: for (int k = 0; k < MAX_NUM_SPECTRA; k++) {
        #pragma HLS DEPENDENCE variable=max_cluster_distances inter false
        #pragma HLS PIPELINE 
        if (k != j && k !=i && k < num_spectra) {
            auto idx_ik = index(i, k);
            auto idx_jk = index(j, k);

            auto vi = max_cluster_distances[idx_ik];
            auto vj = max_cluster_distances[idx_jk];
            auto max_v = (vi > vj) ? vi : vj;
            max_cluster_distances[idx_ik] = max_v;

            *dist_lt_thres_cnt -= (vj > DISTANCE_THRESHOLD && vi <= DISTANCE_THRESHOLD);
        }
    }
}


void agglomerative_ccl_kernel(
distance_t max_cluster_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2],
int num_spectra,
int valid_clusters[MAX_NUM_SPECTRA],
int* num_valid_clusters_ptr,

Cluster thres_clusters[MAX_NUM_SPECTRA],
int valid_dist_cnt
){


    int valid_total_clusters[MAX_NUM_SPECTRA];


    int num_valid_clusters_thres = *num_valid_clusters_ptr;

    int stack[MAX_NUM_SPECTRA];
    int stack_ptr = 0;

    initialize_clusters: for (int i = 0; i < MAX_NUM_SPECTRA; i++) {
        #pragma HLS UNROLL
        valid_clusters[i] = i;
        valid_total_clusters[i]=i;
        thres_clusters[i].num_elements = 1;
        thres_clusters[i].next = -1;
        thres_clusters[i].end = i;
        thres_clusters[i].check_cluster = 0;

    }

    main_while_loop: for (int num_valid_clusters = *num_valid_clusters_ptr; num_valid_clusters > 1 && valid_dist_cnt > 0; num_valid_clusters--) {
        #pragma HLS loop_tripcount min=300 max=300
        std::pair<int, int> closest_clusters;
        #pragma HLS ARRAY_PARTITION variable=valid_total_clusters complete
        bool merged = false;

        merged_while : while (merged == false) {
            #pragma HLS loop_tripcount min=8 max=8

            if (stack_ptr == 0) {
                stack[stack_ptr++] = 0;
            }

            distance_t min_distance = distance_t(0.95*Dhv);
            int i = stack[stack_ptr - 1];
            int j = -1;

            min_row : for (int k = 0; k < num_valid_clusters; ++k) {
                #pragma HLS loop_tripcount min=150 max=150
                #pragma HLS pipeline II=1
                #pragma HLS  UNROLL FACTOR=2
                if (k != i && (max_cluster_distances[index(valid_total_clusters[i], valid_total_clusters[k])] <= min_distance)) {
                    min_distance = max_cluster_distances[index(valid_total_clusters[i], valid_total_clusters[k])];
                    j = k;

                }
            }


            bool in_stack = false;
            if (stack[stack_ptr - 2] == j) { // Found the local minimum
                in_stack = true;

            }


            if (in_stack ) {

                if (j<i){

                    closest_clusters.second = i;
                    closest_clusters.first = j;
                } else {
                    closest_clusters.second = j;
                    closest_clusters.first = i;
                }


                int ci = valid_total_clusters[closest_clusters.first];
                int cj = valid_total_clusters[closest_clusters.second];

                update_max_cluster_distances(max_cluster_distances, ci, cj, num_spectra, &valid_dist_cnt);

                if(min_distance <= DISTANCE_THRESHOLD && closest_clusters.second < num_valid_clusters)
                {

                    int  correction_factor = thres_clusters[closest_clusters.second].check_cluster;
                    int  correction_factor2 = thres_clusters[closest_clusters.second].check_cluster;
                    int  correction_factor1 = thres_clusters[closest_clusters.first].check_cluster;

                    int ti = valid_clusters[closest_clusters.first + correction_factor1] ;
                    int tj = valid_clusters[closest_clusters.second + correction_factor2] ;

                    int thres_old_num_elements_i = thres_clusters[ti].num_elements;
                    int thres_old_num_elements_j = thres_clusters[tj].num_elements;

                    int ti_end = thres_clusters[ti].end;
                    thres_clusters[ti_end].next = tj;
                    thres_clusters[ti].end = thres_clusters[tj].end;


                    thres_clusters[ti].num_elements = thres_old_num_elements_i + thres_old_num_elements_j;
 
                    valid_clusters_shift_thres: for (int k = closest_clusters.second + correction_factor; k < num_valid_clusters_thres-1; k++) {
                        #pragma HLS loop_tripcount min=75 max=75
                        #pragma HLS PIPELINE II=1
                        valid_clusters[k] = valid_clusters[k + 1];
                    }

                    update_loop1: for (int k = closest_clusters.second; k < num_valid_clusters_thres-1; k++) {
                        #pragma HLS loop_tripcount min=75 max=75
                        #pragma HLS PIPELINE II=1
                        thres_clusters[k].check_cluster = thres_clusters[k+1].check_cluster;
                    }

                    num_valid_clusters_thres --;

                } else{


                    update_loop: for (int k = closest_clusters.second; k < num_valid_clusters_thres-1; k++) {
                        #pragma HLS loop_tripcount min=75 max=75
                        #pragma HLS PIPELINE II=1
                        thres_clusters[k].check_cluster = thres_clusters[k+1].check_cluster +1;
                    }

                }

                stack_ptr--;
                stack_ptr--;
                merged = true;


            } else {
                stack[stack_ptr++] = j;

            }
        }

        valid_clusters_shift: for (int k = closest_clusters.second; k < num_valid_clusters-1; k++) {
            #pragma HLS loop_tripcount min=75 max=75
            #pragma HLS PIPELINE II=1
            valid_total_clusters[k] = valid_total_clusters[k + 1];
        }


    }

    *num_valid_clusters_ptr = num_valid_clusters_thres;


}

template<bool AccDistanceLessThanThreshold_V>
void calculate_consensus(
distance_t original_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2],
Cluster clusters[MAX_NUM_SPECTRA],
int valid_clusters[MAX_NUM_SPECTRA],
int consensus[MAX_NUM_SPECTRA],
int num_valid_clusters
) {

    using sum_distance_t = std::conditional_t<AccDistanceLessThanThreshold_V, acc_thres_distance_t, acc_distance_t>;

    calculate_consensus_outer: for(int i = 0; i < num_valid_clusters; i++) {
        #pragma HLS loop_tripcount min=30 max=30
        int cluster_idx = valid_clusters[i];
        int num_elements = clusters[cluster_idx].num_elements;

        int elements_tmp[MAX_NUM_SPECTRA];

        #pragma HLS ARRAY_PARTITION variable=elements_tmp
        int iter_element = cluster_idx;
        for (int j = 0; j < num_elements; j++){
            #pragma HLS loop_tripcount min=7 max=7
            #pragma HLS pipeline
            elements_tmp[j] = iter_element;
            iter_element = clusters[iter_element].next;
        }

        if(num_elements == 1) {
            consensus[i] = elements_tmp[0];
        } else {
            sum_distance_t min_sum_distance = distance_t(0.95 * Dhv) * (num_elements - 1);

            calculate_consensus_inner: for(int j = 0; j < num_elements; j++) {
                #pragma HLS loop_tripcount min=7 max=7
                #pragma HLS pipeline
                sum_distance_t sum_distance = 0;
                calculate_sum_distance: for(int k = 0; k < num_elements; k++) { // * Only check k>j
                    #pragma HLS loop_tripcount min=7 max=7
                    #pragma HLS pipeline
                    if(j != k) {
                        sum_distance += original_distances[index(elements_tmp[j], elements_tmp[k])];
                    }
                }
                if (sum_distance < min_sum_distance) {
                    min_sum_distance = sum_distance;
                    consensus[i] = elements_tmp[j];
                }
            }
        }
    }
}

void hd_encoding(
    bitset_dhv ID[f],
    bitset_dhv Level[Q],
    PeakBuffer &peak_buffer,
    int peak_count,
    bitset_dhv *encoded_spectra
) {
    bitset_dhv xor_results[MAX_PEAKS];
    #pragma HLS BIND_STORAGE variable=ID type=RAM_1P impl=uram

    peak_cnt_t sum[Dhv];

    #pragma HLS ARRAY_PARTITION variable=sum 

    loop_init: for (int j=0; j<Dhv; j++){
        #pragma HLS UNROLL
        sum[j] = 0;
    }

    loop_read_and_calc: for (int i = 0; i < peak_count; i++) {
    #pragma HLS loop_tripcount min=10 max=25
	#pragma HLS PIPELINE II=1
        auto mz_indices_tmp = peak_buffer.mz[i];
        auto intensity_indices_tmp = peak_buffer.intensity[i];
        xor_results[i] = ID[mz_indices_tmp] ^ Level[intensity_indices_tmp];
    }

    bitset_dhv majority;

    loop_summation: for (int i = 0; i < peak_count; i++) {
    #pragma HLS loop_tripcount min=10 max=25
    #pragma HLS PIPELINE II=1
        for (int j = 0; j < Dhv; j++) {
            #pragma HLS UNROLL
            sum[j] += xor_results[i][j];
        }
    }

    peak_cnt_t half_peak_count_tmp = peak_count / 2;

    loop_majority_compute: for (int j=0; j<Dhv; j++){
        #pragma HLS UNROLL
        majority[j] = (sum[j] > half_peak_count_tmp) ? 1 : 0;
    }

    *encoded_spectra = majority;
}



void encoding_work_func(
    bitset_dhv ID_local[f], 
    bitset_dhv Level_local[Q],
    ap_uint<PEAK_PORT_W> *peak_mz_buffer,
    ap_uint<PEAK_PORT_W> *peak_intensity_buffer,
    int *peak_count_buffer,
    int *num_spectra_buffer,
    // bitset_dhv *encoded_spectra_hbm,
    hls::stream<EncodedBuffer> encoded_spectra_stream[N_CLUSTERING],

    int batch_size

){
    #pragma HLS dataflow

    hls::stream<PeakBuffer> local_peak_stream;
    hls::stream<peak_cnt_t> peak_count;
    hls::stream<bitset_dhv> encoded_spectra;
    hls::stream<int> num_spectra_stream;
    hls::stream<int> num_spectra_stream_c1;

    #pragma HLS STREAM variable=local_peak_stream depth=16 type=fifo
    #pragma HLS STREAM variable=peak_count depth=16 type=fifo
    #pragma HLS STREAM variable=encoded_spectra depth=16 type=fifo
    #pragma HLS STREAM variable=num_spectra_stream depth=16 type=fifo
    #pragma HLS STREAM variable=num_spectra_stream_c1 depth=16 type=fifo



    loop_stream_in: for (int ib = 0; ib < batch_size*MAX_NUM_SPECTRA; ib++) {
        #pragma HLS loop_tripcount min=300000 max=300000
        // #pragma HLS pipeline
        PeakBuffer local_peak;
        #pragma HLS aggregate variable=local_peak
        for (int j = 0; j < PEAK_LOOP_CNT; j++) {
            auto tmp_mz = peak_mz_buffer[ib * PEAK_LOOP_CNT + j];
            auto tmp_intensity = peak_intensity_buffer[ib * PEAK_LOOP_CNT + j];
            for (int k = 0; k < PEAK_PORT_W/32; k++){
                #pragma HLS UNROLL
                local_peak.mz[j*32 + k] = tmp_mz.range(k*32+31, k*32);
                local_peak.intensity[j*32 + k] = tmp_intensity.range(k*32+31, k*32);
            }
            if (j == PEAK_LOOP_CNT-1){ //last iter
                local_peak_stream << local_peak;
            }
        }
    }


    
    loop_stream_pc_in: for (int ib = 0; ib < batch_size*MAX_NUM_SPECTRA; ib++) {
        #pragma HLS loop_tripcount min=300000 max=300000
        peak_count << peak_count_buffer[ib];
    }


    loop_workload: for (int b = 0; b < batch_size; b++) {
        #pragma HLS loop_tripcount min=1000 max=1000
        #pragma HLS pipeline
        int num_spectra_tmp = num_spectra_stream.read();
        num_spectra_stream_c1 << num_spectra_tmp;
        loop_workload_inner:for (int i = 0; i < MAX_NUM_SPECTRA; i++){
            #pragma HLS loop_flatten off
            PeakBuffer local_peak;
            #pragma HLS aggregate variable=local_peak
            local_peak_stream >> local_peak;

            peak_cnt_t  local_peak_count;
            bitset_dhv  local_encoded_spectra;
            peak_count >> local_peak_count;
            local_peak_count = (i < num_spectra_tmp) ? local_peak_count : peak_cnt_t(0);
            hd_encoding(ID_local, Level_local, local_peak, local_peak_count, &local_encoded_spectra);
            encoded_spectra << local_encoded_spectra;
        }
    }

    loop_stream_num_in: for(int b=0; b < batch_size; b++){
        #pragma HLS loop_tripcount min=1000 max=1000
        #pragma HLS pipeline
        num_spectra_stream << num_spectra_buffer[b];
    }

    loop_stream_out: for (int b = 0; b < batch_size; b++) {
        #pragma HLS loop_tripcount min=1000 max=1000
        bitset_dhv local_encoded_buffer;

        int n = b % N_CLUSTERING;
        int num_spectra_tmp;
        num_spectra_stream_c1 >> num_spectra_tmp;
        encoded_spectra_stream[n] << bitset_dhv(num_spectra_tmp);
        loop_stream_out_buffer:for (int s=0; s < MAX_NUM_SPECTRA; s++){
            #pragma HLS pipeline
            encoded_spectra >> local_encoded_buffer;
            if (s < num_spectra_tmp){
                encoded_spectra_stream[n] << local_encoded_buffer;
            }
        }

    }
}


void encoding_kernel(
    bitset_dhv *ID_Level_buffer,
    ap_uint<PEAK_PORT_W> *peak_mz_buffer,
    ap_uint<PEAK_PORT_W> *peak_intensity_buffer,
    int *peak_count_buffer,
    int *num_spectra_buffer,
    // bitset_dhv *encoded_spectra_hbm,
    hls::stream<EncodedBuffer> encoded_spectra_stream[N_CLUSTERING],
    int  batch_size
) {
    // // #pragma HLS INTERFACE m_axi port=encoded_spectra_hbm    offset=slave bundle=gmem     num_read_outstanding=1  max_read_burst_length=2
    // #pragma HLS INTERFACE m_axi port=ID_Level_buffer        offset=slave bundle=gmem0    num_write_outstanding=1 max_write_burst_length=2
    // #pragma HLS INTERFACE m_axi port=peak_mz_buffer         offset=slave bundle=gmem2    num_write_outstanding=1 max_write_burst_length=2
    // #pragma HLS INTERFACE m_axi port=peak_intensity_buffer  offset=slave bundle=gmem3    num_write_outstanding=1 max_write_burst_length=2
    // #pragma HLS INTERFACE m_axi port=peak_count_buffer      offset=slave bundle=gmem4    num_write_outstanding=1 max_write_burst_length=2
    // #pragma HLS INTERFACE m_axi port=num_spectra_buffer     offset=slave bundle=gmem5    num_write_outstanding=1 max_write_burst_length=2

    bitset_dhv ID_local[f], Level_local[Q];
    #pragma HLS BIND_STORAGE variable=ID_local type=RAM_1P impl=uram


    for(int j=0; j<f; ++j){
        ID_local[j] = ID_Level_buffer[j];
    }
    for(int j=0; j<Q; ++j){
        Level_local[j] = ID_Level_buffer[j+f];
    }

    encoding_work_func(ID_local, Level_local, peak_mz_buffer, peak_intensity_buffer, peak_count_buffer, num_spectra_buffer, encoded_spectra_stream, batch_size);

}


/*
extern "C" void clustering_kernel(
bitset_dhv *encoded_spectra_buffer,
int num_spectra,
int valid_clusters[MAX_NUM_SPECTRA],
int *num_valid_clusters,
int elements[MAX_NUM_SPECTRA * CLUSTER_SIZE],
int *num_elements,
int consensus[MAX_NUM_SPECTRA],
int *num_consensus
) {

    #pragma HLS INTERFACE m_axi port=valid_clusters   offset=slave bundle=gmem10   
    #pragma HLS INTERFACE m_axi port=elements         offset=slave bundle=gmem11    num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=consensus        offset=slave bundle=gmem12    num_read_outstanding=1 max_read_burst_length=2

    distance_t max_cluster_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2];
    distance_t original_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2];

    #pragma HLS BIND_STORAGE variable=original_distances type=ram_2p impl=uram
    #pragma HLS BIND_STORAGE variable=max_cluster_distances type=ram_2p impl=uram


    int         local_num_valid_clusters;
    int         local_consensus         [MAX_NUM_SPECTRA]; 
    int         local_valid_clusters    [MAX_NUM_SPECTRA]; 
    bitset_dhv  local_encoded_spectra   [MAX_NUM_SPECTRA];

    Cluster thres_clusters[MAX_NUM_SPECTRA];

    loop_stream_in: for (int i = 0; i < num_spectra; i++) {
        #pragma HLS loop_tripcount min=300 max=300
        #pragma HLS pipeline
        #pragma HLS UNROLL FACTOR=2 skip_exit_check
        local_valid_clusters [i] = valid_clusters[i];
        local_encoded_spectra[i] = encoded_spectra_buffer[i];
        
    }
    local_num_valid_clusters = *num_valid_clusters;


    int valid_dist_cnt;
    calculate_distance_matrix_kernel(local_encoded_spectra, num_spectra, max_cluster_distances, original_distances, &valid_dist_cnt);

    agglomerative_ccl_kernel(max_cluster_distances, num_spectra, local_valid_clusters, &local_num_valid_clusters, thres_clusters, valid_dist_cnt);

    calculate_consensus<true>(original_distances, thres_clusters, local_valid_clusters, local_consensus, local_num_valid_clusters);

    *num_consensus = num_spectra;
    *num_valid_clusters = local_num_valid_clusters;

    copy_cluster_elements: for (int i = 0; i < local_num_valid_clusters; i++) {
        #pragma HLS loop_tripcount min=30 max=30
        #pragma HLS pipeline
        #pragma HLS UNROLL FACTOR=2 skip_exit_check

        int cluster_idx = local_valid_clusters[i];
        num_elements[i] = thres_clusters[cluster_idx].num_elements;
        valid_clusters[i] = local_valid_clusters[i];
        consensus[i] = local_consensus[i];
        
    }


    int element_copy_cnt = 0;
    copy_cluster_elements_inner: for (int i = 0; i < local_num_valid_clusters; i++) {
        #pragma HLS loop_tripcount min=30 max=30
        int cluster_idx = local_valid_clusters[i];
        int num_elements = thres_clusters[cluster_idx].num_elements;
        int iter_element = cluster_idx;
        for (int j = 0; j < num_elements; j++) {
            #pragma HLS loop_tripcount min=4 max=20
            #pragma HLS pipeline
                elements[i * CLUSTER_SIZE + j] = iter_element;
                iter_element = thres_clusters[iter_element].next;
            }
    }

}
*/

void clustering_kernel(
// bitset_dhv *encoded_spectra_buffer,
hls::stream<EncodedBuffer> &encoded_spectra_stream,
// int num_spectra,
int *num_valid_clusters, // 1
int *elements, //[MAX_NUM_SPECTRA * CLUSTER_SIZE],
int *num_elements, // [CLUSTER_SIZE]
int *consensus, //[CLUSTER_SIZE],
int batch_size
) {

    // #pragma HLS INTERFACE m_axi port=num_valid_clusters offset=slave bundle=gmem_num   num_read_outstanding=1 max_read_burst_length=2
    // #pragma HLS INTERFACE m_axi port=num_elements       offset=slave bundle=gmem_num   num_read_outstanding=1 max_read_burst_length=2
    // #pragma HLS INTERFACE m_axi port=consensus          offset=slave bundle=gmem_num   num_read_outstanding=1 max_read_burst_length=2
    // #pragma HLS INTERFACE m_axi port=elements           offset=slave bundle=gmem_ele   num_read_outstanding=1 max_read_burst_length=2

    distance_t max_cluster_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2];
    distance_t original_distances[MAX_NUM_SPECTRA * (MAX_NUM_SPECTRA + 1) / 2];

    #pragma HLS BIND_STORAGE variable=original_distances type=ram_2p impl=uram
    #pragma HLS BIND_STORAGE variable=max_cluster_distances type=ram_2p impl=uram


    int         local_num_valid_clusters;
    int         local_consensus         [MAX_NUM_SPECTRA]; 
    int         local_valid_clusters    [MAX_NUM_SPECTRA]; 
    bitset_dhv  local_encoded_spectra   [MAX_NUM_SPECTRA];

    Cluster thres_clusters[MAX_NUM_SPECTRA];

    for (int ib=0; ib<batch_size; ib++){
        #pragma HLS loop_tripcount min=250 max=250

        int num_spectra = encoded_spectra_stream.read();

        loop_stream_in: for (int i = 0; i < num_spectra; i++) {
            #pragma HLS loop_tripcount min=300 max=300
            #pragma HLS pipeline
            // #pragma HLS UNROLL FACTOR=2 skip_exit_check
            local_encoded_spectra[i] = encoded_spectra_stream.read();
            
        }
        local_num_valid_clusters = num_spectra;


        int valid_dist_cnt;
        calculate_distance_matrix_kernel(local_encoded_spectra, num_spectra, max_cluster_distances, original_distances, &valid_dist_cnt);

        agglomerative_ccl_kernel(max_cluster_distances, num_spectra, local_valid_clusters, &local_num_valid_clusters, thres_clusters, valid_dist_cnt);

        calculate_consensus<true>(original_distances, thres_clusters, local_valid_clusters, local_consensus, local_num_valid_clusters);


        int offset = batch_size*CLUSTER_SIZE;
        num_valid_clusters[offset] = local_num_valid_clusters;
        copy_cluster_elements: for (int i = 0; i < local_num_valid_clusters; i++) {
            #pragma HLS loop_tripcount min=30 max=30
            #pragma HLS pipeline
            #pragma HLS UNROLL FACTOR=2 skip_exit_check

            int cluster_idx = local_valid_clusters[i];
            // valid_clusters[offset + i] = cluster_idx;
            num_elements[offset + i] = thres_clusters[cluster_idx].num_elements;
            consensus[offset + i] = local_consensus[i];
            
        }

        int element_copy_cnt = offset;
        copy_cluster_elements_inner: for (int i = 0; i < local_num_valid_clusters; i++) {
            #pragma HLS loop_tripcount min=30 max=30
            int cluster_idx = local_valid_clusters[i];
            int num_elements = thres_clusters[cluster_idx].num_elements;
            int iter_element = cluster_idx;
            for (int j = 0; j < num_elements; j++) {
                #pragma HLS loop_tripcount min=4 max=20
                #pragma HLS pipeline
                    elements[element_copy_cnt++] = iter_element;
                    iter_element = thres_clusters[iter_element].next;
                }
        }
    }
}

void testout(hls::stream<EncodedBuffer> &encoded_spectra_stream) {
    #pragma HLS INLINE off
    int num_sp = encoded_spectra_stream.read();
    for (int j = 0; j < num_sp; ++j) {
        #pragma HLS loop_tripcount min=300 max=300
        encoded_spectra_stream.read();
    }
}

extern "C" void top_wrapper(
    bitset_dhv *ID_Level_buffer,
    ap_uint<PEAK_PORT_W> *peak_mz_buffer,
    ap_uint<PEAK_PORT_W> *peak_intensity_buffer,
    int *peak_count_buffer,
    int *num_spectra_buffer,
    // bitset_dhv *encoded_spectra_hbm,
    int  batch_size,


    int *c0_num_valid_clusters, // 1
    int *c0_elements, //[MAX_NUM_SPECTRA * CLUSTER_SIZE],
    int *c0_num_elements, // [CLUSTER_SIZE]
    int *c0_consensus, //[CLUSTER_SIZE],

    int *c1_num_valid_clusters, // 1
    int *c1_elements, //[MAX_NUM_SPECTRA * CLUSTER_SIZE],
    int *c1_num_elements, // [CLUSTER_SIZE]
    int *c1_consensus, //[CLUSTER_SIZE],

    int *c2_num_valid_clusters, // 1
    int *c2_elements, //[MAX_NUM_SPECTRA * CLUSTER_SIZE],
    int *c2_num_elements, // [CLUSTER_SIZE]
    int *c2_consensus, //[CLUSTER_SIZE],

    int *c3_num_valid_clusters, // 1
    int *c3_elements, //[MAX_NUM_SPECTRA * CLUSTER_SIZE],
    int *c3_num_elements, // [CLUSTER_SIZE]
    int *c3_consensus //[CLUSTER_SIZE],
) {

    #pragma HLS INTERFACE m_axi port=ID_Level_buffer        offset=slave bundle=gmem0    num_write_outstanding=1 max_write_burst_length=2
    #pragma HLS INTERFACE m_axi port=peak_mz_buffer         offset=slave bundle=gmem2    num_write_outstanding=1 max_write_burst_length=2
    #pragma HLS INTERFACE m_axi port=peak_intensity_buffer  offset=slave bundle=gmem3    num_write_outstanding=1 max_write_burst_length=2
    #pragma HLS INTERFACE m_axi port=peak_count_buffer      offset=slave bundle=gmem0    num_write_outstanding=1 max_write_burst_length=2
    #pragma HLS INTERFACE m_axi port=num_spectra_buffer     offset=slave bundle=gmem5    num_write_outstanding=1 max_write_burst_length=2


    #pragma HLS INTERFACE m_axi port=c0_num_valid_clusters offset=slave bundle=gmem0_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c0_num_elements       offset=slave bundle=gmem0_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c0_consensus          offset=slave bundle=gmem0_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c0_elements           offset=slave bundle=gmem0_ele   num_read_outstanding=1 max_read_burst_length=2

    #pragma HLS INTERFACE m_axi port=c1_num_valid_clusters offset=slave bundle=gmem1_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c1_num_elements       offset=slave bundle=gmem1_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c1_consensus          offset=slave bundle=gmem1_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c1_elements           offset=slave bundle=gmem1_ele   num_read_outstanding=1 max_read_burst_length=2

    #pragma HLS INTERFACE m_axi port=c2_num_valid_clusters offset=slave bundle=gmem2_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c2_num_elements       offset=slave bundle=gmem2_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c2_consensus          offset=slave bundle=gmem2_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c2_elements           offset=slave bundle=gmem2_ele   num_read_outstanding=1 max_read_burst_length=2

    #pragma HLS INTERFACE m_axi port=c3_num_valid_clusters offset=slave bundle=gmem3_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c3_num_elements       offset=slave bundle=gmem3_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c3_consensus          offset=slave bundle=gmem3_num   num_read_outstanding=1 max_read_burst_length=2
    #pragma HLS INTERFACE m_axi port=c3_elements           offset=slave bundle=gmem3_ele   num_read_outstanding=1 max_read_burst_length=2

    // #pragma HLS interface mode=ap_ctrl_none port=return

    hls::stream<EncodedBuffer> encoded_spectra_stream[N_CLUSTERING];
    #pragma HLS STREAM variable=encoded_spectra_stream depth=333 type=fifo


    #pragma HLS DATAFLOW

    int batch_size0 = (batch_size+3)/N_CLUSTERING;
    int batch_size1 = (batch_size+2)/N_CLUSTERING;
    int batch_size2 = (batch_size+1)/N_CLUSTERING;
    int batch_size3 = (batch_size+0)/N_CLUSTERING;
    encoding_kernel(ID_Level_buffer, peak_mz_buffer, peak_intensity_buffer,
                    peak_count_buffer, num_spectra_buffer, encoded_spectra_stream,
                    batch_size);

    clustering_kernel(encoded_spectra_stream[0],c0_num_valid_clusters, c0_elements, c0_num_elements, c0_consensus, batch_size0);
    clustering_kernel(encoded_spectra_stream[1],c1_num_valid_clusters, c1_elements, c1_num_elements, c1_consensus, batch_size1);
    clustering_kernel(encoded_spectra_stream[2],c2_num_valid_clusters, c2_elements, c2_num_elements, c2_consensus, batch_size2);
    clustering_kernel(encoded_spectra_stream[3],c3_num_valid_clusters, c3_elements, c3_num_elements, c3_consensus, batch_size3);
        
    
    
} 

