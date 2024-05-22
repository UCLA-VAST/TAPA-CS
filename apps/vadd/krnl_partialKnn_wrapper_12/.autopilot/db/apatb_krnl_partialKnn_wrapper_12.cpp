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
#define AUTOTB_TVIN_searchSpace_0_read_addr "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_searchSpace_0_read_addr.dat"
#define AUTOTB_TVOUT_searchSpace_0_read_addr "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_read_addr.dat"
#define WRAPC_STREAM_SIZE_OUT_searchSpace_0_read_addr "../tv/stream_size/stream_size_out_searchSpace_0_read_addr.dat"
#define WRAPC_STREAM_EGRESS_STATUS_searchSpace_0_read_addr "../tv/stream_size/stream_egress_status_searchSpace_0_read_addr.dat"
#define AUTOTB_TVIN_searchSpace_0_read_data_s "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_searchSpace_0_read_data_s.dat"
#define AUTOTB_TVOUT_searchSpace_0_read_data_s "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_read_data_s.dat"
#define WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_s "../tv/stream_size/stream_size_in_searchSpace_0_read_data_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_s "../tv/stream_size/stream_ingress_status_searchSpace_0_read_data_s.dat"
#define AUTOTB_TVIN_searchSpace_0_read_data_peek "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_searchSpace_0_read_data_peek.dat"
#define AUTOTB_TVOUT_searchSpace_0_read_data_peek "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_read_data_peek.dat"
#define WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_peek "../tv/stream_size/stream_size_in_searchSpace_0_read_data_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_peek "../tv/stream_size/stream_ingress_status_searchSpace_0_read_data_peek.dat"
#define AUTOTB_TVIN_searchSpace_0_write_addr "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_searchSpace_0_write_addr.dat"
#define AUTOTB_TVOUT_searchSpace_0_write_addr "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_addr.dat"
#define WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_addr "../tv/stream_size/stream_size_out_searchSpace_0_write_addr.dat"
#define WRAPC_STREAM_EGRESS_STATUS_searchSpace_0_write_addr "../tv/stream_size/stream_egress_status_searchSpace_0_write_addr.dat"
#define AUTOTB_TVIN_searchSpace_0_write_data "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_searchSpace_0_write_data.dat"
#define AUTOTB_TVOUT_searchSpace_0_write_data "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_data.dat"
#define WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_data "../tv/stream_size/stream_size_out_searchSpace_0_write_data.dat"
#define WRAPC_STREAM_EGRESS_STATUS_searchSpace_0_write_data "../tv/stream_size/stream_egress_status_searchSpace_0_write_data.dat"
#define AUTOTB_TVIN_searchSpace_0_write_resp_s "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_searchSpace_0_write_resp_s.dat"
#define AUTOTB_TVOUT_searchSpace_0_write_resp_s "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_resp_s.dat"
#define WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_s "../tv/stream_size/stream_size_in_searchSpace_0_write_resp_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_s "../tv/stream_size/stream_ingress_status_searchSpace_0_write_resp_s.dat"
#define AUTOTB_TVIN_searchSpace_0_write_resp_peek "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_searchSpace_0_write_resp_peek.dat"
#define AUTOTB_TVOUT_searchSpace_0_write_resp_peek "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_resp_peek.dat"
#define WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_peek "../tv/stream_size/stream_size_in_searchSpace_0_write_resp_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_peek "../tv/stream_size/stream_ingress_status_searchSpace_0_write_resp_peek.dat"
#define AUTOTB_TVIN_start_id_0 "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_start_id_0.dat"
#define AUTOTB_TVOUT_start_id_0 "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_start_id_0.dat"
#define AUTOTB_TVIN_out_dist "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_out_dist.dat"
#define AUTOTB_TVOUT_out_dist "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_out_dist.dat"
#define WRAPC_STREAM_SIZE_OUT_out_dist "../tv/stream_size/stream_size_out_out_dist.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_dist "../tv/stream_size/stream_egress_status_out_dist.dat"
#define AUTOTB_TVIN_out_id "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvin_out_id.dat"
#define AUTOTB_TVOUT_out_id "../tv/cdatafile/c.krnl_partialKnn_wrapper_12.autotvout_out_id.dat"
#define WRAPC_STREAM_SIZE_OUT_out_id "../tv/stream_size/stream_size_out_out_id.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_id "../tv/stream_size/stream_egress_status_out_id.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_searchSpace_0_read_addr "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_read_addr.dat"
#define AUTOTB_TVOUT_PC_searchSpace_0_read_data_s "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_read_data_s.dat"
#define AUTOTB_TVOUT_PC_searchSpace_0_read_data_peek "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_read_data_peek.dat"
#define AUTOTB_TVOUT_PC_searchSpace_0_write_addr "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_addr.dat"
#define AUTOTB_TVOUT_PC_searchSpace_0_write_data "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_data.dat"
#define AUTOTB_TVOUT_PC_searchSpace_0_write_resp_s "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_resp_s.dat"
#define AUTOTB_TVOUT_PC_searchSpace_0_write_resp_peek "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_searchSpace_0_write_resp_peek.dat"
#define AUTOTB_TVOUT_PC_start_id_0 "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_start_id_0.dat"
#define AUTOTB_TVOUT_PC_out_dist "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_out_dist.dat"
#define AUTOTB_TVOUT_PC_out_id "../tv/rtldatafile/rtl.krnl_partialKnn_wrapper_12.autotvout_out_id.dat"


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
  searchSpace_0_read_addr_depth = 0;
  searchSpace_0_read_data_s_depth = 0;
  searchSpace_0_read_data_peek_depth = 0;
  searchSpace_0_write_addr_depth = 0;
  searchSpace_0_write_data_depth = 0;
  searchSpace_0_write_resp_s_depth = 0;
  searchSpace_0_write_resp_peek_depth = 0;
  start_id_0_depth = 0;
  out_dist_depth = 0;
  out_id_depth = 0;
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
  total_list << "{searchSpace_0_read_addr " << searchSpace_0_read_addr_depth << "}\n";
  total_list << "{searchSpace_0_read_data_s " << searchSpace_0_read_data_s_depth << "}\n";
  total_list << "{searchSpace_0_read_data_peek " << searchSpace_0_read_data_peek_depth << "}\n";
  total_list << "{searchSpace_0_write_addr " << searchSpace_0_write_addr_depth << "}\n";
  total_list << "{searchSpace_0_write_data " << searchSpace_0_write_data_depth << "}\n";
  total_list << "{searchSpace_0_write_resp_s " << searchSpace_0_write_resp_s_depth << "}\n";
  total_list << "{searchSpace_0_write_resp_peek " << searchSpace_0_write_resp_peek_depth << "}\n";
  total_list << "{start_id_0 " << start_id_0_depth << "}\n";
  total_list << "{out_dist " << out_dist_depth << "}\n";
  total_list << "{out_id " << out_id_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int searchSpace_0_read_addr_depth;
    int searchSpace_0_read_data_s_depth;
    int searchSpace_0_read_data_peek_depth;
    int searchSpace_0_write_addr_depth;
    int searchSpace_0_write_data_depth;
    int searchSpace_0_write_resp_s_depth;
    int searchSpace_0_write_resp_peek_depth;
    int start_id_0_depth;
    int out_dist_depth;
    int out_id_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


