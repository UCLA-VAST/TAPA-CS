puts "applying partitioning constraints generated by tapac"
write_checkpoint before_add_floorplan_constraints.dcp

# begin defining a slot
create_pblock CR_X0Y4_To_CR_X3Y7
resize_pblock CR_X0Y4_To_CR_X3Y7 -add CLOCKREGION_X0Y4:CLOCKREGION_X3Y7
# remove the reserved clock regions for the Vitis infra
resize_pblock CR_X0Y4_To_CR_X3Y7 -remove CLOCKREGION_X7Y0:CLOCKREGION_X7Y15


# begin defining a slot
create_pblock CR_X0Y0_To_CR_X3Y3
resize_pblock CR_X0Y0_To_CR_X3Y3 -add CLOCKREGION_X0Y0:CLOCKREGION_X3Y3
# remove the reserved clock regions for the Vitis infra
resize_pblock CR_X0Y0_To_CR_X3Y3 -remove CLOCKREGION_X7Y1:CLOCKREGION_X7Y11


# begin defining a slot
create_pblock CR_X4Y4_To_CR_X7Y7
resize_pblock CR_X4Y4_To_CR_X7Y7 -add CLOCKREGION_X4Y4:CLOCKREGION_X7Y7
# remove the reserved clock regions for the Vitis infra
resize_pblock CR_X4Y4_To_CR_X7Y7 -remove CLOCKREGION_X7Y1:CLOCKREGION_X7Y11


# begin defining a slot
create_pblock CR_X4Y0_To_CR_X7Y3
resize_pblock CR_X4Y0_To_CR_X7Y3 -add CLOCKREGION_X4Y0:CLOCKREGION_X7Y3
# remove the reserved clock regions for the Vitis infra
resize_pblock CR_X4Y0_To_CR_X7Y3 -remove CLOCKREGION_X7Y1:CLOCKREGION_X7Y11

