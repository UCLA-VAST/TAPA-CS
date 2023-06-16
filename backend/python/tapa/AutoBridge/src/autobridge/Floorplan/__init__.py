import logging
import os

from typing import Dict, List, Tuple
from tapa.AutoBridge.src.autobridge.Floorplan.Partition import partition
from tapa.AutoBridge.src.autobridge.Floorplan.IterativeBipartion import iterative_bipartition, multi_fpga_iterative_bipartition
from tapa.AutoBridge.src.autobridge.Floorplan.Utilities import (
  print_pre_assignment,
  print_vertex_areas,
  get_eight_way_partition_slots,
  get_four_way_partition_slots,
  get_actual_usage,
)
from tapa.AutoBridge.src.autobridge.Opt.DataflowGraph import Vertex, DataflowGraph
from tapa.AutoBridge.src.autobridge.Opt.Slot import Slot
from tapa.AutoBridge.src.autobridge.Opt.SlotManager import SlotManager, Dir

_logger = logging.getLogger('autobridge')
cli_logger = logging.getLogger('general')


def get_floorplan(
  graph: DataflowGraph,
  slot_manager: SlotManager,
  grouping_constraints_in_str: List[List[str]],
  pre_assignments_in_str: Dict[str, str],
  floorplan_strategy: str = 'HALF_SLR_LEVEL_FLOORPLANNING',
  threshold_for_iterative: int = 200,
  floorplan_opt_priority: str = 'AREA_PRIORITIZED',
  min_area_limit: float = 0.65,
  max_area_limit: float = 0.85,
  min_slr_width_limit: int = 10000,
  max_slr_width_limit: int = 15000,
  max_search_time: int = 600,
  hbm_port_v_name_list: List[str] = []
) -> Tuple[Dict[Vertex, Slot], List[Slot]]:
  """
  main entrance of the floorplan part
  return (1) mapping from vertex to slot
  (2) a list of all potential slots
  Note that an empty slot will not be in (1), but will occur in (2)
  """
  # get initial v2s
  cli_logger.info("we are in get_floorplan")
  init_slot = slot_manager.getInitialSlot()
  init_v2s = {v : init_slot for v in graph.getAllVertices()}

  actual_usage = get_actual_usage(init_v2s.keys(), slot_manager.getInitialSlot())
  if max_area_limit < actual_usage:
    max_area_limit = actual_usage + 0.1
    cli_logger.warning('The specified max_area_limit is less than the actual usage of the design: %f. '
                       'Adjust max_area_limit to %f', actual_usage, max_area_limit)
  if min_area_limit < actual_usage:
    min_area_limit = actual_usage
    cli_logger.warning('Adjust the min_area_limit to the actual usage of the design: %f', actual_usage)

  cli_logger.info('')
  cli_logger.info('Floorplan parameters:')
  cli_logger.info('')
  cli_logger.info('  floorplan_strategy: %s', floorplan_strategy)
  cli_logger.info('  threshold for switching to iterative partitioning: %d', threshold_for_iterative)
  cli_logger.info('  floorplan_opt_priority: %s', floorplan_opt_priority)
  cli_logger.info('  min_area_limit: %f', min_area_limit)
  cli_logger.info('  max_area_limit: %f', max_area_limit)
  cli_logger.info('  min_slr_width_limit: %d', min_slr_width_limit)
  cli_logger.info('  max_slr_width_limit: %d', max_slr_width_limit)
  cli_logger.info('  max_search_time per solving: %d', max_search_time)
  cli_logger.info('')
  cli_logger.info('Start floorplanning, please check the log for the progress...\n')

  # get grouping constraints of Vertex
  grouping_constraints: List[List[Vertex]] = [
    [graph.getVertex(v_name) for v_name in v_name_group]
      for v_name_group in grouping_constraints_in_str
  ]
  _logger.info(f'The following modules are grouped to the same location:')
  for grouping in grouping_constraints_in_str:
    _logger.info('    ' + ', '.join(grouping))

  # get pre_assignment in Vertex
  pre_assignments = { graph.getVertex(v_name) : slot_manager.createSlot(pblock)
    for v_name, pblock in pre_assignments_in_str.items()
  }

  # get the hbm port vertices
  hbm_port_v_list = [graph.getVertex(v_name) for v_name in hbm_port_v_name_list]
  for v_name in hbm_port_v_name_list:
    _logger.info('Binding of HBM vertex %s is subject to change', v_name)

  print_pre_assignment(pre_assignments)
  print_vertex_areas(init_v2s.keys(), slot_manager.getInitialSlot())
  params = {
    'floorplan_opt_priority': floorplan_opt_priority,
    'min_area_limit': min_area_limit,
    'max_area_limit': max_area_limit,
    'min_slr_width_limit': min_slr_width_limit,
    'max_slr_width_limit': max_slr_width_limit,
    'max_search_time': max_search_time,
    'hbm_port_v_list': hbm_port_v_list,
  }

  # choose floorplan method
  num_vertices = len(graph.getAllVertices())
  v2s: Dict[Vertex, Slot] = {}

  # if user specifies floorplan methods
  if floorplan_strategy == 'SLR_LEVEL_FLOORPLANNING':
    _logger.info(f'user specifies to floorplan into SLR-level slots')
    v2s = partition(
      init_v2s, slot_manager, grouping_constraints, pre_assignments, partition_method='FOUR_WAY_PARTITION', **params
    )

    if v2s:
      return v2s, get_four_way_partition_slots(slot_manager)
    else:
      return None, None
  # cli_logger.info("iterative bipartition from single")
  # v2s = iterative_bipartition(init_v2s, slot_manager, grouping_constraints, pre_assignments)
  # cli_logger.info(v2s)
  elif floorplan_strategy == 'QUICK_FLOORPLANNING':
    _logger.info(f'user specifies to prioritize speed')
    cli_logger.info("we chose quick floorplanning and came here")
    v2s = iterative_bipartition(init_v2s, slot_manager, grouping_constraints, pre_assignments)
    cli_logger.info(v2s)
    for vertex in v2s:
      cli_logger.info(vertex.name)
      cli_logger.info(v2s[vertex].getName())
    if v2s:
      return v2s, get_eight_way_partition_slots(slot_manager)
    else:
      return None, None

  else:
    if floorplan_strategy != 'HALF_SLR_LEVEL_FLOORPLANNING':
      raise NotImplementedError('unrecognized floorplan strategy %s', floorplan_strategy)

  # empirically select the floorplan method
  if num_vertices < threshold_for_iterative:
    _logger.info(f'There are {num_vertices} vertices in the design, use eight way partition')

    if num_vertices > 100:
      _logger.warning('Over 100 vertices. May have a long solving time. Reduce threshold_for_iterative to skip to iterative bi-partitioning.')
    # problem is here
    v2s = partition(
      init_v2s, slot_manager, grouping_constraints, pre_assignments, partition_method='EIGHT_WAY_PARTITION', **params
    )
    if v2s:
      return v2s, get_eight_way_partition_slots(slot_manager)
    else:
      _logger.warning(f'Please check if any function in the design is too large')

  _logger.info(f'Use four-way partition because eight-way partition failed or there are too many vertices ({num_vertices})')
  v2s = partition(
    init_v2s, slot_manager, grouping_constraints, pre_assignments, partition_method='FOUR_WAY_PARTITION', **params
  )
  if v2s:
    final_v2s = iterative_bipartition(v2s, slot_manager, grouping_constraints, pre_assignments, partition_order=[Dir.vertical])

    if final_v2s:
      return final_v2s, get_eight_way_partition_slots(slot_manager)
    else:
      return v2s, get_four_way_partition_slots(slot_manager)

  _logger.error(f'AutoBridge fails to partition the design at the SLR level. Either the design is too large, or the functions/modules are too large.')
  return None, None


