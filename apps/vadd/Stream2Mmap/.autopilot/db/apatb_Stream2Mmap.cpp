#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_stream_s "../tv/cdatafile/c.Stream2Mmap.autotvin_stream_s.dat"
#define AUTOTB_TVOUT_stream_s "../tv/cdatafile/c.Stream2Mmap.autotvout_stream_s.dat"
#define WRAPC_STREAM_SIZE_IN_stream_s "../tv/stream_size/stream_size_in_stream_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_stream_s "../tv/stream_size/stream_ingress_status_stream_s.dat"
#define AUTOTB_TVIN_stream_peek "../tv/cdatafile/c.Stream2Mmap.autotvin_stream_peek.dat"
#define AUTOTB_TVOUT_stream_peek "../tv/cdatafile/c.Stream2Mmap.autotvout_stream_peek.dat"
#define WRAPC_STREAM_SIZE_IN_stream_peek "../tv/stream_size/stream_size_in_stream_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_stream_peek "../tv/stream_size/stream_ingress_status_stream_peek.dat"
#define AUTOTB_TVIN_mmap_offset "../tv/cdatafile/c.Stream2Mmap.autotvin_mmap_offset.dat"
#define AUTOTB_TVOUT_mmap_offset "../tv/cdatafile/c.Stream2Mmap.autotvout_mmap_offset.dat"
#define AUTOTB_TVIN_n "../tv/cdatafile/c.Stream2Mmap.autotvin_n.dat"
#define AUTOTB_TVOUT_n "../tv/cdatafile/c.Stream2Mmap.autotvout_n.dat"
#define AUTOTB_TVIN_mmap "../tv/cdatafile/c.Stream2Mmap.autotvin_mmap.dat"
#define AUTOTB_TVOUT_mmap "../tv/cdatafile/c.Stream2Mmap.autotvout_mmap.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_stream_s "../tv/rtldatafile/rtl.Stream2Mmap.autotvout_stream_s.dat"
#define AUTOTB_TVOUT_PC_stream_peek "../tv/rtldatafile/rtl.Stream2Mmap.autotvout_stream_peek.dat"
#define AUTOTB_TVOUT_PC_mmap_offset "../tv/rtldatafile/rtl.Stream2Mmap.autotvout_mmap_offset.dat"
#define AUTOTB_TVOUT_PC_n "../tv/rtldatafile/rtl.Stream2Mmap.autotvout_n.dat"
#define AUTOTB_TVOUT_PC_mmap "../tv/rtldatafile/rtl.Stream2Mmap.autotvout_mmap.dat"


static const bool little_endian()
{
  int a = 1;
  return *(char*)&a == 1;
}

inline static void rev_endian(char* p, size_t nbytes)
{
  std::reverse(p, p+nbytes);
}

template<size_t bit_width>
struct transaction {
  typedef uint64_t depth_t;
  static const size_t wbytes = (bit_width+7)>>3;
  static const size_t dbytes = sizeof(depth_t);
  const depth_t depth;
  const size_t vbytes;
  const size_t tbytes;
  char * const p;
  typedef char (*p_dat)[wbytes];
  p_dat vp;

  transaction(depth_t depth)
    : depth(depth), vbytes(wbytes*depth), tbytes(dbytes+vbytes),
      p(new char[tbytes]) {
    *(depth_t*)p = depth;
    rev_endian(p, dbytes);
    vp = (p_dat) (p+dbytes);
  }

  void reorder() {
    rev_endian(p, dbytes);
    p_dat vp = (p_dat) (p+dbytes);
    for (depth_t i = 0; i < depth; ++i) {
      rev_endian(vp[i], wbytes);
    }
  }

  template<size_t psize>
  void import(char* param, depth_t num, int64_t offset) {
    param -= offset*psize;
    for (depth_t i = 0; i < num; ++i) {
      memcpy(vp[i], param, wbytes);
      param += psize;
      if (little_endian()) {
        rev_endian(vp[i], wbytes);
      }
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[i], wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num, int64_t skip) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[skip+i], wbytes);
      param += psize;
    }
  }

  ~transaction() { if (p) { delete[] p; } }
};


inline static const std::string begin_str(int num)
{
  return std::string("[[transaction]]           ")
         .append(std::to_string(num))
         .append("\n");
}

inline static const std::string end_str()
{
  return std::string("[[/transaction]]\n");
}

