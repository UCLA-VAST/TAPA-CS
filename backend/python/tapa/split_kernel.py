from tapa.AutoBridge.src.autobridge.Opt.DataflowGraph import Edge, Vertex
from tapa.AutoBridge.src.autobridge.Opt.Slot import Slot
import tapa.core
import logging
from typing import Dict, List


_logger = logging.getLogger().getChild(__name__)

def sanitize_names(name:str):
    return name.replace('TASK_VERTEX_', '')

def add_tasks(input_file:str, file1, file2, program:tapa.core.Program):
    with open(input_file, 'r') as top:
        lines = top.readlines()
        for line in lines:
            if 'void ' not in line:
                file1.write(line)
                file2.write(line)
            elif 'void ' in line and 'void '+program.top not in line:
                file1.write(line.replace(line.split(' ')[1], line.split(' ')[1]+'_1'))
                file2.write(line.replace(line.split(' ')[1], line.split(' ')[1]+'_2'))
            else:
                break
    file1.write('void '+program.top+'_1(\n')
    file2.write('void '+program.top+'_2(\n')

def add_ports(input_file:str, file1, file2, device_1_items, device_2_items, program:tapa.core.Program):
    device_1_names = []
    for i in range(len(device_1_items)):
        device_1_names.append(device_1_items[i].name)
    _logger.info(device_1_names)
    device_2_names = []
    for i in range(len(device_2_items)):
        device_2_names.append(device_2_items[i].name)
    device_1_names = '\t'.join(device_1_names)
    device_2_names = '\t'.join(device_2_names)
    for port in program.toplevel_ports:
        width = port.width
        name = port.name
        ctype = port.ctype
        # we need to write tapa::mmap<ctype> port.name
        if port.name+'__m_axi' in device_1_names and str(port.cat).split('.')[1]=='MMAP':
            file1.write('tapa::mmap<'+ctype[:-1]+' '+port.name+',\n')
        elif port.name+'__m_axi' in device_2_names and str(port.cat).split('.')[1]=='MMAP':
            file2.write('tapa::mmap<'+ctype[:-1]+' '+port.name+',\n')
    
# def add_inter_fpga_comm(input_file:str, file1, file2, device_1_items, device_2_items, program:tapa.core.Program):
#     # get which ones are being sent out of the board and which are being sent into the board and write those into the args
#     _logger.info("todo")

# def add_invokes(input_file:str, file1, file2, device_1_items, device_2_items, program:tapa.core.Program):
    
def find_partitions(device_1_items, device_2_items):
    device_1_names = []
    for i in range(len(device_1_items)):
        device_1_names.append(device_1_items[i].name)
    _logger.info(device_1_names)
    device_2_names = []
    for i in range(len(device_2_items)):
        device_2_names.append(device_2_items[i].name)
    device_1_names = '\t'.join(device_1_names)
    device_2_names = '\t'.join(device_2_names)
    partition_1_in = []
    partition_1_out = []
    partition_2_in = []
    partition_2_out = []
    for vertex in device_1_items:
        in_edges = vertex.in_edges
        out_edges = vertex.out_edges
        for in_edge in in_edges:
            if in_edge.src.name in device_2_names:
                partition_1_in.append(vertex.name)
        for out_edge in out_edges:
            if out_edge.dst.name in device_2_names:
                partition_1_out.append(vertex.name)
    for vertex in device_2_items:
        in_edges = vertex.in_edges
        out_edges = vertex.out_edges
        for in_edge in in_edges:
            if in_edge.src.name in device_1_names:
                partition_2_in.append(vertex.name)
        for out_edge in out_edges:
            if out_edge.dst.name in device_1_names:
                partition_2_out.append(vertex.name)
    return partition_1_in, partition_1_out, partition_2_in, partition_2_out


def split_kernel(v2s:Dict[Vertex, Slot], slot_list:List[Slot], program:tapa.core.Program, input_file):
    device_1_items = []
    device_2_items = []
    for vertex in v2s:
        if int(v2s[vertex].getName()[15])<=7:
            device_1_items.append(vertex)
        else:
            device_2_items.append(vertex)
    for vertex in device_1_items:
        _logger.info(vertex.name)
    for vertex in device_2_items:
        _logger.info(vertex.name)
    file1 = open("kernel_1.cpp", 'w+')
    file2 = open("kernel_2.cpp", 'w+')

    add_tasks(input_file, file1, file2, program)
    add_ports(input_file, file1, file2, device_1_items, device_2_items, program)
    partition_1_in, partition_1_out, partition_2_in, partition_2_out = find_partitions(device_1_items, device_2_items)
    _logger.info(partition_1_in)
    _logger.info(partition_1_out)
    _logger.info(partition_2_in)
    _logger.info(partition_2_out)
    # add_inter_fpga_comm(input_file, file1, file2, device_1_items, device_2_items, program)

