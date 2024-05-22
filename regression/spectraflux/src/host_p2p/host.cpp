

#include "host.h"

decltype(&xclGetMemObjectFd) xcl::P2P::getMemObjectFd = nullptr;
decltype(&xclGetMemObjectFromFd) xcl::P2P::getMemObjectFromFd = nullptr;

cl_program xcl_import_binary_file(cl_device_id device_id, cl_context context, const char* xclbin_file_name);
//==================================================================================================


int main(int argc, char **argv)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::cout <<"HV Width: " << sizeof(bitset_dhv) << "Byte" << std::endl;
    
    // OpenCL-related var
    // cl_kernel kernels[NUM_KERNELS];
    // cl_kernel kernels_encoding[NUM_KERNELS_ENCODING];
    cl_int err;
    cl_command_queue q[N_FPGA];
    cl_device_id device[N_FPGA];
    cl_context context[N_FPGA];
    cl_program program[N_FPGA];
    cl_platform_id platform;
    cl_int ret;
    cl_uint num_platforms;
    
    // Kernel's buffers on host
    // std::vector<std::vector<int>> valid_clusters(NUM_KERNELS, std::vector<int>(MAX_NUM_SPECTRA));
    std::vector<std::vector<int>> elements(NUM_KERNELS, std::vector<int>(MAX_NUM_SPECTRA * clu_MAX_BATCH_SIZE, 0));
    std::vector<std::vector<int>> num_elements(NUM_KERNELS, std::vector<int>(MAX_NUM_SPECTRA * clu_MAX_BATCH_SIZE, 0));
    std::vector<std::vector<int>> consensus(NUM_KERNELS, std::vector<int>(MAX_NUM_SPECTRA * clu_MAX_BATCH_SIZE, 0));
    std::vector<std::vector<int>> num_valid_clusters(NUM_KERNELS, std::vector<int>(clu_MAX_BATCH_SIZE, 0));
    // std::vector<std::vector<int>> num_consensus(NUM_KERNELS, std::vector<int>(MAX_NUM_SPECTRA, 0));
    
    std::vector<int> num_spectra_arr(NUM_BATCH);

    std::vector<std::vector<bitset_dhv>> encoded_spectra_hbm(NUM_BATCH);
    std::vector<std::vector<bitset_dhv>> encoded_spectra(NUM_BATCH);    


    // Read the bucket_size file
    std::multimap<int, int> bucket_sizes = load_bucket_sizes("./data/small1511_bucket.csv");
    // std::multimap<int, int> bucket_sizes = load_bucket_sizes("/home/coder/Spec-HD/data/bucket_breakdown_1511_300.csv");
    std::vector<std::pair<int, int>> bucket_sizes_vec(bucket_sizes.begin(), bucket_sizes.end());
     

    for (int ii = 0; ii < NUM_BATCH; ii++) {
        num_spectra_arr[ii] = bucket_sizes_vec[ii].second;
        // num_valid_clusters[ii] = bucket_sizes_vec[ii].second;
    }


    // Read the CSV file
    std::vector<std::vector<std::pair<float, float>>> spectra;
    auto start_timex = std::chrono::high_resolution_clock::now();
    // read_processed_csv_files("/home/coder/Spec-HD/data/spectra_mz_1511_1.csv", "/home/coder/Spec-HD/data/spectra_intensity_1511_1.csv", spectra);
    read_processed_csv_files("./data/small1511_mz.csv", "./data/small1511_intensity.csv", spectra);
    auto end_time_csv = std::chrono::high_resolution_clock::now();
    auto time_csv = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_csv - start_timex).count();
    std::cout << "Time to read CSV files: " << time_csv << " milliseconds" << std::endl;
    
    
    // Parse the spectra file
    std::vector<std::vector<int>> peak_mz_buffer(NUM_BATCH/mMAX_BATCH_SIZE+1, std::vector<int>(mMAX_BATCH_SIZE * MAX_NUM_SPECTRA * MAX_PEAKS, 0));
    std::vector<std::vector<int>> peak_intensity_buffer(NUM_BATCH/mMAX_BATCH_SIZE+1, std::vector<int>(mMAX_BATCH_SIZE * MAX_NUM_SPECTRA * MAX_PEAKS, 0));
    std::vector<std::vector<int>> peak_count_buffer(NUM_BATCH/mMAX_BATCH_SIZE+1, std::vector<int>(mMAX_BATCH_SIZE * MAX_NUM_SPECTRA, 0));

    auto start_timey = std::chrono::high_resolution_clock::now();
    int start_spectra = 0;
    for (int i = 0; i < NUM_BATCH; i++) {
        int idx = i / mMAX_BATCH_SIZE;
        int offset = i % mMAX_BATCH_SIZE;
        read_input_data(spectra, peak_mz_buffer[idx].data() + offset * MAX_NUM_SPECTRA * MAX_PEAKS, peak_intensity_buffer[idx].data() + offset * MAX_NUM_SPECTRA * MAX_PEAKS,
                            peak_count_buffer[idx].data() + offset  * MAX_NUM_SPECTRA, start_spectra, num_spectra_arr[i]);
         
        // std::cout << start_spectra << std::endl;
    }
    auto end_time_loop = std::chrono::high_resolution_clock::now();
    auto time_loop = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_loop - start_timey).count();
    std::cout << "Time for loop: " << time_loop << " milliseconds" << std::endl;
    std::cout << "spectra size"  << spectra.size() << std::endl;
    
    
    // Load the HD model
    std::vector<bitset_dhv> id_hypervectors;
    std::vector<bitset_dhv> level_hypervectors;
    bitset_dhv id[f];
    bitset_dhv level[Q];
    bitset_dhv id_level[f+Q];

    read_hypervectors("./data/ID_Hypervectors.txt", id_hypervectors);
    read_hypervectors("./data/Level_Hypervectors.txt", level_hypervectors);



    for (int i = 0; i < id_hypervectors.size(); i++) {
        // id[i] = id_hypervectors[i];
        id_level[i] = id_hypervectors[i];
    }
    for (int i = 0; i < level_hypervectors.size(); i++) {
        // level[i] = level_hypervectors[i];
        id_level[i+f] = level_hypervectors[i];
    }
    assert(id_hypervectors.size()==f);
    assert(level_hypervectors.size()==Q);



    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << "  \n";
        return 1;
    }
    std::string binaryFile[N_FPGA];
    for (int i=0; i<N_FPGA; i++){
        binaryFile[i] = argv[1+i];
    }
    
    
    //********************************************* Create the kernel *********************************************

    err = clGetPlatformIDs(0, NULL, &num_platforms);
    if (err != CL_SUCCESS)
    {
        std::cerr << "Error: clGetPlatformIDs() failed with error code " << err << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<cl_platform_id> platforms(num_platforms);
    err = clGetPlatformIDs(num_platforms, platforms.data(), NULL);
    if (err != CL_SUCCESS)
    {
        std::cerr << "Error: clGetPlatformIDs() failed with error code " << err << std::endl;
        return EXIT_FAILURE;
    }

    bool platform_found = false;
    for (cl_uint i = 0; i < num_platforms; i++)
    {
        char platform_name[128];
        err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platform_name), platform_name, NULL);
        if (err != CL_SUCCESS)
        {
            std::cerr << "Error: clGetPlatformInfo() failed with error code " << err << std::endl;
            return EXIT_FAILURE;
        }
        
        if (std::string(platform_name).find("Xilinx") != std::string::npos)
        {
            platform = platforms[i];
            platform_found = true;
            break;
        }
    }

    if (!platform_found)
    {
        std::cerr << "Error: Xilinx platform not found" << std::endl;
        return EXIT_FAILURE;
    }
    

    cl_uint device_count;



    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ACCELERATOR, N_FPGA, device, NULL);
    
    for (int i=0; i<N_FPGA; i++){
        context[i] = clCreateContext(0, 1, &device[i], NULL, NULL, &err);
        err, q[i] = clCreateCommandQueue(context[i], device[i], CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &err);
    }
    
    // std::ifstream file(binaryFile, std::ios::binary);
    // file.seekg(0, std::ios::end);
    // size_t length = file.tellg();
    // file.seekg(0, std::ios::beg);
    
    // char *buffer = new char[length];
    
    // file.read(buffer, length);
    // file.close();
    // size_t size = length;
    // program = clCreateProgramWithBinary(context, 1, &device, &size, (const unsigned char **)&buffer, NULL, &err);
    // delete[] buffer;
    

    // if (err != CL_SUCCESS)
    // {
    //     std::cerr << "Error: clCreateProgramWithBinary() failed with error code " << err << std::endl;
    //     return EXIT_FAILURE;
    // }
    
    
    // err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    // if (err != CL_SUCCESS)
    // {
    //     std::cerr << "Error: clBuildProgram() failed with error code " << err << std::endl;
    //     return EXIT_FAILURE;
    // }

    cl_kernel krnl_1, krnl_2;

    for (int i=0; i<N_FPGA; i++){
        program[i] = xcl_import_binary_file(device[i], context[i], binaryFile[i].c_str());
    }
    std::cout<<"1111"<<std::endl;


    /*
    for (int i = 0; i < NUM_KERNELS_ENCODING; i++) {
        
        kernels_encoding[i] = clCreateKernel(program, "encoding_kernel", &err);
        if (err != CL_SUCCESS) {
            std::cerr << "Error: clCreateKernel() failed with error code " << err << std::endl;
            return EXIT_FAILURE;
        }
        
    }
        
    
    
    for (int i = 0; i < NUM_KERNELS; i++) {
        
        kernels[i] = clCreateKernel(program, "clustering_kernel", &err);
        if (err != CL_SUCCESS) {
            std::cerr << "Error: clCreateKernel() failed with error code " << err << std::endl;
            return EXIT_FAILURE;
        }
        
    }
    */
    
    // kernels_encoding[0] = clCreateKernel(program, "wrapper", &err);
    // kernels[0] = kernels_encoding[0];
    krnl_1 = clCreateKernel(program[0], "wrapper", &err);
    krnl_2 = clCreateKernel(program[1], "wrapper", &err);

    if (err != CL_SUCCESS) {
        std::cerr << "Error: clCreateKernel() failed with error code " << err << std::endl;
        return EXIT_FAILURE;
    }




    std::cout<<"1111"<<std::endl;


    xcl::P2P::init(platform);

    
    /*
    size_t max_work_group_size;
    err = clGetKernelWorkGroupInfo(kernels[0], device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
    if (err != CL_SUCCESS) {
        std::cerr << "Error: clGetKernelWorkGroupInfo() failed with error code " << err << std::endl;
        return EXIT_FAILURE;
    }
    */
    
    
    size_t global_work_size = 1;
    size_t local_size = 1;
    