const std::string formatData(unsigned char *pos, size_t wbits)
{
  bool LE = little_endian();
  size_t wbytes = (wbits+7)>>3;
  size_t i = LE ? wbytes-1 : 0;
  auto next = [&] () {
    auto c = pos[i];
    LE ? --i : ++i;
    return c;
  };
  std::ostringstream ss;
  ss << "0x";
  if (int t = (wbits & 0x7)) {
    if (t <= 4) {
      unsigned char mask = (1<<t)-1;
      ss << std::hex << std::setfill('0') << std::setw(1)
         << (int) (next() & mask);
      wbytes -= 1;
    }
  }
  for (size_t i = 0; i < wbytes; ++i) {
    ss << std::hex << std::setfill('0') << std::setw(2) << (int)next();
  }
  ss.put('\n');
  return ss.str();
}

static bool RTLOutputCheckAndReplacement(std::string &data)
{
  bool changed = false;
  for (size_t i = 2; i < data.size(); ++i) {
    if (data[i] == 'X' || data[i] == 'x') {
      data[i] = '0';
      changed = true;
    }
  }
  return changed;
}

struct SimException : public std::exception {
  const char *msg;
  const size_t line;
  SimException(const char *msg, const size_t line)
    : msg(msg), line(line)
  {
  }
};

template<size_t bit_width>
class PostCheck
{
  static const char *bad;
  static const char *err;
  std::fstream stream;
  std::string s;

  void send(char *p, ap_uint<bit_width> &data, size_t l, size_t rest)
  {
    if (rest == 0) {
      if (!little_endian()) {
        const size_t wbytes = (bit_width+7)>>3;
        rev_endian(p-wbytes, wbytes);
      }
    } else if (rest < 8) {
      *p = data.range(l+rest-1, l).to_uint();
      send(p+1, data, l+rest, 0);
    } else {
      *p = data.range(l+8-1, l).to_uint();
      send(p+1, data, l+8, rest-8);
    }
  }

  void readline()
  {
    std::getline(stream, s);
    if (stream.eof()) {
      throw SimException(bad, __LINE__);
    }
  }

public:
  char *param;
  size_t psize;
  size_t depth;

  PostCheck(const char *file)
  {
    stream.open(file);
    if (stream.fail()) {
      throw SimException(err, __LINE__);
    } else {
      readline();
      if (s != "[[[runtime]]]") {
        throw SimException(bad, __LINE__);
      }
    }
  }

  ~PostCheck() noexcept(false)
  {
    stream.close();
  }

  void run(size_t AESL_transaction_pc, size_t skip)
  {
    if (stream.peek() == '[') {
      readline();
    }

    for (size_t i = 0; i < skip; ++i) {
      readline();
    }

    bool foundX = false;
    for (size_t i = 0; i < depth; ++i) {
      readline();
      foundX |= RTLOutputCheckAndReplacement(s);
      ap_uint<bit_width> data(s.c_str(), 16);
      send(param+i*psize, data, 0, bit_width);
    }
    if (foundX) {
      std::cerr << "WARNING: [SIM 212-201] RTL produces unknown value "
                << "'x' or 'X' on some port, possible cause: "
                << "There are uninitialized variables in the design.\n";
    }

    if (stream.peek() == '[') {
      readline();
    }
  }
};

template<size_t bit_width>
const char* PostCheck<bit_width>::bad = "Bad TV file";

template<size_t bit_width>
const char* PostCheck<bit_width>::err = "Error on TV file";
      
class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  stream_s_depth = 0;
  stream_peek_depth = 0;
  mmap_offset_depth = 0;
  n_depth = 0;
  mmap_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{stream_s " << stream_s_depth << "}\n";
  total_list << "{stream_peek " << stream_peek_depth << "}\n";
  total_list << "{mmap_offset " << mmap_offset_depth << "}\n";
  total_list << "{n " << n_depth << "}\n";
  total_list << "{mmap " << mmap_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int stream_s_depth;
    int stream_peek_depth;
    int mmap_offset_depth;
    int n_depth;
    int mmap_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


extern "C" void Stream2Mmap_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, long long);

extern "C" void apatb_Stream2Mmap_hw(volatile void * __xlx_apatb_param_stream_s, volatile void * __xlx_apatb_param_stream_peek, volatile void * __xlx_apatb_param_mmap, long long __xlx_apatb_param_n) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
static AESL_FILE_HANDLER aesl_fh;
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
long __xlx_apatb_param_stream_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_stream_s);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_stream_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_stream_s_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_stream_s)->read();
long __xlx_apatb_param_stream_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_stream_peek);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_stream_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_stream_peek_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_stream_peek)->read();
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_mmap);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_mmap;
pc.depth = 1;
pc.run(AESL_transaction_pc, 0);
} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}

    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_stream_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_stream_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_stream_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_stream_peek);
