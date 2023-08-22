from tapa.AutoBridge.src.autobridge.Opt.DataflowGraph import Edge, Vertex
from tapa.AutoBridge.src.autobridge.Opt.Slot import Slot
import tapa.core
import logging
from typing import Dict, List
import re

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
    elif 'FIFO' in name:
        name = re.sub('FIFO_EDGE_', '', name)
        _logger.info(name)
        index = name.split('_')[-1]
        name_split = name.split('_')[:-1]
        final_name = ''
        for elem in name_split:
            final_name+=elem+'_'
        final_name = final_name[:-1]
        final_name = final_name+'['+index+']'
        _logger.info(final_name)
        return final_name
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
            _logger.info(in_edge.name)
            _logger.info(in_edge.width)
            if in_edge.src.name in device_2_names and 'AXI_EDGE' not in in_edge.name:
                partition_1_in.append((vertex.name, in_edge))
        for out_edge in out_edges:
            _logger.info(out_edge.dst.name)
            if out_edge.dst.name in device_2_names and 'AXI_EDGE' not in out_edge.name:
                partition_1_out.append((vertex.name, out_edge))
    for vertex in device_2_items:
        in_edges = vertex.in_edges
        out_edges = vertex.out_edges
        for in_edge in in_edges:
            if in_edge.src.name in device_1_names and 'AXI_EDGE' not in in_edge.name:
                partition_2_in.append((vertex.name, in_edge))
        for out_edge in out_edges:
            if out_edge.dst.name in device_1_names and 'AXI_EDGE' not in out_edge.name:
                partition_2_out.append((vertex.name, out_edge))
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

def round_width(width:int):
    width=width-1
    while width & width-1:
        width=width&width-1
    return width<<1



def add_mmap2streams(unique_counts, unique_types, edge_mappings, file1):
    func_names = []
    args_names = []
    for i in range(len(unique_counts)):
        count = unique_counts[i]
        types = unique_types[i]
        edges_in = edge_mappings[i]
        args = ''
        streams_list = []
        temps_list = []
        for j in range(len(edges_in)):
            name = edges_in[j]
            name = sanitize_names(name)
            if j != len(edges_in)-1:
                args+='tapa::ostream<'+types+'> &'+name+','
                streams_list.append(name)
            else:
                args+='tapa::ostream<'+types+'> &'+name+','
                streams_list.append(name)
                for i in range(count):
                    if i !=count-1:
                        args+='tapa::mmap<'+types+'>'+' temp'+str(i)+','
                        temps_list.append('temp'+str(i))
                    else:
                        args+='tapa::mmap<'+types+'>'+' temp'+str(i)
                        temps_list.append('temp'+str(i))
        _logger.info(args)
        _logger.info(temps_list)
        _logger.info(streams_list)
        file1.write('void Mmap2Stream_'+types+'('+args+'){\n')
        func_names.append('Mmap2Stream_'+types)
        args_names.append(args)
        ranges = count*10
        file1.write('for(int i = 0 ; i < '+str(ranges)+' ; ++i){\n')
        for i in range(count):
            if i==0:
                file1.write('\tif(i%'+str(count)+'=='+str(i)+'){\n')
                # file1.write('\ttapa::ostream<'+)
                file1.write('\t'+streams_list[i]+'<<'+temps_list[i]+'[i/'+str(count)+'];}\n')
            elif i==count-1:
                file1.write('\telse(i%'+str(count)+'=='+str(i)+'){\n')
                file1.write('\t'+streams_list[i]+'<<'+temps_list[i]+'[i/'+str(count)+'];}\n')
            else:
                file1.write('\telif(i%'+str(count)+'=='+str(i)+'){\n')
                file1.write('\t'+streams_list[i]+'<<'+temps_list[i]+'[i/'+str(count)+'];}\n')
        file1.write('}}\n')
        return func_names, args_names