def get_multi_fpga_floorplan(
  graph: DataflowGraph,
  slot_managers: List[SlotManager], 
  multi_fpga: int,
  grouping_constraints_in_str: List[List[str]],
  pre_assignments_in_str: Dict[str, str],
  floorplan_strategy: str = 'HALF_SLR_LEVEL_FLOORPLANNING',
  threshold_for_iterative: int = 200,
  floorplan_opt_priority: str = 'AREA_PRIORITIZED',
  min_area_limit: float = 0.65,
  max_area_limit: float = 0.85,
  min_slr_width_limit: int = 10000,
  max_slr_width_limit: int = 15000,
  max_search_time: int = 600,
  hbm_port_v_name_list: List[str] = []
) -> Tuple[Dict[Vertex, Slot], List[Slot]]:
  """
  main entrance of the multi_fpga floorplan part
  return (1) mapping from vertex to slot
  (2) a list of all potential slots
  Note that an empty slot will not be in (1), but will occur in (2)
  """
  # cli_logger.info("slot managers")
  # cli_logger.info(len(slot_managers))
  for i in range(len(slot_managers)):
    init_slot = slot_managers[i].getInitialSlot()
    init_v2s = {v: init_slot for v in graph.getAllVertices()}
    actual_usage = get_actual_usage(init_v2s.keys(), slot_managers[i].getInitialSlot())
    if max_area_limit < actual_usage:
      max_area_limit = actual_usage + 0.1
      cli_logger.warning('The specified max_area_limit is less than the actual usage of the design: %f. '
                        'Adjust max_area_limit to %f', actual_usage, max_area_limit)
    if min_area_limit < actual_usage:
      min_area_limit = actual_usage
      cli_logger.warning('Adjust the min_area_limit to the actual usage of the design: %f', actual_usage)
  cli_logger.info('')
  cli_logger.info('Floorplan parameters:')
  cli_logger.info('')
  cli_logger.info('  number of FPGAs: %d', multi_fpga)
  cli_logger.info('  floorplan_strategy: %s', floorplan_strategy)
  cli_logger.info('  threshold for switching to iterative partitioning: %d', threshold_for_iterative)
  cli_logger.info('  floorplan_opt_priority: %s', floorplan_opt_priority)
  cli_logger.info('  min_area_limit: %f', min_area_limit)
  cli_logger.info('  max_area_limit: %f', max_area_limit)
  cli_logger.info('  min_slr_width_limit: %d', min_slr_width_limit)
  cli_logger.info('  max_slr_width_limit: %d', max_slr_width_limit)
  cli_logger.info('  max_search_time per solving: %d', max_search_time)
  cli_logger.info('')
  cli_logger.info('Start floorplanning, please check the log for the progress...\n')
  grouping_constraints: List[List[Vertex]] = [
    [graph.getVertex(v_name) for v_name in v_name_group]
      for v_name_group in grouping_constraints_in_str
  ]
  for grouping in grouping_constraints_in_str:
    _logger.info('    ' + ', '.join(grouping))
  pre_assignments = []
  for i in range(multi_fpga):
    pre_assignments.append({ graph.getVertex(v_name) : slot_managers[i].createSlot(pblock)
      for v_name, pblock in pre_assignments_in_str.items()
    })
  hbm_port_v_list = [graph.getVertex(v_name) for v_name in hbm_port_v_name_list]
  for v_name in hbm_port_v_name_list:
    _logger.info('Binding of HBM vertex %s is subject to change', v_name)

  
  # for i in range(multi_fpga):
  #   cli_logger.info("FPGA %d", i+1)
  #   print_pre_assignment(pre_assignments[i])
  #   print_vertex_areas(init_v2s.keys(), slot_managers[i].getInitialSlot())
  params = {
    'floorplan_opt_priority': floorplan_opt_priority,
    'min_area_limit': min_area_limit,
    'max_area_limit': max_area_limit,
    'min_slr_width_limit': min_slr_width_limit,
    'max_slr_width_limit': max_slr_width_limit,
    'max_search_time': max_search_time,
    'hbm_port_v_list': hbm_port_v_list,
  }
  # cli_logger.info(graph.getAllVertices())
  # for vertex in graph.getAllVertices():
  #   cli_logger.info(vertex.name)
  num_vertices = len(graph.getAllVertices())
  # cli_logger.info("num_vertices")
  # cli_logger.info(num_vertices)
  v2s: Dict[Vertex, Slot] = {}
  # cli_logger.info("floorplan strategy")
  # cli_logger.info(floorplan_strategy)
  floorplan_strategy = 'QUICK_FLOORPLANNING'
  # v2s = multi_fpga_iterative_bipartition(init_v2s, slot_managers, grouping_constraints, pre_assignments)
  v2s = iterative_bipartition(init_v2s, slot_managers[0], grouping_constraints, pre_assignments[0])
  cli_logger.info("iterative bipartition v2s")
  cli_logger.info(v2s)
  for vertex in v2s:
    cli_logger.info(vertex.name)
    cli_logger.info(v2s[vertex].getName())
  return v2s, get_eight_way_partition_slots(slot_managers[0])