add_cells_to_pblock [get_pblocks CR_X4Y0_To_CR_X7Y3] [get_cells -regex {
  level0_i/ulp/.*/inst/.*/Control_0
  level0_i/ulp/.*/inst/.*/ProcElem_0
  level0_i/ulp/.*/inst/.*/ProcElem_3
  level0_i/ulp/.*/inst/.*/UpdateHandler_0
  level0_i/ulp/.*/inst/.*/UpdateHandler_1
  level0_i/ulp/.*/inst/.*/UpdateHandler_3
  level0_i/ulp/.*/inst/.*/VertexMem_0
  level0_i/ulp/.*/inst/.*/VertexRouterR1_0
  level0_i/ulp/.*/inst/.*/VertexRouterR2_0
  level0_i/ulp/.*/inst/.*/degrees__m_axi
  level0_i/ulp/.*/inst/.*/rankings__m_axi
  level0_i/ulp/.*/inst/.*/tmps__m_axi
  level0_i/ulp/.*/inst/.*/edge_req_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/edge_req_3/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/edge_resp_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/edge_resp_3/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/num_updates_0/.*.unit
  level0_i/ulp/.*/inst/.*/num_updates_1/.*.unit
  level0_i/ulp/.*/inst/.*/num_updates_2/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/num_updates_3/.*.unit
  level0_i/ulp/.*/inst/.*/scatter_phase_vertex_req/.*.unit
  level0_i/ulp/.*/inst/.*/task_req_0/.*.unit
  level0_i/ulp/.*/inst/.*/task_req_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/task_req_2/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/task_req_3/.*.unit
  level0_i/ulp/.*/inst/.*/task_resp_0/.*.unit
  level0_i/ulp/.*/inst/.*/task_resp_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/task_resp_2/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/task_resp_3/.*.unit
  level0_i/ulp/.*/inst/.*/update_config_0/.*.unit
  level0_i/ulp/.*/inst/.*/update_config_1/.*.unit
  level0_i/ulp/.*/inst/.*/update_config_2/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_config_3/.*.unit
  level0_i/ulp/.*/inst/.*/update_mm2pe_0/.*.unit
  level0_i/ulp/.*/inst/.*/update_mm2pe_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_mm2pe_3/.*.unit
  level0_i/ulp/.*/inst/.*/update_pe2mm_0/.*.unit
  level0_i/ulp/.*/inst/.*/update_pe2mm_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_pe2mm_3/.*.unit
  level0_i/ulp/.*/inst/.*/update_phase_0/.*.unit
  level0_i/ulp/.*/inst/.*/update_phase_1/.*.unit
  level0_i/ulp/.*/inst/.*/update_phase_2/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_phase_3/.*.unit
  level0_i/ulp/.*/inst/.*/update_read_addr_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_addr_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_addr_3/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_data_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_data_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_data_3/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_req_0/.*.unit
  level0_i/ulp/.*/inst/.*/update_req_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_req_3/.*.unit
  level0_i/ulp/.*/inst/.*/update_write_addr_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_addr_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_addr_3/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_data_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_data_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_data_3/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r0_0/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r0_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r1_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r1_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r2_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r2_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r0_0/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r0_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r1_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r1_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r2_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r2_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r0_0/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r0_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r1_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r1_1/.*.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r2_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r2_1/.*.unit
} ]
add_cells_to_pblock [get_pblocks CR_X0Y0_To_CR_X3Y3] [get_cells -regex {
  level0_i/ulp/.*/inst/.*/EdgeMem_0
  level0_i/ulp/.*/inst/.*/EdgeMem_1
  level0_i/ulp/.*/inst/.*/EdgeMem_2
  level0_i/ulp/.*/inst/.*/EdgeMem_3
  level0_i/ulp/.*/inst/.*/ProcElem_2
  level0_i/ulp/.*/inst/.*/UpdateHandler_2
  level0_i/ulp/.*/inst/.*/UpdateMem_0
  level0_i/ulp/.*/inst/.*/UpdateMem_1
  level0_i/ulp/.*/inst/.*/UpdateMem_2
  level0_i/ulp/.*/inst/.*/UpdateMem_3
  level0_i/ulp/.*/inst/.*/edges_0__m_axi
  level0_i/ulp/.*/inst/.*/edges_1__m_axi
  level0_i/ulp/.*/inst/.*/edges_2__m_axi
  level0_i/ulp/.*/inst/.*/edges_3__m_axi
  level0_i/ulp/.*/inst/.*/updates_0__m_axi
  level0_i/ulp/.*/inst/.*/updates_1__m_axi
  level0_i/ulp/.*/inst/.*/updates_2__m_axi
  level0_i/ulp/.*/inst/.*/updates_3__m_axi
  level0_i/ulp/.*/inst/.*/edge_req_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/edge_req_1/inst\\[2]\\.unit
  level0_i/ulp/.*/inst/.*/edge_req_2/.*.unit
  level0_i/ulp/.*/inst/.*/edge_req_3/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/edge_resp_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/edge_resp_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/edge_resp_2/.*.unit
  level0_i/ulp/.*/inst/.*/edge_resp_3/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/num_updates_2/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/task_req_2/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/task_resp_2/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_config_2/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_mm2pe_2/.*.unit
  level0_i/ulp/.*/inst/.*/update_pe2mm_2/.*.unit
  level0_i/ulp/.*/inst/.*/update_phase_2/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_addr_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_addr_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_addr_2/.*.unit
  level0_i/ulp/.*/inst/.*/update_read_addr_3/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_data_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_data_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_read_data_2/.*.unit
  level0_i/ulp/.*/inst/.*/update_read_data_3/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_req_2/.*.unit
  level0_i/ulp/.*/inst/.*/update_write_addr_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_addr_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_addr_2/.*.unit
  level0_i/ulp/.*/inst/.*/update_write_addr_3/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_data_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_data_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_write_data_2/.*.unit
  level0_i/ulp/.*/inst/.*/update_write_data_3/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r2_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r2_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r2_0/inst\\[0]\\.unit
} ]
add_cells_to_pblock [get_pblocks CR_X4Y4_To_CR_X7Y7] [get_cells -regex {
  level0_i/ulp/.*/inst/.*/ProcElem_1
  level0_i/ulp/.*/inst/.*/edge_req_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/edge_resp_1/inst\\[2]\\.unit
  level0_i/ulp/.*/inst/.*/task_req_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/task_resp_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_mm2pe_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/update_pe2mm_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/update_req_1/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_mm2pe_r1_0/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_pe2mm_r1_0/inst\\[0]\\.unit
  level0_i/ulp/.*/inst/.*/vertex_req_r1_0/inst\\[0]\\.unit
} ]
add_cells_to_pblock [get_pblocks CR_X0Y4_To_CR_X3Y7] [get_cells -regex {
  level0_i/ulp/.*/inst/.*/edge_req_1/inst\\[1]\\.unit
  level0_i/ulp/.*/inst/.*/edge_resp_1/inst\\[1]\\.unit
} ]
foreach pblock [get_pblocks -regexp CR_X\\d+Y\\d+_To_CR_X\\d+Y\\d+] {
  if {[get_property CELL_COUNT $pblock] == 0} {
    puts "WARNING: delete empty pblock $pblock "
    delete_pblocks $pblock
  }
}
foreach pblock [get_pblocks] {
  report_utilization -pblocks $pblock
}