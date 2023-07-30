#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <math.h>
#include <unordered_set>

#include <gflags/gflags.h>
#include <tapa.h>

#include "knn.h"

// AlveoLink imports
#include <vector>
#include "genColHost.hpp"
#include "netLayer.hpp"
#include "popl.hpp"
#include "xNativeFPGA.hpp"
#include "/home/ubuntu/fpga-runtime/src/frt.cpp"


using std::clog;
using std::endl;
using std::vector;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
typedef ap_axiu<SWIDTH, 0, 0, 0> pkt;
typedef ap_axiu<SWIDTH, 0, 0, 0>    id_pkt;
void Knn_1(
    tapa::mmap<INTERFACE_WIDTH> in_0,  tapa::mmap<INTERFACE_WIDTH> in_1,
    tapa::mmap<INTERFACE_WIDTH> in_2,  tapa::mmap<INTERFACE_WIDTH> in_3,
    tapa::mmap<INTERFACE_WIDTH> in_4,  tapa::mmap<INTERFACE_WIDTH> in_5,
    tapa::mmap<INTERFACE_WIDTH> in_6,  tapa::mmap<INTERFACE_WIDTH> in_7,
    tapa::mmap<INTERFACE_WIDTH> in_8, tapa::mmap<pkt> temp1, 
    tapa::mmap<id_pkt> temp2, tapa::mmap<pkt> temp3, 
    tapa::mmap<id_pkt> temp4, tapa::mmap<pkt> temp5, 
    tapa::mmap<id_pkt> temp6
);

void Knn_2(
    tapa::mmap<INTERFACE_WIDTH> in_9,
  tapa::mmap<INTERFACE_WIDTH> in_10, tapa::mmap<INTERFACE_WIDTH> in_11,
  tapa::mmap<INTERFACE_WIDTH> in_12, tapa::mmap<INTERFACE_WIDTH> in_13,
  tapa::mmap<INTERFACE_WIDTH> in_14, tapa::mmap<INTERFACE_WIDTH> in_15,
  tapa::mmap<INTERFACE_WIDTH> in_16, tapa::mmap<INTERFACE_WIDTH> in_17,
  tapa::mmap<pkt> temp1, tapa::mmap<id_pkt> temp2, tapa::mmap<pkt> temp3, 
  tapa::mmap<pkt> temp5, tapa::mmap<id_pkt> temp6, tapa::mmap<pkt> temp7,
  tapa::mmap<float> L3_out_dist, tapa::mmap<int> L3_out_id
);

DEFINE_string(bitstream, "", "path to bitstream file, run csim if empty");

// sorting operator
struct {
    bool operator()(const std::pair<DATA_TYPE, int>& a, const std::pair<DATA_TYPE, int>& b){
        if (a.first < b.first) {
            return true;
        } else if (a.first > b.first) {
            return false;
        } else {
            // Sort based on ID secondarily.
            if (a.second < b.second) {
                return true;
            } else {
                return false;
            }
        }
    }
} custom_cmp;

DATA_TYPE square_and_handle_overflow(DATA_TYPE input)
{
    // Detect if we will have (over/under)flow after squaring input.
    // Return MAX_DATA_TYPE_VAL if we will over or underflow,
    //  and input * input if we wont.

    if (input == 0) {
        return 0;
    }
    else if (input < -1*MAX_DATA_TYPE_VAL) {
        // if input is the smallest possible value, the rest of the handling wont work properly.
        return MAX_DATA_TYPE_VAL;
    }
    else if ( (fabs(input) >= FLOOR_SQRT_MAX_DATA_TYPE_VAL) ) {
        return MAX_DATA_TYPE_VAL;
    }
    else {
        return input * input;
    }

}

DATA_TYPE add_and_handle_overflow(DATA_TYPE a_val, DATA_TYPE b_val)
{
    // Detect if we will have (over/under)flow after addition.
    // Return MAX_DATA_TYPE_VAL if we will overflow, -1*MAX_DATA_TYPE_VAL if we will underflow,
    //  and a_val + b_val if we wont.

    if ((a_val > 0) && (b_val > static_cast<DATA_TYPE>(MAX_DATA_TYPE_VAL) - a_val)) {
        return MAX_DATA_TYPE_VAL;
    }
    else if ((a_val < 0) && (b_val < static_cast<DATA_TYPE>(-1*MAX_DATA_TYPE_VAL) - a_val)) {
        // NOTE: dont return MIN, because fabs() behaves incorrectly with MIN.
        return -1 * MAX_DATA_TYPE_VAL;
    }
    else {
        return a_val + b_val;
    }
}

