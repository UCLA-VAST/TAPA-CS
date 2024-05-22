# TAPA-CS

TAPA-CS is a task-parallel dataflow programming framework built upon [TAPA](https://tapa.readthedocs.io/en/release/) which automatically partitions and compiles a large design across a cluster of FPGAs while achieving high frequency and throughput. TAPA-CS has three main contributions:
- Allows users to leverage virtually "unlimited" accelerator fabric, high-bandwidth memory (HBM), and on-chip memory.
- Given as input a large design, TAPA-CS automatically partitions the design to map to multiple FPGAs, while ensuring congestion control, resource balancing, and overlapping of communication and computation.
- Couples coarse-grained floor-planning with interconnect pipelining at the inter- and intra-FPGA levels to ensure high frequency.

  
![alt text](https://github.com/nehaprakriya/tapa/blob/main/tapa-cs-github.png)

## Getting Started

+ Installation:
  - Install from source by cloning this repository and following the installation instructions [here](https://tapa.readthedocs.io/en/release/installation.html)
  - For RDMA-based inter-FPGA communication, please install [AlveoLink](https://github.com/Xilinx/AlveoLink/tree/main) and build the network IPs. Examples for using AlveoLink can be found [here](https://github.com/Xilinx/AlveoLink/tree/main/examples/network/roce_v2/generator_collector).
  - For PCIe-based P2P inter-FPGA communication, please follow the instructions [here](https://xilinx.github.io/XRT/master/html/p2p.html) to setup P2P. Examples for using P2P can be found [here](https://github.com/Xilinx/Vitis_Accel_Examples/tree/main/host_xrt/p2p_fpga2fpga_xrt).

+ Supported boards: Alveo U55C, Alveo U280, Alveo U250
+ Supported Vitis versions: Require Vitis version 2022.1 to build AlveoLink IPs. Support versions >=2020.2 if using PCIe-based P2P.
+ TAPA-CS uses the same backend as the TAPA compiler. Examples of running the TAPA compiler can be found [here](https://tapa.readthedocs.io/en/release/getting_started.html#). Each application in the regression folder also contains the run_tapa.sh files which can be used to launch TAPA. 
+ To use TAPA-CS, pass the --multi-fpga N option to the TAPA compiler. 


## TAPA-CS Publications
+ Neha Prakriya, Yuze Chi, Suhail Basalama, Linghao Song, and Jason Cong. 2024. TAPA-CS: Enabling Scalable Accelerator Design on Distributed HBM-FPGAs. In Proceedings of the 29th ACM International Conference on Architectural Support for Programming Languages and Operating Systems, Volume 3 (ASPLOS '24), Vol. 3. Association for Computing Machinery, New York, NY, USA, 966–980. https://doi.org/10.1145/3620666.3651347.

## Successful Cases
+ Tianqi Zhang, Neha Prakriya, Sumukh Pinge, Jason Cong, and Tajana Rosing. 2024. SpectraFlux: Harnessing the Flow of Multi-FPGA in Mass Spectrometry Clustering. In 61st ACM/IEEE Design Automation Conference (DAC ’24), June 23–27, 2024, San Francisco, CA, USA. ACM, New York, NY, USA, 6 pages. https://doi.org/10.1145/3649329.3657354
  
    - Code for the P2P and ethernet versions are available at the following path: tapa/regression/spectraflux