def split_kernel_1(v2s:Dict[Vertex, Slot] , slot_list:List[Slot], program:tapa.core.Program, input_file):
    _logger.info("slot list from split kernel")
    # _logger.info(slot_list)
    for slots in slot_list:
        _logger.info(slots.getName())
    _logger.info(program.top)
    _logger.info(program.tasks)
    _logger.info("getting program cpp dir")
    _logger.info(program.cpp_dir)
    tasks = []
    for task in program.tasks:
        _logger.info(program.get_cpp(task.name))
        _logger.info(task.name)
        tasks.append(task.name)
    # device 1: X0Y0-X7Y7
    # device 2: X0Y7-X7Y15
    device_1 = []
    # device_1_args = []
    device_2 = []
    for vertex in v2s:
        _logger.info(vertex.name)
        _logger.info(v2s[vertex].getName())
        _logger.info("partition to")
        # if int(v2s[vertex].getName()[15])
        if int(v2s[vertex].getName()[15])<=7:
            # if 'TASK_VERTEX' in vertex.name:
            # sanitized_name = vertex.name[12:]
            # sanitized_name = sanitized_name[:2]
            device_1.append(vertex.name[12:])
            # _logger.info(len(vertex.in_edges))
            if len(vertex.in_edges)>0:
                for i in range(len(vertex.in_edges)):
                    _logger.info(vertex.in_edges[i].name)
            _logger.info("added %s to device 1", vertex.name)
        else:
            # if 'TASK_VERTEX' in vertex.name:
            device_2.append(vertex.name[12:])
            if len(vertex.in_edges)>0:
                for i in range(len(vertex.in_edges)):
                    _logger.info(vertex.in_edges[i].name)
            # _logger.info(vertex.in_edges[0].name)
            _logger.info("added %s to device 2", vertex.name)
    for port in program.toplevel_ports:
        _logger.info(port.cat)
        _logger.info(port.name)
        _logger.info(port.width)
        _logger.info(port.ctype)
    file1 = open('kernel_1.cpp', 'w+')
    file2 = open('kernel_2.cpp', 'w+')
    with open(input_file, 'r') as top:
        lines = top.readlines()
        for line in lines:
            if 'void '+program.top not in line:
                file1.write(line)
                file2.write(line)
            else:
                break

    file1.write('void '+program.top+'_1(')
    file2.write('void '+program.top+'_2(')
    numports = len(program.toplevel_ports)
    count=1
    device_1_items = '\t'.join(device_1)
    device_2_items = '\t'.join(device_2)
    _logger.info("device_1_items")
    _logger.info(device_1_items)
    _logger.info("device_2_items")
    _logger.info(device_2_items)
    for port in program.toplevel_ports:
        cat_type = str(port.cat).split('.')[1]
        width = port.width
        name = port.name
        _logger.info(name)
        ctype = port.ctype
        if cat_type=='MMAP':
            if port.name+'__m_axi' in device_1_items:
                _logger.info(port.name)
                toadd = 'tapa::mmap<INTERFACE_WIDTH> '+name+',\n'
                file1.write(toadd)
            elif port.name+'__m_axi' in device_2_items:
                toadd = 'tapa::mmap<INTERFACE_WIDTH> '+name+',\n'
                file2.write(toadd)
        elif cat_type=='SCALAR':
            toadd = ctype+' '+name+',\n'
            file1.write(toadd)
            file2.write(toadd)
        # elif count==numports:
    file1.write('tapa::ostream<float> &out_board,\n')
    file1.write('tapa::istream<float> &in_board){\n')
    file2.write('tapa::ostream<float> &out_board,\n')
    file2.write('tapa::istream<float> &in_board){\n')
    _logger.info(device_1_items)
    _logger.info(device_2_items)
    for elem in device_1:
        if 'axi' in elem or 'external_controller' in elem:
            device_1.remove(elem)
    for elem in device_2:
        if 'axi' in elem or 'external_controller' in elem:
            device_2.remove(elem)
    device_1_items = '\t'.join(device_1)
    device_2_items = '\t'.join(device_2)
    _logger.info(device_1_items)
    _logger.info(device_2_items)
    # TODO need something for the strweams in between the args and middle


    with open(input_file, 'r') as top:
        lines = top.readlines()
        for line in lines:
            if 'tapa::stream' in line:
                file1.write(line)
                file2.write(line)

    file1.write('tapa::task()\n')
    file2.write('tapa::task()\n')
    with open(input_file, 'r') as top:
        lines = top.readlines()
        for line in lines:
            if '.invoke' in line:
                line = line.split('(')
                line = line[1].split(',')
                _logger.info(line)
                if line[0][1:] in device_1_items:
                    # device_1_list = device_1_items.split(line[0])
                    device_1_items = device_1_items.replace(line[0], "", 1)
                    # device_1_items =''
                    # for elem in device_1_list:
                    #     device_1_items+=elem
                    _logger.info(line[0])
                    _logger.info(device_1_items)
                    to_write = '.invoke('
                    for elem in line:
                        if ')' in elem:
                            to_write+=elem
                        else:
                            to_write+=elem+', '  
                    file1.write(to_write)
                elif line[0][1:] in device_2_items:
                    device_2_items = device_2_items.replace(line[0], "", 1)
                    to_write = '.invoke('
                    for elem in line:
                        if ')' in elem:
                            to_write+=elem
                        else:
                            to_write+=elem+', '  
                    file2.write(to_write)
    file1.write(';\n')
    file1.write('}')
    file2.write(';\n')
    file2.write('}')

                    # file1.write()
                # file1.write(line)

    # for vertex in v2s:
    #     if vertex.name in device_1_items and 'TASK_VERTEX' in vertex.name:
    #         _logger.info(vertex.name)
    #         _logger.info(vertex.in_edge_names)
    #         in_edges = vertex.in_edge_names
    #         in_edges_sanitized = []
    #         for edge in in_edges:
    #             edge = edge[10:]
    #             in_edges_sanitized.append(edge)
    #         out_edges_sanitized=[]
    #         out_edges = vertex.out_edge_names
    #         for edge in out_edges:
    #             edge = edge[10:]
    #             out_edges_sanitized.append(edge)
    #         _logger.info(','.join(in_edges_sanitized))
    #         _logger.info(','.join(out_edges_sanitized))
            
            # file1.write('\t.invoke('+vertex.name, )
            # file1.write('\t.invoke('+vertex.name+'\n')