DATA_TYPE calc_single_dim_dist( DATA_TYPE query_point,
                                DATA_TYPE data_point)
{
    DATA_TYPE delta=0.0;

    if (DISTANCE_METRIC == 0){
        delta = fabs( add_and_handle_overflow(query_point,  -1*data_point) );
    }else if (DISTANCE_METRIC == 1){
        delta = add_and_handle_overflow(query_point,  -1*data_point);
        delta = square_and_handle_overflow(delta);
    }
    return delta;
}

bool elementsAreDistinct(std::vector<int> input)
{
    int input_size = input.size();

    std::unordered_set<int> element_set;
    for (int i = 0; i < input_size; ++i) {
        element_set.insert(input[i]);
    }

    return (element_set.size() == input.size());
}
// Function for verifying results
bool verify(std::vector<DATA_TYPE> &sw_dist,
            std::vector<DATA_TYPE> &hw_dist,
            std::vector<int> &sw_id,
            std::vector<int> &hw_id,
            std::vector<DATA_TYPE> &query,
            std::vector<DATA_TYPE> &searchSpace,
            unsigned int size)
{
    bool check = true;

    if (elementsAreDistinct(hw_id) == false)
    {
        check = false;
        std::cout << "ERROR!!! Some of the FPGAs IDs are duplicates!" << std::endl;
    }
    if (elementsAreDistinct(sw_id) == false)
    {
        check = false;
        std::cout << "TEST GENERATION ERROR. Some of the CPUs Top K IDs are duplicates." << std::endl;
    }

    for (unsigned int i=0; i<size; ++i) {

        std::cout << "i = " << i
                  << std::endl;

        // The top K distances all must match, otherwise there was a bug.
        if (sw_dist[i] != hw_dist[i]) {
            check = false;
            std::cout << "	ERROR!!! Result mismatch on i = " << i
                      << std::endl;
        }
        // If the ID doesnt match, there might have been a few points that
        // coincidentally had the same distance, and the FPGA might have returned
        // them in a different order. Check to make sure these distances
        // are correct.
        else if (sw_id[i] != hw_id[i]) {
            DATA_TYPE tmp_sw_dist;
            DATA_TYPE tmp_hw_dist;
            DATA_TYPE delta_sum = 0;
            DATA_TYPE delta = 0;

            // Calculate distance for the sw_id, and the hw_id.
            delta_sum = 0.0;
            for (unsigned int j=0; j<INPUT_DIM; ++j){
                delta = calc_single_dim_dist(query[j], searchSpace[sw_id[i]*INPUT_DIM+j]);
                delta_sum = add_and_handle_overflow( delta_sum, delta );
            }
            tmp_sw_dist = delta_sum;

            delta_sum = 0.0;
            for (unsigned int j=0; j<INPUT_DIM; ++j){
                delta = calc_single_dim_dist(query[j], searchSpace[hw_id[i]*INPUT_DIM+j]);
                delta_sum = add_and_handle_overflow( delta_sum, delta );
            }
            tmp_hw_dist = delta_sum;

            if (tmp_hw_dist != tmp_sw_dist) {
                check = false;
                std::cout << "	ERROR!!! Result mismatch on i = " << i
                          << std::endl;
            } else {
                std::cout << "	ID mismatch, but the distances were the same." << std::endl;
            }
        }

        std::cout << " CPU result = " << sw_id[i] << " : " << sw_dist[i]
                  << std::endl
                  << " FPGA result = " << hw_id[i] << " : " << hw_dist[i]
                  << std::endl
                  << " Delta = " << fabs(sw_dist[i] - hw_dist[i])
                  << std::endl;

    }

    return check;
}