struct __cosim_s9__ { char data[16]; };
struct __cosim_s33__ { char data[64]; };
extern "C" void krnl_partialKnn_wrapper_12_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, int, volatile void *, volatile void *);

extern "C" void apatb_krnl_partialKnn_wrapper_12_hw(volatile void * __xlx_apatb_param_searchSpace_0_read_addr, volatile void * __xlx_apatb_param_searchSpace_0_read_data_s, volatile void * __xlx_apatb_param_searchSpace_0_read_data_peek, volatile void * __xlx_apatb_param_searchSpace_0_write_addr, volatile void * __xlx_apatb_param_searchSpace_0_write_data, volatile void * __xlx_apatb_param_searchSpace_0_write_resp_s, volatile void * __xlx_apatb_param_searchSpace_0_write_resp_peek, int __xlx_apatb_param_start_id_0, volatile void * __xlx_apatb_param_out_dist, volatile void * __xlx_apatb_param_out_id) {
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
long __xlx_apatb_param_searchSpace_0_read_addr_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_searchSpace_0_read_addr);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_searchSpace_0_read_addr_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_searchSpace_0_read_addr);
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
          std::vector<sc_bv<65> > searchSpace_0_read_addr_pc_buffer;
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              searchSpace_0_read_addr_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "searchSpace_0_read_addr" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
__cosim_s9__ xlx_stream_elt __attribute__ ((aligned));
((long long*)&xlx_stream_elt)[0*2+0] = searchSpace_0_read_addr_pc_buffer[j].range(63,0).to_int64();
((long long*)&xlx_stream_elt)[0*2+1] = searchSpace_0_read_addr_pc_buffer[j].range(64,64).to_int64();
((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_read_addr)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  long __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size; ++i)((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_s)->read();
long __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size; ++i)((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_peek)->read();
long __xlx_apatb_param_searchSpace_0_write_addr_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_addr);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_searchSpace_0_write_addr_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_searchSpace_0_write_addr);
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
          std::vector<sc_bv<65> > searchSpace_0_write_addr_pc_buffer;
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              searchSpace_0_write_addr_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "searchSpace_0_write_addr" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
__cosim_s9__ xlx_stream_elt __attribute__ ((aligned));
((long long*)&xlx_stream_elt)[0*2+0] = searchSpace_0_write_addr_pc_buffer[j].range(63,0).to_int64();
((long long*)&xlx_stream_elt)[0*2+1] = searchSpace_0_write_addr_pc_buffer[j].range(64,64).to_int64();
((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_write_addr)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  long __xlx_apatb_param_searchSpace_0_write_data_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_data);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_searchSpace_0_write_data_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_searchSpace_0_write_data);
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
          std::vector<sc_bv<257> > searchSpace_0_write_data_pc_buffer;
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              searchSpace_0_write_data_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "searchSpace_0_write_data" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
__cosim_s33__ xlx_stream_elt __attribute__ ((aligned));
((long long*)&xlx_stream_elt)[0*8+0] = searchSpace_0_write_data_pc_buffer[j].range(63,0).to_int64();
((long long*)&xlx_stream_elt)[0*8+1] = searchSpace_0_write_data_pc_buffer[j].range(127,64).to_int64();
((long long*)&xlx_stream_elt)[0*8+2] = searchSpace_0_write_data_pc_buffer[j].range(191,128).to_int64();
((long long*)&xlx_stream_elt)[0*8+3] = searchSpace_0_write_data_pc_buffer[j].range(255,192).to_int64();
((long long*)&xlx_stream_elt)[0*8+4] = searchSpace_0_write_data_pc_buffer[j].range(256,256).to_int64();
((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_write_data)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  long __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size; ++i)((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_s)->read();
long __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size; ++i)((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_peek)->read();
long __xlx_apatb_param_out_dist_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_out_dist);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_out_dist_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_dist);
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
          std::vector<sc_bv<45> > out_dist_pc_buffer;
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_dist_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "out_dist" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
long long xlx_stream_elt __attribute__ ((aligned));
((char*)&xlx_stream_elt)[0*8+0] = out_dist_pc_buffer[j].range(7, 0).to_int64();
((char*)&xlx_stream_elt)[0*8+1] = out_dist_pc_buffer[j].range(15, 8).to_int64();
((char*)&xlx_stream_elt)[0*8+2] = out_dist_pc_buffer[j].range(23, 16).to_int64();
((char*)&xlx_stream_elt)[0*8+3] = out_dist_pc_buffer[j].range(31, 24).to_int64();
((char*)&xlx_stream_elt)[0*8+4] = out_dist_pc_buffer[j].range(39, 32).to_int64();
((char*)&xlx_stream_elt)[0*8+5] = out_dist_pc_buffer[j].range(44, 40).to_int64();
((hls::stream<long long>*)__xlx_apatb_param_out_dist)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  long __xlx_apatb_param_out_id_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_out_id);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_out_id_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_id);
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
          std::vector<sc_bv<45> > out_id_pc_buffer;
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_id_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "out_id" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
long long xlx_stream_elt __attribute__ ((aligned));
((char*)&xlx_stream_elt)[0*8+0] = out_id_pc_buffer[j].range(7, 0).to_int64();
((char*)&xlx_stream_elt)[0*8+1] = out_id_pc_buffer[j].range(15, 8).to_int64();
((char*)&xlx_stream_elt)[0*8+2] = out_id_pc_buffer[j].range(23, 16).to_int64();
((char*)&xlx_stream_elt)[0*8+3] = out_id_pc_buffer[j].range(31, 24).to_int64();
((char*)&xlx_stream_elt)[0*8+4] = out_id_pc_buffer[j].range(39, 32).to_int64();
((char*)&xlx_stream_elt)[0*8+5] = out_id_pc_buffer[j].range(44, 40).to_int64();
((hls::stream<long long>*)__xlx_apatb_param_out_id)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_searchSpace_0_read_addr);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_searchSpace_0_read_addr);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_addr);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_searchSpace_0_write_addr);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_data);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_searchSpace_0_write_data);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_dist);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_dist);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_id);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_id);
CodeState = DUMP_INPUTS;
std::vector<__cosim_s9__> __xlx_apatb_param_searchSpace_0_read_addr_stream_buf;
long __xlx_apatb_param_searchSpace_0_read_addr_stream_buf_size = ((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_read_addr)->size();
std::vector<__cosim_s33__> __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf;
{
  while (!((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_s)->empty())
    __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf.push_back(((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_s)->read());
  for (int i = 0; i < __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_s)->write(__xlx_apatb_param_searchSpace_0_read_data_s_stream_buf[i]);
  }
long __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_size = ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_s)->size();
std::vector<__cosim_s33__> __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf;
{
  while (!((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_peek)->empty())
    __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf.push_back(((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_peek)->write(__xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf[i]);
  }
long __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_size = ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_peek)->size();
std::vector<__cosim_s9__> __xlx_apatb_param_searchSpace_0_write_addr_stream_buf;
long __xlx_apatb_param_searchSpace_0_write_addr_stream_buf_size = ((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_write_addr)->size();
std::vector<__cosim_s33__> __xlx_apatb_param_searchSpace_0_write_data_stream_buf;
long __xlx_apatb_param_searchSpace_0_write_data_stream_buf_size = ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_write_data)->size();
std::vector<short> __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf;
{
  while (!((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_s)->empty())
    __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf.push_back(((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_s)->read());
  for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf.size(); ++i)
    ((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_s)->write(__xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf[i]);
  }
long __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_size = ((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_s)->size();
std::vector<short> __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf;
{
  while (!((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_peek)->empty())
    __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf.push_back(((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf.size(); ++i)
    ((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_peek)->write(__xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf[i]);
  }
long __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_size = ((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_peek)->size();
std::vector<long long> __xlx_apatb_param_out_dist_stream_buf;
long __xlx_apatb_param_out_dist_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_out_dist)->size();
std::vector<long long> __xlx_apatb_param_out_id_stream_buf;
long __xlx_apatb_param_out_id_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_out_id)->size();
// print start_id_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_start_id_0, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_start_id_0;
aesl_fh.write(AUTOTB_TVIN_start_id_0, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.start_id_0_depth);
aesl_fh.write(AUTOTB_TVIN_start_id_0, end_str());
}

CodeState = CALL_C_DUT;
krnl_partialKnn_wrapper_12_hw_stub_wrapper(__xlx_apatb_param_searchSpace_0_read_addr, __xlx_apatb_param_searchSpace_0_read_data_s, __xlx_apatb_param_searchSpace_0_read_data_peek, __xlx_apatb_param_searchSpace_0_write_addr, __xlx_apatb_param_searchSpace_0_write_data, __xlx_apatb_param_searchSpace_0_write_resp_s, __xlx_apatb_param_searchSpace_0_write_resp_peek, __xlx_apatb_param_start_id_0, __xlx_apatb_param_out_dist, __xlx_apatb_param_out_id);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_searchSpace_0_read_addr_stream_buf_final_size = ((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_read_addr)->size() - __xlx_apatb_param_searchSpace_0_read_addr_stream_buf_size;
{
  while (!((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_read_addr)->empty())
    __xlx_apatb_param_searchSpace_0_read_addr_stream_buf.push_back(((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_read_addr)->read());
  for (int i = 0; i < __xlx_apatb_param_searchSpace_0_read_addr_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_read_addr)->write(__xlx_apatb_param_searchSpace_0_read_addr_stream_buf[i]);
  }
// print searchSpace_0_read_addr Transactions
{
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_read_addr, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_searchSpace_0_read_addr_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_searchSpace_0_read_addr_stream_buf.data()+__xlx_apatb_param_searchSpace_0_read_addr_stream_buf_size+i);
std::string s(formatData(pos, 65));
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_read_addr, s);
}

  tcl_file.set_num(__xlx_apatb_param_searchSpace_0_read_addr_stream_buf_final_size, &tcl_file.searchSpace_0_read_addr_depth);
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_read_addr, end_str());
}

{
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_read_addr, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_searchSpace_0_read_addr_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_read_addr, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_read_addr, end_str());
}
long __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size = __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_size - ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_s)->size();
// print searchSpace_0_read_data_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_read_data_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_searchSpace_0_read_data_s_stream_buf.data()+i);
std::string s(formatData(pos, 257));
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_read_data_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size, &tcl_file.searchSpace_0_read_data_s_depth);
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_read_data_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size > 0) {
  long searchSpace_0_read_data_s_stream_ingress_size = __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_read_data_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size; j != e; j++) {
    searchSpace_0_read_data_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_read_data_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_s, __xlx_sprintf_buffer.data());
  }
} else {
  long searchSpace_0_read_data_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_read_data_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_searchSpace_0_read_data_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_s, end_str());
}
long __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size = __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_size - ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_read_data_peek)->size();
// print searchSpace_0_read_data_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_read_data_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf.data()+i);
std::string s(formatData(pos, 257));
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_read_data_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size, &tcl_file.searchSpace_0_read_data_peek_depth);
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_read_data_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size > 0) {
  long searchSpace_0_read_data_peek_stream_ingress_size = __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_read_data_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size; j != e; j++) {
    searchSpace_0_read_data_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_read_data_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long searchSpace_0_read_data_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_read_data_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_read_data_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_searchSpace_0_read_data_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_read_data_peek, end_str());
}
long __xlx_apatb_param_searchSpace_0_write_addr_stream_buf_final_size = ((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_write_addr)->size() - __xlx_apatb_param_searchSpace_0_write_addr_stream_buf_size;
{
  while (!((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_write_addr)->empty())
    __xlx_apatb_param_searchSpace_0_write_addr_stream_buf.push_back(((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_write_addr)->read());
  for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_addr_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s9__>*)__xlx_apatb_param_searchSpace_0_write_addr)->write(__xlx_apatb_param_searchSpace_0_write_addr_stream_buf[i]);
  }
// print searchSpace_0_write_addr Transactions
{
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_write_addr, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_addr_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_searchSpace_0_write_addr_stream_buf.data()+__xlx_apatb_param_searchSpace_0_write_addr_stream_buf_size+i);
std::string s(formatData(pos, 65));
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_write_addr, s);
}

  tcl_file.set_num(__xlx_apatb_param_searchSpace_0_write_addr_stream_buf_final_size, &tcl_file.searchSpace_0_write_addr_depth);
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_write_addr, end_str());
}