def add_stream2Mmaps(unique_counts, unique_types, edge_mappings, file1):
    func_names = []
    args_names = []
    for i in range(len(unique_counts)):
        count = unique_counts[i]
        types = unique_types[i]
        edges_in = edge_mappings[i]
        args = ''
        streams_list = []
        temps_list = []
        for j in range(len(edges_in)):
            name = edges_in[j]
            name = sanitize_names(name)
            if j!=len(edges_in)-1:
                args+='tapa::istream<'+types+'> &'+name+','
                streams_list.append(name)
            else:
                args+='tapa::istream<'+types+'> &'+name+','
                streams_list.append(name)
                for i in range(count):
                    if i !=count-1:
                        args+='tapa::mmap<'+types+'>'+' temp'+str(i)+','
                        temps_list.append('temp'+str(i))
                    else:
                        args+='tapa::mmap<'+types+'>'+' temp'+str(i)
                        temps_list.append('temp'+str(i))
        _logger.info(args)
        _logger.info(temps_list)
        _logger.info(streams_list)
        file1.write('void Stream2Mmap_'+types+'('+args+'){\n')
        func_names.append('Stream2Mmap_'+types)
        args_names.append(args)
        ranges = count*10
        file1.write('for(int i=0; i < '+str(ranges)+' ; ++i){\n')
        for i in range(count):
            if i==0:
                file1.write('\tif(i%'+str(count)+'=='+str(i)+'){\n')
                # file1.write('\ttapa::ostream<'+)
                file1.write('\t'+streams_list[i]+'>>'+temps_list[i]+'[i/'+str(count)+'];}\n')
            elif i==count-1:
                file1.write('\telse(i%'+str(count)+'=='+str(i)+'){\n')
                file1.write('\t'+streams_list[i]+'>>'+temps_list[i]+'[i/'+str(count)+'];}\n')
            else:
                file1.write('\telif(i%'+str(count)+'=='+str(i)+'){\n')
                file1.write('\t'+streams_list[i]+'>>'+temps_list[i]+'[i/'+str(count)+'];}\n')
        file1.write('}}\n')
        return func_names, args_names

def add_inter_fpga_comm_1(input_file, temp1, file1, device_own_items, device_other_items, partition_1_in, partition_1_out):
    # lines = file1.readlines()
    tmp1 = open(input_file, 'r')
    lines = tmp1.readlines()
    for line in lines:
        if 'void' not in line:
            file1.write(line)
        else:
            break
    middle_streams_types = []
    for line in lines:
        if 'tapa::stream' in line:
            middle_name = str(line.split('>')[1])[:-2]
            middle_streams_types.append((middle_name, str(str(line.split('<')[1]).split(',')[0])))
    _logger.info(middle_streams_types)

    vertices=[]
    in_edge_names = []
    for i in range(len(partition_1_in)):
        vertice, in_edge = partition_1_in[i]
        in_edge_names.append(in_edge.name)
        vertices.append(vertice)
    edge_types = []
    for edge_names in in_edge_names:
        _logger.info(edge_names)
        for i in range(len(middle_streams_types)):
            name, types = middle_streams_types[i]
            # name = sanitize_names(name)
            name = sanitize_names(name)
            _logger.info(name)
            if name in edge_names:
                edge_types.append((edge_names, types))
    _logger.info(edge_types)
    # unique_types, edge_mappings = get_type_mappings(edge_types)
    unique_types = []
    unique_counts = []
    edge_mappings = []
    for i in range(len(edge_types)):
        edge_name, edge_type = edge_types[i]
        if edge_type not in unique_types:
            unique_types.append(edge_type)
            unique_counts.append(0)
            edge_mappings.append([])
    for i in range(len(unique_types)):
        unique_type = unique_types[i]
        for name, types in edge_types:
            if types==unique_type:
                unique_counts[i]+=1
                edge_mappings[i].append(name)
    _logger.info(unique_counts)
    _logger.info(unique_types)
    _logger.info(edge_mappings)
    if len(partition_1_in)!=0:
        func_names_in, args_names_in = add_mmap2streams(unique_counts, unique_types, edge_mappings, file1)
    
    vertices = []
    out_edge_names = []
    for i in range(len(partition_1_out)):
        vertice, out_edge = partition_1_out[i]
        out_edge_names.append(out_edge.name)
        vertices.append(vertice)
    edge_types_out = []
    for edge_names in out_edge_names:
        _logger.info(edge_names)
        for i in range(len(middle_streams_types)):
            name, types = middle_streams_types[i]
            name = sanitize_names(name)
            _logger.info(name)
            if name in edge_names:
                edge_types_out.append((edge_names, types))
    _logger.info(edge_types_out)
    unique_types_out = []
    unique_counts_out = []
    edge_mappings_out = []
    for i in range(len(edge_types_out)):
        edge_name, edge_type = edge_types_out[i]
        if edge_type not in unique_types_out:
            unique_types_out.append(edge_type)
            unique_counts_out.append(0)
            edge_mappings_out.append([])
    for i in range(len(unique_types_out)):
        unique_type = unique_types_out[i]
        for name, types in edge_types_out:
            if types ==unique_type:
                unique_counts_out[i]+=1
                edge_mappings_out[i].append(name)
    _logger.info(unique_counts_out)
    _logger.info(unique_types_out)
    _logger.info(edge_mappings_out)
    if len(partition_1_out)!=0:
        func_names_out, args_names_out = add_stream2Mmaps(unique_counts_out, unique_types_out, edge_mappings_out, file1)
    if len(partition_1_out)==0:
        func_names_out=[]
        args_names_out = []
    if len(partition_1_in)==0:
        func_names_in=[]
        args_names_in=[]
    # if func_names_in==None:
    #     func_names_in=[]
    # elif func_names_out==None:
    #     func_names_out=[]
    # elif args_names_in==None:
    #     args_names_in=[]
    # elif args_names_out==None:
    #     args_names_out=[]
    return func_names_in, args_names_in, func_names_out, args_names_out
        

