


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <CL/cl2.hpp>
//#include <CL/cl.hpp>
#include <chrono>  
#include <map>
#include <CL/cl_ext_xilinx.h>

#include <fcntl.h>     
#include <sys/stat.h>  
#include <unistd.h>    
#include <sys/mman.h>  




#include "../kernel/hac.h"


     
    //  const int NUM_BATCH = 51923; 
    const int mMAX_BATCH_SIZE = 1024;
    const int NUM_BATCH = 2048; 

    #define NUM_KERNELS N_CLUSTERING
    #define NUM_KERNELS_ENCODING 1

    const int clu_MAX_BATCH_SIZE = (mMAX_BATCH_SIZE+NUM_KERNELS)/NUM_KERNELS;





void read_processed_csv_files(const std::string &input_file_mz, const std::string &input_file_intensity,
                              std::vector<std::vector<std::pair<float, float>>> &spectra)
{
    std::ifstream infile_mz(input_file_mz);
    std::ifstream infile_intensity(input_file_intensity);
    std::string line_mz, line_intensity;

    while (std::getline(infile_mz, line_mz) && std::getline(infile_intensity, line_intensity))
    {
        std::vector<std::pair<float, float>> spectrum;
        std::istringstream iss_mz(line_mz), iss_intensity(line_intensity);
        std::string token_mz, token_intensity;

        while (std::getline(iss_mz, token_mz, ',') && std::getline(iss_intensity, token_intensity, ','))
        {
            float mz = std::stof(token_mz);
            float intensity = std::stof(token_intensity);

            if(mz != -1.0f) {
                spectrum.push_back({mz, intensity});
            }
        }

        spectra.push_back(spectrum);
    }
}






void read_input_data(const std::vector<std::vector<std::pair<float, float>>> &spectra,
                     int *peak_mz_buffer,
                     int *peak_intensity_buffer,
                     int *peak_count_buffer,
                     int &start_spectra,
                     int num_spectra) {

    int end_spectra = start_spectra + num_spectra;

    for (int i = 0; i < num_spectra; i++) {
        int peak_count = spectra[start_spectra + i].size();
        peak_count_buffer[i] = peak_count;
    }

    for (int i = 0; i < num_spectra; i++) {
        for (int j = 0; j < peak_count_buffer[i]; j++) {
            float mz = spectra[start_spectra + i][j].first;
            int quantized_mz = static_cast<int>(2 * mz);
            peak_mz_buffer[i * MAX_PEAKS + j] = quantized_mz;
            float intensity = spectra[start_spectra + i][j].second;
            int partitioned_intensity = static_cast<int>(intensity * (Q - 1));
            peak_intensity_buffer[i * MAX_PEAKS + j] = partitioned_intensity;
        }
    }

    start_spectra = end_spectra;  



}






std::multimap<int, int> load_bucket_sizes(const std::string &filename) {
    std::multimap<int, int> bucket_sizes;
    std::ifstream file(filename);

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string bucket_str, spectra_str;

        std::getline(ss, bucket_str, ',');
        std::getline(ss, spectra_str, ',');

        int bucket = std::stoi(bucket_str);
        int spectra = std::stoi(spectra_str);

        bucket_sizes.insert(std::make_pair(bucket, spectra));
    }

    return bucket_sizes;
}









bitset_dhv read_encoded_vector(const std::string &line) {
    bitset_dhv encoded_vector;
    for (int i = 0; i < Dhv; i++) {
        encoded_vector[i] = (line[i] == '1');
    }
    return encoded_vector;
}






void read_hypervectors(const std::string &filename, std::vector<bitset_dhv> &hypervectors) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Unable to open the input file '" << filename << "'." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(infile, line)) {
        hypervectors.push_back(read_encoded_vector(line));
    }
    infile.close();
}





 void print_clusters_temp(
    const int *elements, 
    const int *num_elements, 
    const int *consensus, 
    const int *valid_clusters, 
    int num_valid_clusters, 
    const std::string& file_path){
   
    std::ofstream file(file_path, std::ios_base::app);



    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        return;
    }


    // for (int i=0; i<CLUSTER_SIZE; ++i ){
    //     // for (int j=0; j<CLUSTER_SIZE; ++j ){
    //     //     file << valid_clusters[i * CLUSTER_SIZE + j] <<" ";
    //     // }file <<"\n";
    //     file << consensus[i]<<" ";
    // }
    // file <<std::endl;
    for (int i = 0; i < num_valid_clusters; i++) {
        int cluster_idx = valid_clusters[i];
        std::string line;
        for (int j = 0; j < num_elements[i]; j++) {
            line += std::to_string(elements[i * CLUSTER_SIZE + j]) + " ";
        }
       
        line += "Consensus: " + std::to_string(consensus[i]);
        file << "Cluster " << i << ": " << line << std::endl;
    }


    file <<  std::endl;

    file.close();
}







void print_clusters(
    const int *elements, 
    const int *num_elements, 
    const int *consensus, 
    const int *valid_clusters, 
    int num_valid_clusters, 
    const std::string& file_path,
    int offset,
    int idx_offset) {
   
    std::ofstream file(file_path, std::ios_base::app);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        return;
    }

    
    std::vector<std::tuple<int, int, bool>> results;

     
    for (int i = 0; i < num_valid_clusters; i++) {
        int cluster_idx = valid_clusters[i];
        for (int j = 0; j < num_elements[i]; j++) {
            int element = elements[i * CLUSTER_SIZE + j];
            bool is_consensus = element == consensus[i];
            results.emplace_back(element+idx_offset, i + offset, is_consensus);  
        }
    }
     

    std::sort(results.begin(), results.end());

     
    for (const auto &result : results) {
        file << std::get<0>(result) << ", " << std::get<1>(result) << ", " << (std::get<2>(result) ? "TRUE" : "FALSE") << std::endl;
    }

    
    file.close();
}