{
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_addr, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_searchSpace_0_write_addr_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_addr, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_addr, end_str());
}
long __xlx_apatb_param_searchSpace_0_write_data_stream_buf_final_size = ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_write_data)->size() - __xlx_apatb_param_searchSpace_0_write_data_stream_buf_size;
{
  while (!((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_write_data)->empty())
    __xlx_apatb_param_searchSpace_0_write_data_stream_buf.push_back(((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_write_data)->read());
  for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_data_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s33__>*)__xlx_apatb_param_searchSpace_0_write_data)->write(__xlx_apatb_param_searchSpace_0_write_data_stream_buf[i]);
  }
// print searchSpace_0_write_data Transactions
{
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_write_data, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_data_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_searchSpace_0_write_data_stream_buf.data()+__xlx_apatb_param_searchSpace_0_write_data_stream_buf_size+i);
std::string s(formatData(pos, 257));
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_write_data, s);
}

  tcl_file.set_num(__xlx_apatb_param_searchSpace_0_write_data_stream_buf_final_size, &tcl_file.searchSpace_0_write_data_depth);
aesl_fh.write(AUTOTB_TVOUT_searchSpace_0_write_data, end_str());
}

{
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_data, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_searchSpace_0_write_data_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_data, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_searchSpace_0_write_data, end_str());
}
long __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size = __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_size - ((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_s)->size();
// print searchSpace_0_write_resp_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_write_resp_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf.data()+i);
std::string s(formatData(pos, 9));
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_write_resp_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size, &tcl_file.searchSpace_0_write_resp_s_depth);
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_write_resp_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size > 0) {
  long searchSpace_0_write_resp_s_stream_ingress_size = __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_write_resp_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size; j != e; j++) {
    searchSpace_0_write_resp_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_write_resp_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_s, __xlx_sprintf_buffer.data());
  }
} else {
  long searchSpace_0_write_resp_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_write_resp_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_searchSpace_0_write_resp_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_s, end_str());
}
long __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size = __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_size - ((hls::stream<short>*)__xlx_apatb_param_searchSpace_0_write_resp_peek)->size();
// print searchSpace_0_write_resp_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_write_resp_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf.data()+i);
std::string s(formatData(pos, 9));
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_write_resp_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size, &tcl_file.searchSpace_0_write_resp_peek_depth);
aesl_fh.write(AUTOTB_TVIN_searchSpace_0_write_resp_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size > 0) {
  long searchSpace_0_write_resp_peek_stream_ingress_size = __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_write_resp_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size; j != e; j++) {
    searchSpace_0_write_resp_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_write_resp_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long searchSpace_0_write_resp_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", searchSpace_0_write_resp_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_searchSpace_0_write_resp_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_searchSpace_0_write_resp_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_searchSpace_0_write_resp_peek, end_str());
}
long __xlx_apatb_param_out_dist_stream_buf_final_size = ((hls::stream<long long>*)__xlx_apatb_param_out_dist)->size() - __xlx_apatb_param_out_dist_stream_buf_size;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_out_dist)->empty())
    __xlx_apatb_param_out_dist_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_out_dist)->read());
  for (int i = 0; i < __xlx_apatb_param_out_dist_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_out_dist)->write(__xlx_apatb_param_out_dist_stream_buf[i]);
  }
