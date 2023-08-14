from tapa.AutoBridge.src.autobridge.Opt.DataflowGraph import Edge, Vertex
from tapa.AutoBridge.src.autobridge.Opt.Slot import Slot
import tapa.core
import logging
from typing import Dict, List

# logging.basicConfig(filename="/home/ubuntu/tapa_m/regression/stencil-dilate/tapa/src/std.log", 
# 					format='%(asctime)s %(message)s', 
# 					filemode='w+') 

# #Let us Create an object 
# _logger=logging.getLogger() 

# #Now we are going to Set the threshold of logger to DEBUG 
# _logger.setLevel(logging.INFO) 

# # logging.basicConfig(filename = 'output.txt', 
# #                     filemode = 'a',
# #                     level = logging.info)
_logger = logging.getLogger().getChild(__name__)

# def sanitise_names(v2s):


def split_kernel(v2s:Dict[Vertex, Slot] , slot_list:List[Slot], program:tapa.core.Program):
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
    file_1 = open('kernel_1.cpp', 'w+')
    file_2 = open('kernel_2.cpp', 'w+')
    with open('tapa_kernel.cpp', 'r') as top:
        lines = top.readlines()
        for line in lines:
            if 'void '+program.top not in line:
                file_1.write(line)
                file_2.write(line)
            else:
                break

    file_1.write('void '+program.top+'_1(')
    file_2.write('void '+program.top+'_2(')
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
            if port.name in device_1_items:
                toadd = 'tapa::mmap<INTERFACE_WIDTH> '+name+',\n'
                file_1.write(toadd)
            elif port.name in device_2_items:
                toadd = 'tapa::mmap<INTERFACE_WIDTH> '+name+',\n'
                file_2.write(toadd)
        elif cat_type=='SCALAR':
            toadd = ctype+' '+name+',\n'
            file_1.write(toadd)
            file_2.write(toadd)
        # elif count==numports:
    file_1.write('tapa::ostream<float> &out_board,\n')
    file_1.write('tapa::istream<float> &in_board){\n')
    file_2.write('tapa::ostream<float> &out_board,\n')
    file_2.write('tapa::istream<float> &in_board){\n')
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


    with open('tapa_kernel.cpp', 'r') as top:
        lines = top.readlines()
        for line in lines:
            if 'tapa::stream' in line:
                file_1.write(line)
                file_2.write(line)

    file_1.write('tapa::task()\n')
    file_2.write('tapa::task()\n')
    with open('tapa_kernel.cpp', 'r') as top:
        lines = top.readlines()
        for line in lines:
            if '.invoke' in line:
                line = line.split('(')
                line = line[1].split(',')
                _logger.info(line)
                if line[0] in device_1_items:
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
                    file_1.write(to_write)
                elif line[0] in device_2_items:
                    device_2_items = device_2_items.replace(line[0], "", 1)
                    to_write = '.invoke('
                    for elem in line:
                        if ')' in elem:
                            to_write+=elem
                        else:
                            to_write+=elem+', '  
                    file_2.write(to_write)
    file_1.write(';\n')
    file_1.write('}')
    file_2.write(';\n')
    file_2.write('}')

                    # file_1.write()
                # file_1.write(line)

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
            
            # file_1.write('\t.invoke('+vertex.name, )
            # file_1.write('\t.invoke('+vertex.name+'\n')