void Generate_sw_verif_data(std::vector<DATA_TYPE> &query,
                            std::vector<DATA_TYPE> &searchSpace,
                            std::vector<DATA_TYPE> &dist,
                            std::vector<int> &id,
                            unsigned int num_of_points)
{
    // Generate random DATA_TYPE data
    std::fill(query.begin(), query.end(), 0.0);
    std::fill(searchSpace.begin(), searchSpace.end(), 0.0);
    std::fill(dist.begin(), dist.end(), MAX_DATA_TYPE_VAL);
    std::fill(id.begin(), id.end(), 0);

    for (unsigned int i=0; i<INPUT_DIM; ++i){
        // For a float payload, we want to normalize everything between 0 and 1
        query[i] = static_cast <DATA_TYPE>(rand()) / static_cast<DATA_TYPE>(RAND_MAX);
    }

#if DATA_TYPE_TOTAL_SZ <= 20
    unsigned long long int two_pow_data_type_total_sz = pow(static_cast<double> (2),
                                                    static_cast<double> (DATA_TYPE_TOTAL_SZ));
    unsigned long long int num_of_non_max_values = two_pow_data_type_total_sz / 4;
    //unsigned long long int num_of_non_max_values = 500;
    unsigned int start_of_non_max_values = rand() % (num_of_points - num_of_non_max_values);
    //unsigned int start_of_non_max_values = 15;

    printf("\nStart of non-max values = %d\n", start_of_non_max_values);
    printf("\nNum of non-max value = %lld\n", num_of_non_max_values);
#endif


    for (unsigned long long int i=0; i<num_of_points*INPUT_DIM; ++i){
        // For a float payload, we want to normalize everything between 0 and 1
        searchSpace[i] = static_cast <DATA_TYPE>(rand()) / static_cast<DATA_TYPE>(RAND_MAX);

    }

    DATA_TYPE delta_sum=0.0;
    DATA_TYPE delta=0.0;
    std::vector<DATA_TYPE> distance(num_of_points);

    for (unsigned int i=0; i<num_of_points; ++i){
        delta_sum = 0.0;
        for (unsigned int j=0; j<INPUT_DIM; ++j){
            delta = calc_single_dim_dist(query[j], searchSpace[i*INPUT_DIM+j]);
            delta_sum = add_and_handle_overflow( delta_sum, delta );
        }
        distance[i] = delta_sum;

        // if (i % 1000 == 0)
        // {
        //     printf("KDEBUG: distance[%d] = %f\n", i, distance[i]);
        // }
    }

    // Sort distances METHOD 1 (original)
    std::vector<DATA_TYPE> distance_cpy(distance);
    std::vector<DATA_TYPE> dist_old_algo(TOP);
    std::vector<int> id_old_algo(TOP);
    std::sort(distance_cpy.begin(), distance_cpy.end());

    for (int i(0); i < TOP; ++i){
        dist_old_algo[i] = distance_cpy[TOP-1-i];
    }

    for (int i(0); i<TOP; ++i){
        for (unsigned int j(0); j < num_of_points; ++j){
            if (distance[j] == dist_old_algo[i]){
                id_old_algo[i] = j;
                break;
            }
        }
    }

    // Sort distances METHOD 2 (new)
    std::vector<std::pair<DATA_TYPE, int>> distance_and_id(num_of_points);

    for (unsigned int i(0); i < num_of_points; ++i){
        distance_and_id[i] = std::make_pair(distance[i], i);
    }

    std::sort(distance_and_id.begin(), distance_and_id.end(), custom_cmp);

    for (int i(0); i < TOP; ++i){
        dist[i] = distance_and_id[TOP-1-i].first;
        id[i] = distance_and_id[TOP-1-i].second;
    }


    // Check to make sure method 2 works
    printf("\n\nKDEBUG: CHECKING the new sorting method now!!\n");
    for (int i(0); i < TOP; ++i){
        printf("dist[%d].first      = %f\n",   i, dist[i]);
        printf("dist_old_algo[%d]   = %f\n",   i, dist_old_algo[i]);
        printf("id[%d].second       = %d\n",   i, id[i]);
        printf("id_old_algo[%d]     = %d\n\n", i, id_old_algo[i]);

        if (dist_old_algo[i] != dist[i]){
            printf("\n\nERROR IN SOFTWARE SORTING, SOMEHOW :(\n\n");
            exit(15);
        } else if (id_old_algo[i] != id[i]){
            printf("\nWARNING: Top K index %d got a bad ID\n", i);
        }
    }

    // Debugging: Print a few of the values we generated
    for (int i(0); i<TOP; ++i){
        printf("KDEBUG: dist[%d]        = %f\n", i, dist[i]);
        printf("KDEBUG: searchSpace[%d] = %f\n", i, searchSpace[i]);
    }

    return;
}