CodeState = DUMP_INPUTS;
unsigned __xlx_offset_byte_param_mmap = 0;
std::vector<long long> __xlx_apatb_param_stream_s_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_stream_s)->empty())
    __xlx_apatb_param_stream_s_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_stream_s)->read());
  for (int i = 0; i < __xlx_apatb_param_stream_s_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_stream_s)->write(__xlx_apatb_param_stream_s_stream_buf[i]);
  }
long __xlx_apatb_param_stream_s_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_stream_s)->size();
std::vector<long long> __xlx_apatb_param_stream_peek_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_stream_peek)->empty())
    __xlx_apatb_param_stream_peek_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_stream_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_stream_peek_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_stream_peek)->write(__xlx_apatb_param_stream_peek_stream_buf[i]);
  }
long __xlx_apatb_param_stream_peek_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_stream_peek)->size();
aesl_fh.touch(AUTOTB_TVIN_mmap);
{
aesl_fh.write(AUTOTB_TVIN_mmap, begin_str(AESL_transaction));
__xlx_offset_byte_param_mmap = 0*4;
if (__xlx_apatb_param_mmap) {
for (size_t i = 0; i < 1; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_mmap + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_mmap, s);
}
}
tcl_file.set_num(1, &tcl_file.mmap_depth);
aesl_fh.write(AUTOTB_TVIN_mmap, end_str());
}
// print mmap_offset Transactions
{
aesl_fh.write(AUTOTB_TVIN_mmap_offset, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_mmap;
aesl_fh.write(AUTOTB_TVIN_mmap_offset, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.mmap_offset_depth);
aesl_fh.write(AUTOTB_TVIN_mmap_offset, end_str());
}

// print n Transactions
{
aesl_fh.write(AUTOTB_TVIN_n, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_n;
aesl_fh.write(AUTOTB_TVIN_n, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.n_depth);
aesl_fh.write(AUTOTB_TVIN_n, end_str());
}

CodeState = CALL_C_DUT;
Stream2Mmap_hw_stub_wrapper(__xlx_apatb_param_stream_s, __xlx_apatb_param_stream_peek, __xlx_apatb_param_mmap, __xlx_apatb_param_n);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_stream_s_stream_buf_final_size = __xlx_apatb_param_stream_s_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_stream_s)->size();
// print stream_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_stream_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_stream_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_stream_s_stream_buf.data()+i);
std::string s(formatData(pos, 33));
aesl_fh.write(AUTOTB_TVIN_stream_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_stream_s_stream_buf_final_size, &tcl_file.stream_s_depth);
aesl_fh.write(AUTOTB_TVIN_stream_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_stream_s_stream_buf_final_size > 0) {
  long stream_s_stream_ingress_size = __xlx_apatb_param_stream_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", stream_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_stream_s_stream_buf_final_size; j != e; j++) {
    stream_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", stream_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_s, __xlx_sprintf_buffer.data());
  }
} else {
  long stream_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", stream_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_stream_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_stream_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_stream_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_stream_s, end_str());
}
long __xlx_apatb_param_stream_peek_stream_buf_final_size = __xlx_apatb_param_stream_peek_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_stream_peek)->size();
// print stream_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_stream_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_stream_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_stream_peek_stream_buf.data()+i);
std::string s(formatData(pos, 33));
aesl_fh.write(AUTOTB_TVIN_stream_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_stream_peek_stream_buf_final_size, &tcl_file.stream_peek_depth);
aesl_fh.write(AUTOTB_TVIN_stream_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_stream_peek_stream_buf_final_size > 0) {
  long stream_peek_stream_ingress_size = __xlx_apatb_param_stream_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", stream_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_stream_peek_stream_buf_final_size; j != e; j++) {
    stream_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", stream_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long stream_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", stream_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_stream_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_stream_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_stream_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_stream_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_stream_peek, end_str());
}
aesl_fh.touch(AUTOTB_TVOUT_mmap);
{
aesl_fh.write(AUTOTB_TVOUT_mmap, begin_str(AESL_transaction));
__xlx_offset_byte_param_mmap = 0*4;
if (__xlx_apatb_param_mmap) {
for (size_t i = 0; i < 1; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_mmap + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_mmap, s);
}
}
tcl_file.set_num(1, &tcl_file.mmap_depth);
aesl_fh.write(AUTOTB_TVOUT_mmap, end_str());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
