# problem with the subscript matching and edges: basically wrong functions are going to the wrong file

from tapa.AutoBridge.src.autobridge.Opt.DataflowGraph import Edge, Vertex
from tapa.AutoBridge.src.autobridge.Opt.Slot import Slot
import tapa.core
import logging
from typing import Dict, List


_logger = logging.getLogger().getChild(__name__)

def sanitize_names(name:str):
    # return name.replace('TASK_VERTEX_', '')
    if ' ' in name and '[' not in name:
        return name.replace(' ', '')
    elif '[' in name:
        name = str(name.split('[')[0])
        if ' ' in name:
            name = name.replace(' ', '')
            _logger.info(name)
        return name
    else:
        return name

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
            file1.write('tapa::mmap<'+ctype[:-1]+'> '+port.name+',\n')
        elif port.name+'__m_axi' in device_2_names and str(port.cat).split('.')[1]=='MMAP':
            file2.write('tapa::mmap<'+ctype[:-1]+'> '+port.name+',\n')
    file1.write(')\n')
    file2.write(')\n')
    file1.write('{\n')
    file2.write('{\n')
    
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
                partition_1_in.append((vertex.name, in_edge.name))
        for out_edge in out_edges:
            if out_edge.dst.name in device_2_names:
                partition_1_out.append((vertex.name, out_edge.name))
    for vertex in device_2_items:
        in_edges = vertex.in_edges
        out_edges = vertex.out_edges
        for in_edge in in_edges:
            if in_edge.src.name in device_1_names:
                partition_2_in.append((vertex.name, in_edge.name))
        for out_edge in out_edges:
            if out_edge.dst.name in device_1_names:
                partition_2_out.append((vertex.name, out_edge.name))
    return partition_1_in, partition_1_out, partition_2_in, partition_2_out

def unique_task_counts(input_file:str):
    file_input = open(input_file, 'r')
    lines = file_input.readlines()
    unique_tasks = []
    task_counts = []
    for line in lines:
        if '.invoke' in line:
            task_name = str(line.split('(')[1]).split(',')[0]
            task_name = sanitize_names(task_name)
            if task_name not in unique_tasks:
                unique_tasks.append(task_name)
                task_counts.append(0)

    for line in lines:
        if '.invoke' in line:
            task_name = str(line.split('(')[1]).split(',')[0]
            task_name = sanitize_names(task_name)
            for i in range(len(unique_tasks)):
                if unique_tasks[i]==task_name:
                    task_counts[i]+=1
    return unique_tasks, task_counts

    
        


def add_invokes(input_file:str, file1, file2, device_1_items, device_2_items, program:tapa.core.Program):
    file_input = open(input_file, 'r')
    lines = file_input.readlines()
    device_1_names = []
    device_2_names = []
    for vertex in device_1_items:
        device_1_names.append(vertex.name)
    for vertex in device_2_items:
        device_2_names.append(vertex.name)
    device_1_names = '\t'.join(device_1_names)
    device_2_names = '\t'.join(device_2_names)
    middle_streams = []
    for line in lines:
        if 'tapa::stream' in line:
            middle_streams.append(str(line.split('>')[1])[:-2])
            file1.write(line)
            file2.write(line)
    middle_streams = '\t'.join(middle_streams)
    _logger.info(middle_streams)
    unique_tasks, task_counts = unique_task_counts(input_file)
    already_invoked = []
    for line in lines:
        if '.invoke' in line:
            task_name = str(line.split('(')[1]).split(',')[0]
            edge_1_name = str(line.split('(')[1]).split(',')[1]
            _logger.info(task_name)
            _logger.info(edge_1_name)
            task_name = sanitize_names(task_name)
            edge_1_name = sanitize_names(edge_1_name)
            counts = 0
            for i in range(len(already_invoked)):
                if already_invoked[i]==task_name:
                    counts+=1
            _logger.info(counts)
            already_invoked.append(task_name)
            if task_name+'_'+str(counts) in device_1_names:
                file1.write(line)
                _logger.info(task_name)
                device_1_names = device_1_names.replace('TASK_VERTEX_'+task_name+'_'+str(counts), '')
                _logger.info(device_1_names)
            elif task_name+'_'+str(counts) in device_2_names:
                file2.write(line)
                device_2_names = device_2_names.replace('TASK_VERTEX_'+task_name+'_'+str(counts), '')



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
    add_invokes(input_file, file1, file2, device_1_items, device_2_items, program)
    file1.write('}\n')
    file2.write('}\n')
    # add_inter_fpga_comm(input_file, file1, file2, device_1_items, device_2_items, program)