std::cout<<"1111"<<std::endl;

    //********************************************* Create the buffer *********************************************


    // cl_mem buffer_id[NUM_KERNELS_ENCODING];
    // cl_mem buffer_level[NUM_KERNELS_ENCODING];
    cl_mem buffer_id_level[NUM_KERNELS_ENCODING];
    cl_mem buffer_peak_mz[NUM_KERNELS_ENCODING];
    cl_mem buffer_peak_intensity[NUM_KERNELS_ENCODING];
    cl_mem buffer_peak_count[NUM_KERNELS_ENCODING];
    cl_mem buffer_num_spectra[NUM_KERNELS_ENCODING];
    // cl_mem buffer_encoded_spectra_hbm[NUM_KERNELS_ENCODING];

    cl_mem buffer_temp_krnl1[NUM_KERNELS-1];
    cl_mem buffer_temp_krnl2[NUM_KERNELS-1];

    // cl_mem buffer_encoded_spectra[NUM_KERNELS];
    // cl_mem buffer_valid_clusters[NUM_KERNELS];
    cl_mem buffer_num_valid_clusters[NUM_KERNELS];
    cl_mem buffer_elements[NUM_KERNELS];
    cl_mem buffer_num_elements[NUM_KERNELS];
    cl_mem buffer_consensus[NUM_KERNELS];
    // cl_mem buffer_num_consensus[NUM_KERNELS];
    

    // // cl_mem_ext_ptr_t ext_buffer_id[NUM_KERNELS_ENCODING];
    // // cl_mem_ext_ptr_t ext_buffer_level[NUM_KERNELS_ENCODING];
    // cl_mem_ext_ptr_t ext_buffer_id_level[NUM_KERNELS_ENCODING];
    // cl_mem_ext_ptr_t ext_buffer_peak_mz[NUM_KERNELS_ENCODING];
    // cl_mem_ext_ptr_t ext_buffer_peak_intensity[NUM_KERNELS_ENCODING];
    // cl_mem_ext_ptr_t ext_buffer_peak_count[NUM_KERNELS_ENCODING];
    // cl_mem_ext_ptr_t ext_buffer_encoded_spectra_hbm[NUM_KERNELS_ENCODING];

    cl_mem_ext_ptr_t ext_buffer_temp_krnl2[NUM_KERNELS-1];


    // cl_mem_ext_ptr_t ext_buffer_encoded_spectra[NUM_KERNELS];
    // cl_mem_ext_ptr_t ext_buffer_consensus[NUM_KERNELS];
    // cl_mem_ext_ptr_t ext_buffer_num_consensus[NUM_KERNELS];
    // cl_mem_ext_ptr_t ext_buffer_valid_clusters[NUM_KERNELS];
    // cl_mem_ext_ptr_t ext_buffer_elements[NUM_KERNELS];
    // cl_mem_ext_ptr_t ext_buffer_num_elements[NUM_KERNELS];
    // cl_mem_ext_ptr_t ext_buffer_num_valid_clusters[NUM_KERNELS];


    auto start_time2 = std::chrono::high_resolution_clock::now();
        

    // for (int i = 0; i < NUM_KERNELS_ENCODING; i++) {
    //     // ext_buffer_id[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | (i)), &id[0], 0};
    //     // ext_buffer_level[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | (i)), &level[0], 0};
    //     ext_buffer_id_level[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | (i)), &id_level[0], 0};
    //     // ext_buffer_peak_mz[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | (i)), peak_mz_buffer[i].data(), 0};
    //     ext_buffer_peak_mz[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | (i)), &peak_mz_buffer[i][0], 0};
    //     ext_buffer_peak_intensity[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | (i)), peak_intensity_buffer[i].data(), 0};
    //     ext_buffer_peak_count[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | (i)), peak_count_buffer[i].data(), 0};
   
    // }

    for (int i=0; i < NUM_KERNELS-1; i++){
        ext_buffer_temp_krnl2[i] = {XCL_MEM_EXT_P2P_BUFFER, nullptr, 0};
    }

    
    // for (int i = 0; i < NUM_KERNELS; i++) {
    //     ext_buffer_encoded_spectra[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | 4*(i)+1), &encoded_spectra[i][0], 0};
    //     ext_buffer_consensus[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | 4*(i)+1), &consensus[i][0], 0};
    //     ext_buffer_num_consensus[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | 4*(i)+1), &num_consensus[i][0], 0};
    //     ext_buffer_valid_clusters[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | 4*(i)+1), &valid_clusters[i][0], 0};
    //     ext_buffer_elements[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | 4*(i)+1), &elements[i][0], 0};
    //     ext_buffer_num_elements[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | 4*(i)+1), &num_elements[i][0], 0};
    //     ext_buffer_num_valid_clusters[i] = {static_cast<unsigned int>(XCL_MEM_TOPOLOGY | 4*(i)+1), &num_valid_clusters[i], 0};
    // }

    


    for (int i = 0; i < NUM_KERNELS_ENCODING; i++) {
        // buffer_id[i] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR | CL_MEM_EXT_PTR_XILINX, sizeof(bitset_dhv) * f, &ext_buffer_id[i], &err);
        // buffer_level[i] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR | CL_MEM_EXT_PTR_XILINX, sizeof(bitset_dhv) * Q, &ext_buffer_level[i], &err);
        buffer_id_level[i] = clCreateBuffer(context[0], CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(bitset_dhv) * (f+Q), &id_level[0], &err);

        buffer_peak_mz[i] = clCreateBuffer(context[0], CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * mMAX_BATCH_SIZE * MAX_NUM_SPECTRA * MAX_PEAKS, peak_mz_buffer[i].data(), &err);

        buffer_peak_intensity[i] = clCreateBuffer(context[0], CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * mMAX_BATCH_SIZE * MAX_NUM_SPECTRA * MAX_PEAKS, peak_intensity_buffer[i].data(), &err);

        buffer_peak_count[i] = clCreateBuffer(context[0], CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * mMAX_BATCH_SIZE * MAX_NUM_SPECTRA, peak_count_buffer[i].data(), &err);
        // buffer_encoded_spectra_hbm[i] = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(bitset_dhv)*MAX_NUM_SPECTRA*NUM_BATCH, &encoded_spectra_hbm[i][0], &err);
        buffer_num_spectra[i] = clCreateBuffer(context[0], CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * mMAX_BATCH_SIZE, num_spectra_arr.data(), &err);

        if (err != CL_SUCCESS) {
            std::cerr << "Failed to create buffers for kernel NUM_KERNELS_ENCODING" << i << ". Error code: " << err << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout<<"1111"<<std::endl;
    for (int i = 0; i < NUM_KERNELS-1; i++){
        buffer_temp_krnl1[i] = clCreateBuffer(context[0], CL_MEM_WRITE_ONLY, sizeof(bitset_dhv)*(MAX_NUM_SPECTRA+1)*(mMAX_BATCH_SIZE+N_CLUSTERING-1/N_CLUSTERING), nullptr, &err);
        buffer_temp_krnl2[i] = clCreateBuffer(context[1], CL_MEM_READ_ONLY | CL_MEM_EXT_PTR_XILINX, sizeof(bitset_dhv)*(MAX_NUM_SPECTRA+1)*(mMAX_BATCH_SIZE+N_CLUSTERING-1/N_CLUSTERING), &ext_buffer_temp_krnl2[i], &err);
    }

    for (int i = 0; i < NUM_KERNELS; i++) {
        // buffer_encoded_spectra[i] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_EXT_PTR_XILINX, sizeof(bitset_dhv)*MAX_NUM_SPECTRA, &ext_buffer_encoded_spectra[i], &err);
        buffer_consensus[i] = clCreateBuffer(context[i>0], CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * consensus[i].size(), consensus[i].data(), &err);
        // buffer_num_consensus[i] = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR | CL_MEM_EXT_PTR_XILINX, sizeof(int) * num_consensus[i].size(), &ext_buffer_num_consensus[i], &err);
        // buffer_valid_clusters[i] = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR | CL_MEM_EXT_PTR_XILINX, sizeof(int) * valid_clusters[i].size(), valid_clusters[i].data(), &err);
        buffer_elements[i] = clCreateBuffer(context[i>0], CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * elements[i].size(), elements[i].data(), &err);
        buffer_num_elements[i] = clCreateBuffer(context[i>0], CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * num_elements[i].size(), num_elements[i].data(), &err);
        buffer_num_valid_clusters[i] = clCreateBuffer(context[i>0], CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * num_valid_clusters[i].size(), num_valid_clusters[i].data(), &err);

        if (err != CL_SUCCESS) {
            std::cerr << "Failed to create buffers for kernel NUM_KERNELS" << i << ". Error code: " << err << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout<<"1111"<<std::endl;


    int current_cluster_id = 0;
    int current_index_id = 0;


//********************************************* Run encoding *********************************************

    
    for (int ii = 0; ii < NUM_BATCH/(mMAX_BATCH_SIZE*NUM_KERNELS_ENCODING) + 1; ii++) {
        
        
        cl_event kernel_events[NUM_KERNELS_ENCODING];
    
        for (int j = 0; j < NUM_KERNELS_ENCODING; j++) {    
            int batch_size = mMAX_BATCH_SIZE * (ii*NUM_KERNELS_ENCODING + j+1) <= NUM_BATCH ? 
                                    mMAX_BATCH_SIZE : NUM_BATCH - mMAX_BATCH_SIZE*(ii*NUM_KERNELS_ENCODING + j);

                                    std::cout <<"!!batch_size"<<batch_size<<std::endl;
            if (batch_size <= 0) {
                goto FINISH;
                break;
            }

            // cl_buffer_region region;
            // region.origin = mMAX_BATCH_SIZE * (ii * NUM_KERNELS_ENCODING + j) * sizeof(bitset_dhv) * MAX_NUM_SPECTRA;
            // region.size = batch_size * sizeof(bitset_dhv) * MAX_NUM_SPECTRA;  

            // cl_mem subBuffer = clCreateSubBuffer(buffer_encoded_spectra_hbm[j], CL_MEM_READ_WRITE, CL_BUFFER_CREATE_TYPE_REGION, &region, &err);

            // if (err != CL_SUCCESS) {
            //     std::cerr << "Failed to create sub-buffer" << std::endl;
            //     return EXIT_FAILURE;
            // }
            

            // err  = clSetKernelArg(kernels_encoding[j], 0, sizeof(cl_mem), &buffer_id[j]);
            // err |= clSetKernelArg(kernels_encoding[j], 0, sizeof(cl_mem), &buffer_level[j]);
            err |= clSetKernelArg(krnl_1, 0, sizeof(cl_mem), &buffer_id_level[j]);
            err |= clSetKernelArg(krnl_1, 1, sizeof(cl_mem), &buffer_peak_mz[j]);
            err |= clSetKernelArg(krnl_1, 2, sizeof(cl_mem), &buffer_peak_intensity[j]);
            err |= clSetKernelArg(krnl_1, 3, sizeof(cl_mem), &buffer_peak_count[j]);
            err |= clSetKernelArg(krnl_1, 4, sizeof(cl_mem), &buffer_num_spectra[j]);
            // err |= clSetKernelArg(kernels_encoding[j], 4, sizeof(cl_mem), &subBuffer);
            err |= clSetKernelArg(krnl_1, 5, sizeof(int), &batch_size);

            int arg_cnt1 = 6;
            for (int j_clu=0; j_clu < 1; j_clu++){
                err |= clSetKernelArg(krnl_1, arg_cnt1++, sizeof(cl_mem), &buffer_num_valid_clusters[j+j_clu]);
                err |= clSetKernelArg(krnl_1, arg_cnt1++, sizeof(cl_mem), &buffer_elements[j+j_clu]);
                err |= clSetKernelArg(krnl_1, arg_cnt1++, sizeof(cl_mem), &buffer_num_elements[j+j_clu]);
                err |= clSetKernelArg(krnl_1, arg_cnt1++, sizeof(cl_mem), &buffer_consensus[j+j_clu]);
            }
            

            int arg_cnt2 = 0;
            err |= clSetKernelArg(krnl_2, arg_cnt2++, sizeof(int), &batch_size);
            for (int j_clu=1; j_clu < N_CLUSTERING; j_clu++){
                err |= clSetKernelArg(krnl_1, arg_cnt1++, sizeof(cl_mem), &buffer_temp_krnl1[j_clu-1]);
                err |= clSetKernelArg(krnl_2, arg_cnt2++, sizeof(cl_mem), &buffer_temp_krnl2[j_clu-1]);

                err |= clSetKernelArg(krnl_2, arg_cnt2++, sizeof(cl_mem), &buffer_num_valid_clusters[j+j_clu]);
                err |= clSetKernelArg(krnl_2, arg_cnt2++, sizeof(cl_mem), &buffer_elements[j+j_clu]);
                err |= clSetKernelArg(krnl_2, arg_cnt2++, sizeof(cl_mem), &buffer_num_elements[j+j_clu]);
                err |= clSetKernelArg(krnl_2, arg_cnt2++, sizeof(cl_mem), &buffer_consensus[j+j_clu]);
            }


            
            if (err != CL_SUCCESS) {
                std::cerr << "Failed to set kernel arguments for kernel " << j << std::endl;
                return EXIT_FAILURE;
            }
            
            std::cout<< "E " << ii * NUM_KERNELS_ENCODING + j <<std::endl;
            
            // err  = clEnqueueWriteBuffer(q[j], buffer_id[j], CL_TRUE, 0, sizeof(bitset_dhv) * f, id, 0, NULL, NULL);
            // err |= clEnqueueWriteBuffer(q[j], buffer_level[j], CL_TRUE, 0, sizeof(bitset_dhv) * Q, level, 0, NULL, NULL);
            err |= clEnqueueWriteBuffer(q[j], buffer_id_level[j], CL_TRUE, 0, sizeof(bitset_dhv) * (f+Q), id_level, 0, NULL, NULL);

            // for (int ib=0; ib<batch_size; ib++){

            err |= clEnqueueWriteBuffer(q[j], buffer_peak_mz[j], CL_TRUE, 0, sizeof(int) * batch_size *  MAX_NUM_SPECTRA * MAX_PEAKS, peak_mz_buffer[(ii*NUM_KERNELS_ENCODING+j)].data(), 0, NULL, NULL);

            err |= clEnqueueWriteBuffer(q[j], buffer_peak_intensity[j], CL_TRUE, 0, sizeof(int) * batch_size * MAX_NUM_SPECTRA * MAX_PEAKS, peak_intensity_buffer[(ii*NUM_KERNELS_ENCODING+j)].data(), 0, NULL, NULL);

            err |= clEnqueueWriteBuffer(q[j], buffer_peak_count[j], CL_TRUE, 0, sizeof(int) * batch_size * MAX_NUM_SPECTRA, peak_count_buffer[(ii*NUM_KERNELS_ENCODING+j)].data(), 0, NULL, NULL);

            err |= clEnqueueWriteBuffer(q[j], buffer_num_spectra[j], CL_TRUE, 0, sizeof(int) * batch_size, &num_spectra_arr[(ii*NUM_KERNELS_ENCODING+j)*mMAX_BATCH_SIZE], 0, NULL, NULL);
            // }
            // err |= clEnqueueWriteBuffer(q[j], buffer_num_valid_clusters[j], CL_TRUE, 0, sizeof(int), &num_valid_clusters[(ii*NUM_KERNELS_ENCODING+j)], 0, NULL, NULL);

            
            if (err != CL_SUCCESS) {
                std::cerr << "Failed to write one or more buffers for kernel " << j << std::endl;
                return EXIT_FAILURE;
            }
            clFinish(q[0]);



            // err = clEnqueueNDRangeKernel(q[j], kernels_encoding[j], 1, NULL, &global_work_size, &local_size, 0, NULL, &kernel_events[j]);
            err = clEnqueueTask(q[j], krnl_1, 0, nullptr, nullptr);
            
            if (err != CL_SUCCESS) {
                std::cerr << "Failed to enqueue kernel " << 1 << "." << std::endl;
                return EXIT_FAILURE;
            }
            
            // clReleaseMemObject(subBuffer);

        }
        
        

        // err = clWaitForEvents(NUM_KERNELS_ENCODING, kernel_events);

        for(int i=0; i<NUM_KERNELS_ENCODING; i++) {
            clFinish(q[i]);
            // clReleaseEvent(kernel_events[i]);
            // clReleaseMemObject(subBuffer);
        }
    //********************************************* P2P*********************************************
    

        std::cout << "Transferring from FPGA-1 to FPGA-2..." << std::endl;
        int fd[N_CLUSTERING-1];
        cl_mem exported_buf[N_CLUSTERING-1];
        cl_event p2p_event[N_CLUSTERING-1];
        for (int i=0; i<N_CLUSTERING-1; ++i){
            err |= xcl::P2P::getMemObjectFd(buffer_temp_krnl2[i], &fd[i]);
            err |= xcl::P2P::getMemObjectFromFd(context[0], device[0], 0, fd[i], &exported_buf[i]);
            err |= clEnqueueCopyBuffer(q[0], buffer_temp_krnl1[i], exported_buf[i], 0, 0, sizeof(bitset_dhv)*(MAX_NUM_SPECTRA+1)*(mMAX_BATCH_SIZE+N_CLUSTERING-1/N_CLUSTERING), 0, nullptr,
                                            &p2p_event[i]);
        }
        if (err != CL_SUCCESS) {
            std::cerr << "Failed to getMemObjectFd " << fd << "." << std::endl;
            return EXIT_FAILURE;
        }
        for (int i=0; i<N_CLUSTERING-1; ++i){
            clWaitForEvents(1, &p2p_event[i]);
            clReleaseMemObject(exported_buf[i]);
        }

    //************************************ run kernel2 ******************************************

        err = clEnqueueTask(q[1], krnl_2, 0, nullptr, nullptr);
        
        if (err != CL_SUCCESS) {
            std::cerr << "Failed to enqueue kernel " << 2 << "." << std::endl;
            return EXIT_FAILURE;
        }

        clFinish(q[0]);
        clFinish(q[1]);


        if (NUM_BATCH <50){
            // Transfer data   FPGA --->  Host
            for (int j = 0; j < NUM_KERNELS; j++) {
                // err  = clEnqueueReadBuffer(q[j], buffer_valid_clusters[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, valid_clusters[j].data(), 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_num_valid_clusters[j], CL_TRUE, 0, sizeof(int), &num_valid_clusters[j], 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_elements[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA * CLUSTER_SIZE, elements[j].data(), 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_num_elements[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, num_elements[j].data(), 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_consensus[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, consensus[j].data(), 0, NULL, NULL);
                // err |= clEnqueueReadBuffer(q[j], buffer_num_consensus[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, num_consensus[j].data(), 0, NULL, NULL);
                if (err != CL_SUCCESS) {
                    std::cerr << "Failed to read from buffers for kernel " << j << "." << std::endl;
                    return EXIT_FAILURE;
                }
            }
            for (int j = 0; j < NUM_KERNELS; j++) {
                clFinish(q[j]);
            }

            
            
            // Write output file
            // for (int i = 0; i < NUM_KERNELS; i++) {
            //     std::stringstream filename;
            //     std::stringstream filename2;
            //     filename << "Final_norm_new_combined_test.txt";
            //     filename2 << "Final_serial_combined_test.txt";
            //     print_clusters(elements[i].data(), num_elements[i].data(), consensus[i].data(), valid_clusters[i].data(), num_valid_clusters[i], filename2.str().c_str(), current_cluster_id, current_index_id);
                
            //     print_clusters_temp(elements[i].data(), num_elements[i].data(), consensus[i].data(), valid_clusters[i].data(), num_valid_clusters[i], filename.str().c_str());

            //     current_cluster_id += num_valid_clusters[i];
            //     current_index_id += num_spectra_arr[(ii*NUM_KERNELS+i)]; 
                
            // }
        }
        

    
    }

FINISH:
//********************************************* Run clustering *********************************************

    /*for (int ii = 0; ii < NUM_BATCH/NUM_KERNELS; ii++) {
        cl_event kernel_events[NUM_KERNELS];
        
        for (int j = 0; j < NUM_KERNELS; j++) {
            
            err |= clSetKernelArg(kernels[j],  6, sizeof(cl_mem), &buffer_encoded_spectra[j]);
            err |= clSetKernelArg(kernels[j],  7, sizeof(int), &num_spectra_arr[(ii*NUM_KERNELS+j)]);
            err |= clSetKernelArg(kernels[j],  8, sizeof(cl_mem), &buffer_valid_clusters[j]);
            err |= clSetKernelArg(kernels[j],  9, sizeof(cl_mem), &buffer_num_valid_clusters[j]);
            err |= clSetKernelArg(kernels[j], 10, sizeof(cl_mem), &buffer_elements[j]);
            err |= clSetKernelArg(kernels[j], 11, sizeof(cl_mem), &buffer_num_elements[j]);
            err |= clSetKernelArg(kernels[j], 12, sizeof(cl_mem), &buffer_consensus[j]);
            err |= clSetKernelArg(kernels[j], 13, sizeof(cl_mem), &buffer_num_consensus[j]);
            int batch_size = 0;
            err |= clSetKernelArg(kernels_encoding[j], 5, sizeof(int), &batch_size);
            
            
            if (err != CL_SUCCESS) {
                std::cerr << "Failed to set kernel arguments for kernel " << j << std::endl;
                return EXIT_FAILURE;
            }
            
            std::cout << ii * NUM_KERNELS + j <<std::endl;
            

        err = clEnqueueWriteBuffer(q[j], buffer_num_valid_clusters[j], CL_TRUE, 0, sizeof(int), &num_valid_clusters[(ii*NUM_KERNELS+j)], 0, NULL, NULL);

        
        if (err != CL_SUCCESS) {
            std::cerr << "Failed to write one or more buffers for kernel " << j << std::endl;
            return EXIT_FAILURE;
        }

        size_t src_offset = (ii * NUM_KERNELS + j) * sizeof(bitset_dhv) * MAX_NUM_SPECTRA;

        size_t size_to_copy = sizeof(bitset_dhv) * num_spectra_arr[(ii*NUM_KERNELS+j)]; 
        cl_event copy_event;
        err = clEnqueueCopyBuffer(q[j],                      
                                buffer_encoded_spectra_hbm[0],  
                                buffer_encoded_spectra[j],      
                                src_offset,                          
                                0,                             
                                size_to_copy,                  
                                0,                             
                                NULL,                           
                                &copy_event);                   

        if (err != CL_SUCCESS) {
            std::cerr << "Failed to copy buffer. Error code: " << err << std::endl;
            return EXIT_FAILURE;
        }
                                
        err = clEnqueueNDRangeKernel(q[j], kernels[j], 1, NULL, &global_work_size, &local_size, 0, NULL, &kernel_events[j]);
            
            
            if (err != CL_SUCCESS) {
                std::cerr << "Failed to enqueue kernel " << j << "." << std::endl;
                return EXIT_FAILURE;
            }
            
            
        }
        
        err = clWaitForEvents(NUM_KERNELS, kernel_events);
        
        for(int i=0; i<NUM_KERNELS; i++) {
            clFinish(q[i]);
            clReleaseEvent(kernel_events[i]);
        }
        
        if (NUM_BATCH <50){
            // Transfer data   FPGA --->  Host
            for (int j = 0; j < NUM_KERNELS; j++) {
                err = clEnqueueReadBuffer(q[j], buffer_valid_clusters[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, valid_clusters[j].data(), 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_num_valid_clusters[j], CL_TRUE, 0, sizeof(int), &num_valid_clusters[j], 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_elements[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA * CLUSTER_SIZE, elements[j].data(), 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_num_elements[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, num_elements[j].data(), 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_consensus[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, consensus[j].data(), 0, NULL, NULL);
                err |= clEnqueueReadBuffer(q[j], buffer_num_consensus[j], CL_TRUE, 0, sizeof(int) * MAX_NUM_SPECTRA, num_consensus[j].data(), 0, NULL, NULL);
                if (err != CL_SUCCESS) {
                    std::cerr << "Failed to read from buffers for kernel " << j << "." << std::endl;
                    return EXIT_FAILURE;
                }
            }
            
            
            // Write output file
            for (int i = 0; i < NUM_KERNELS; i++) {
                std::stringstream filename;
                std::stringstream filename2;
                filename << "Final_norm_new_combined_test.txt";
                filename2 << "Final_serial_combined_test.txt";
                print_clusters(elements[i].data(), num_elements[i].data(), consensus[i].data(), valid_clusters[i].data(), num_valid_clusters[i], filename2.str().c_str(), current_cluster_id, current_index_id);
                
                print_clusters_temp(elements[i].data(), num_elements[i].data(), consensus[i].data(), valid_clusters[i].data(), num_valid_clusters[i], filename.str().c_str());

                current_cluster_id += num_valid_clusters[i];
                current_index_id += num_spectra_arr[(ii*NUM_KERNELS+i)]; 
                
            }
        }
        
        
        
        
    } */
    


    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    auto kernel_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time2);
    std::cout << "Total time: " << total_duration.count() << " ms\n";
    std::cout << "Clustering time: " << kernel_duration.count() << " ms\n";


    return 0;

}
                


// ============================ Helper Functions
// =========================================
static int load_file_to_memory(const char* filename, char** result);
cl_program xcl_import_binary_file(cl_device_id device_id, cl_context context, const char* xclbin_file_name) {
    int err;

    std::cout << "INFO: Importing " << xclbin_file_name << std::endl;

    if (access(xclbin_file_name, R_OK) != 0) {
        return nullptr;
        std::cerr << "ERROR: " << xclbin_file_name << "xclbin not available please build\n";
        exit(EXIT_FAILURE);
    }

    char* krnl_bin;
    const size_t krnl_size = load_file_to_memory(xclbin_file_name, &krnl_bin);
    std::cout << "INFO: Loaded file\n";

    cl_program program =
        clCreateProgramWithBinary(context, 1, &device_id, &krnl_size, (const unsigned char**)&krnl_bin, nullptr, &err);
    if ((!program) || (err != CL_SUCCESS)) {
        std::cout << "Error: Failed to create compute program from binary " << err << std::endl;
        std::cerr << "Test failed\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "INFO: Created Binary\n";

    err = clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        size_t len;
        char buffer[2048];

        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        std::cout << buffer << std::endl;
        std::cerr << "Error: Failed to build program executable!\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "INFO: Built Program\n";

    free(krnl_bin);

    return program;
}

static void* smalloc(size_t size) {
    void* ptr;

    ptr = malloc(size);

    if (ptr == nullptr) {
        std::cerr << "Error: Cannot allocate memory\n";
        exit(EXIT_FAILURE);
    }
    return ptr;
}
static int load_file_to_memory(const char* filename, char** result) {
    unsigned int size;

    FILE* _f = fopen(filename, "rb");
    if (_f == nullptr) {
        *result = nullptr;
        std::cerr << "Error: Could not read file" << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    fseek(_f, 0, SEEK_END);
    size = ftell(_f);
    fseek(_f, 0, SEEK_SET);

    *result = (char*)smalloc(sizeof(char) * (size + 1));

    if (size != fread(*result, sizeof(char), size, _f)) {
        free(*result);
        std::cerr << "Error: read of kernel failed\n";
        exit(EXIT_FAILURE);
    }

    fclose(_f);
    (*result)[size] = 0;

    return size;
}