int main(int argc, char* argv[]){
    gflags::ParseCommandLineFlags(&argc, &argv, /*remove_flags=*/true);
    int num_pe = 18;
    int dataSize = NUM_SP_PTS_PADDED * num_pe;
    vector<float> searchspace_data(dataSize*INPUT_DIM);
	vector<float> searchspace_data_part[num_pe];
    vector<float> query_data(INPUT_DIM);

    vector<float> sw_dist(TOP);
    vector<int> sw_id(TOP);
    vector<float> hw_dist(TOP);
    vector<int> hw_id(TOP);
    // Initializing hw output vectors to zero
    std::fill(hw_dist.begin(), hw_dist.end(), 0.0);
    std::fill(hw_id.begin(), hw_id.end(), 0);

    // generate sw results
    Generate_sw_verif_data(query_data, searchspace_data, sw_dist, sw_id, dataSize);
    // partition the full matrix into separate submatrices
    int starting_idx = 0;
    int part_size = dataSize*INPUT_DIM/num_pe;
    for (int i = 0; i < num_pe; ++i) {
        starting_idx = i*part_size;
        searchspace_data_part[i].resize(QUERY_FEATURE_RESERVE + part_size);
        for (unsigned int j = 0; j < QUERY_FEATURE_RESERVE; ++j){
            searchspace_data_part[i][j] = 0.0;
        }
        for (int j = 0; j < INPUT_DIM; ++j){
            searchspace_data_part[i][j] = query_data[j];
        }
        for (int j = 0; j < part_size; ++j){
            searchspace_data_part[i][QUERY_FEATURE_RESERVE + j] = searchspace_data[starting_idx+j];
        }
    }
	// format data based on packing factor on AXI ports
    vector<INTERFACE_WIDTH> in[18];
	int data_packing_factor = (IWIDTH/32);
	int formatted_length = (QUERY_FEATURE_RESERVE + part_size)/data_packing_factor;
	for (int i(0); i<18; ++i) {
		in[i].resize(formatted_length);
		for (int j(0); j<formatted_length; ++j) {
			INTERFACE_WIDTH tmp;
			for (int k(0); k<data_packing_factor; ++k) {
				float this_ele = searchspace_data_part[i][j*data_packing_factor + k];
				tmp.range(k*32+31, k*32) = *((uint32_t *)(&this_ele));
			}
			in[i][j] = tmp;
		}
	}

    // AlveoLink setups
    std::cout<<"starting device stuff"<<std::endl;
    AlveoLink::common::FPGA fpga_card[2];
    fpga_card[0].setId(0);
    fpga_card[1].setId(1);
    std::cout<<"Loading first xclbin"<<std::endl;
    fpga_card[0].load_xclbin("./Knn_1_.xclbin");
    std::cout<<"Loaded xclbin on first fpga, loading second xclbin"<<std::endl;
    fpga_card[1].load_xclbin("./Knn_2_.xclbin");
    std::cout<<"Loaded xclbin on second FPGA"<<std::endl;
    AlveoLink::network_roce_v2::NetLayer<2> l_netLayer[2];
    for (auto i=0; i<2; ++i) {
    std::cout<<"in here?"<<std::endl;
    l_netLayer[i].init(&(fpga_card[i]));
    std::cout<<"init"<<std::endl;
    for (auto j=0; j<2; ++j) {
        std::cout<<"we reach inside"<<std::endl;
        l_netLayer[i].setIPSubnet(j, 0x0000a8c0);
        l_netLayer[i].setMACSubnet(j, 0x347844332211);
        l_netLayer[i].setID(j, i*2+j);
        std::cout<<"we reach here"<<std::endl;
        }
    }
    std::cout<<"setup the links on both"<<std::endl;
    for (auto i=0; i<2; ++i) {
        for (auto j=0; j<2; ++j) {
            std::cout <<"INFO: turn on RS_FEC for device " << i << " port " <<j << std::endl;
            l_netLayer[i].turnOn_RS_FEC(j, true);
        }
    }
    unsigned int l_totalDevLinksUp = 0;
    while (l_totalDevLinksUp < 2) {
        std::cout << "INFO: Waiting for links up on device " << l_totalDevLinksUp << std::endl;
        if (l_netLayer[l_totalDevLinksUp].linksUp()) {
            l_totalDevLinksUp++;
        }
    }
    auto start = high_resolution_clock::now();
    // tapa::invoke(Knn_1, FLAGS_bitstream,
    //             tapa::read_only_mmap<INTERFACE_WIDTH>(in[0]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[1]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[2]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[3]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[4]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[5]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[6]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[7]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[8]),
    //             )
	// tapa::invoke(Knn, FLAGS_bitstream,
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[0]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[1]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[2]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[3]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[4]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[5]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[6]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[7]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[8]),  tapa::read_only_mmap<INTERFACE_WIDTH>(in[9]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[10]), tapa::read_only_mmap<INTERFACE_WIDTH>(in[11]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[12]), tapa::read_only_mmap<INTERFACE_WIDTH>(in[13]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[14]), tapa::read_only_mmap<INTERFACE_WIDTH>(in[15]),
	// 			 tapa::read_only_mmap<INTERFACE_WIDTH>(in[16]), tapa::read_only_mmap<INTERFACE_WIDTH>(in[17]),
	// 			 tapa::write_only_mmap<float>(hw_dist), tapa::write_only_mmap<int>(hw_id));
	auto stop = high_resolution_clock::now();
	duration<double> elapsed = stop - start;
	clog << "elapsed time: " << elapsed.count() << " s" << endl;
    return 0;

    
}