// print out_dist Transactions
{
aesl_fh.write(AUTOTB_TVOUT_out_dist, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_out_dist_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_out_dist_stream_buf.data()+__xlx_apatb_param_out_dist_stream_buf_size+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVOUT_out_dist, s);
}

  tcl_file.set_num(__xlx_apatb_param_out_dist_stream_buf_final_size, &tcl_file.out_dist_depth);
aesl_fh.write(AUTOTB_TVOUT_out_dist, end_str());
}

{
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_dist, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_dist_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_dist, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_dist, end_str());
}
long __xlx_apatb_param_out_id_stream_buf_final_size = ((hls::stream<long long>*)__xlx_apatb_param_out_id)->size() - __xlx_apatb_param_out_id_stream_buf_size;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_out_id)->empty())
    __xlx_apatb_param_out_id_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_out_id)->read());
  for (int i = 0; i < __xlx_apatb_param_out_id_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_out_id)->write(__xlx_apatb_param_out_id_stream_buf[i]);
  }
// print out_id Transactions
{
aesl_fh.write(AUTOTB_TVOUT_out_id, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_out_id_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_out_id_stream_buf.data()+__xlx_apatb_param_out_id_stream_buf_size+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVOUT_out_id, s);
}

  tcl_file.set_num(__xlx_apatb_param_out_id_stream_buf_final_size, &tcl_file.out_id_depth);
aesl_fh.write(AUTOTB_TVOUT_out_id, end_str());
}

{
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_id, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_id_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_id, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_id, end_str());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