# def combine(file1, file1_final, partition_1_in, partition_1_out):
#     file1 = open(file1, 'r')
#     lines = file1.readlines()
#     for line in lines:
#         if '.invoke' not line:

def find_placements(temp1, func_1_in, args_1_in, func_1_out, args_1_out):
    file1 = open(temp1, 'r')
    lines = file1.readlines()
    placement_ins = ''
    placement_outs = ''
    _logger.info(func_1_in)
    _logger.info(args_1_in)
    _logger.info(func_1_out)
    _logger.info(args_1_out)
    if len(args_1_in)!=0:
        args_1_in = args_1_in[0].split(',')
    else:
        args_1_in = ['no values']
    if len(args_1_out)!=0:
        args_1_out = args_1_out[0].split(',')
    else:
        args_1_out = ['no values']
    _logger.info(args_1_in)
    args_1_preprocessed_in = []
    args_1_preprocessed_out = []
    for values in args_1_in:
        _logger.info(values.split('&'))
        if '&' in values:
            values = values.split('&')[1]
        elif ' ' in values:
            values = values.split(' ')[1]
        args_1_preprocessed_in.append(values)
    for values in args_1_out:
        if '&' in values:
            values = values.split(' ')[1]
        elif ' ' in values:
            values = values.split(' ')[1]
        args_1_preprocessed_out.append(values)
    _logger.info(args_1_preprocessed_in)
    _logger.info(args_1_preprocessed_out)
    placements_1_in = []
    placements_1_out = []
    for line in lines:
        if '.invoke' in line:
            split_line = line.split(',')[1:]
            _logger.info(split_line)
            for items in split_line:
                if items in args_1_preprocessed_in:
                    placements_1_in.append(line)
                if items in args_1_preprocessed_out:
                    placements_1_out.append(line)
    return placements_1_in, placements_1_out


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
    file1 = open("tmp1.cpp", 'w+')
    file2 = open("tmp2.cpp", 'w+')
    file1_final = open("kernel_1.cpp", 'w+')
    file2_final = open("kernel_2.cpp", 'w+')
    add_tasks(input_file, file1, file2, program)
    add_ports(input_file, file1, file2, device_1_items, device_2_items, program)
    partition_1_in, partition_1_out, partition_2_in, partition_2_out = find_partitions(device_1_items, device_2_items)
    _logger.info(partition_1_in)
    _logger.info(partition_1_out)
    _logger.info(partition_2_in)
    _logger.info(partition_2_out)
    add_invokes(input_file, file1, file2, device_1_items, device_2_items, program)
    file1.close()
    # file1 = open("tmp1.cpp", 'r+')
    # lines = file1.readlines()
    # _logger.info(len(lines))
    temp1 = 'tmp1.cpp'
    func_1_in, args_1_in, func_1_out, args_1_out = add_inter_fpga_comm_1(input_file, temp1, file1_final, device_1_items, device_2_items, partition_1_in, partition_1_out)
    _logger.info(func_1_in)
    _logger.info(args_1_in)
    _logger.info(func_1_out)
    _logger.info(args_1_out)
    # placements_1_in_out = find_placements(temp1, func_1_in, args_1_in, func_1_out, args_1_out)
    placements_1_in, placements_1_out = find_placements(temp1, func_1_in, args_1_in, func_1_out, args_1_out)
    _logger.info(placements_1_in)
    _logger.info(placements_1_out)
    # combine(file1, file1_final, partition_1_in, partition_1_out)
    # add_inter_fpga_comm_2(input_file, file2, device_2_items, device_1_items, partition_2_in, partition_2_out)
    # file1.write('}\n')
    # file2.write('}\n')
    # add_inter_fpga_comm(input_file, file1, file2, device_1_items, device_2_items, program)
