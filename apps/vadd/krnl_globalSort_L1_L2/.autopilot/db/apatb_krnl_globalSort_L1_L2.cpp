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
#define AUTOTB_TVIN_in_dist0_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_dist0_s.dat"
#define AUTOTB_TVOUT_in_dist0_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_dist0_s.dat"
#define WRAPC_STREAM_SIZE_IN_in_dist0_s "../tv/stream_size/stream_size_in_in_dist0_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_dist0_s "../tv/stream_size/stream_ingress_status_in_dist0_s.dat"
#define AUTOTB_TVIN_in_dist0_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_dist0_peek.dat"
#define AUTOTB_TVOUT_in_dist0_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_dist0_peek.dat"
#define WRAPC_STREAM_SIZE_IN_in_dist0_peek "../tv/stream_size/stream_size_in_in_dist0_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_dist0_peek "../tv/stream_size/stream_ingress_status_in_dist0_peek.dat"
#define AUTOTB_TVIN_in_id0_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_id0_s.dat"
#define AUTOTB_TVOUT_in_id0_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_id0_s.dat"
#define WRAPC_STREAM_SIZE_IN_in_id0_s "../tv/stream_size/stream_size_in_in_id0_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_id0_s "../tv/stream_size/stream_ingress_status_in_id0_s.dat"
#define AUTOTB_TVIN_in_id0_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_id0_peek.dat"
#define AUTOTB_TVOUT_in_id0_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_id0_peek.dat"
#define WRAPC_STREAM_SIZE_IN_in_id0_peek "../tv/stream_size/stream_size_in_in_id0_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_id0_peek "../tv/stream_size/stream_ingress_status_in_id0_peek.dat"
#define AUTOTB_TVIN_in_dist1_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_dist1_s.dat"
#define AUTOTB_TVOUT_in_dist1_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_dist1_s.dat"
#define WRAPC_STREAM_SIZE_IN_in_dist1_s "../tv/stream_size/stream_size_in_in_dist1_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_dist1_s "../tv/stream_size/stream_ingress_status_in_dist1_s.dat"
#define AUTOTB_TVIN_in_dist1_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_dist1_peek.dat"
#define AUTOTB_TVOUT_in_dist1_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_dist1_peek.dat"
#define WRAPC_STREAM_SIZE_IN_in_dist1_peek "../tv/stream_size/stream_size_in_in_dist1_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_dist1_peek "../tv/stream_size/stream_ingress_status_in_dist1_peek.dat"
#define AUTOTB_TVIN_in_id1_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_id1_s.dat"
#define AUTOTB_TVOUT_in_id1_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_id1_s.dat"
#define WRAPC_STREAM_SIZE_IN_in_id1_s "../tv/stream_size/stream_size_in_in_id1_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_id1_s "../tv/stream_size/stream_ingress_status_in_id1_s.dat"
#define AUTOTB_TVIN_in_id1_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_id1_peek.dat"
#define AUTOTB_TVOUT_in_id1_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_id1_peek.dat"
#define WRAPC_STREAM_SIZE_IN_in_id1_peek "../tv/stream_size/stream_size_in_in_id1_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_id1_peek "../tv/stream_size/stream_ingress_status_in_id1_peek.dat"
#define AUTOTB_TVIN_in_dist2_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_dist2_s.dat"
#define AUTOTB_TVOUT_in_dist2_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_dist2_s.dat"
#define WRAPC_STREAM_SIZE_IN_in_dist2_s "../tv/stream_size/stream_size_in_in_dist2_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_dist2_s "../tv/stream_size/stream_ingress_status_in_dist2_s.dat"
#define AUTOTB_TVIN_in_dist2_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_dist2_peek.dat"
#define AUTOTB_TVOUT_in_dist2_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_dist2_peek.dat"
#define WRAPC_STREAM_SIZE_IN_in_dist2_peek "../tv/stream_size/stream_size_in_in_dist2_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_dist2_peek "../tv/stream_size/stream_ingress_status_in_dist2_peek.dat"
#define AUTOTB_TVIN_in_id2_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_id2_s.dat"
#define AUTOTB_TVOUT_in_id2_s "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_id2_s.dat"
#define WRAPC_STREAM_SIZE_IN_in_id2_s "../tv/stream_size/stream_size_in_in_id2_s.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_id2_s "../tv/stream_size/stream_ingress_status_in_id2_s.dat"
#define AUTOTB_TVIN_in_id2_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_in_id2_peek.dat"
#define AUTOTB_TVOUT_in_id2_peek "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_in_id2_peek.dat"
#define WRAPC_STREAM_SIZE_IN_in_id2_peek "../tv/stream_size/stream_size_in_in_id2_peek.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_id2_peek "../tv/stream_size/stream_ingress_status_in_id2_peek.dat"
#define AUTOTB_TVIN_out_dist "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_out_dist.dat"
#define AUTOTB_TVOUT_out_dist "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_out_dist.dat"
#define WRAPC_STREAM_SIZE_OUT_out_dist "../tv/stream_size/stream_size_out_out_dist.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_dist "../tv/stream_size/stream_egress_status_out_dist.dat"
#define AUTOTB_TVIN_out_id "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvin_out_id.dat"
#define AUTOTB_TVOUT_out_id "../tv/cdatafile/c.krnl_globalSort_L1_L2.autotvout_out_id.dat"
#define WRAPC_STREAM_SIZE_OUT_out_id "../tv/stream_size/stream_size_out_out_id.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_id "../tv/stream_size/stream_egress_status_out_id.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_in_dist0_s "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_dist0_s.dat"
#define AUTOTB_TVOUT_PC_in_dist0_peek "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_dist0_peek.dat"
#define AUTOTB_TVOUT_PC_in_id0_s "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_id0_s.dat"
#define AUTOTB_TVOUT_PC_in_id0_peek "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_id0_peek.dat"
#define AUTOTB_TVOUT_PC_in_dist1_s "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_dist1_s.dat"
#define AUTOTB_TVOUT_PC_in_dist1_peek "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_dist1_peek.dat"
#define AUTOTB_TVOUT_PC_in_id1_s "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_id1_s.dat"
#define AUTOTB_TVOUT_PC_in_id1_peek "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_id1_peek.dat"
#define AUTOTB_TVOUT_PC_in_dist2_s "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_dist2_s.dat"
#define AUTOTB_TVOUT_PC_in_dist2_peek "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_dist2_peek.dat"
#define AUTOTB_TVOUT_PC_in_id2_s "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_id2_s.dat"
#define AUTOTB_TVOUT_PC_in_id2_peek "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_in_id2_peek.dat"
#define AUTOTB_TVOUT_PC_out_dist "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_out_dist.dat"
#define AUTOTB_TVOUT_PC_out_id "../tv/rtldatafile/rtl.krnl_globalSort_L1_L2.autotvout_out_id.dat"


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
  in_dist0_s_depth = 0;
  in_dist0_peek_depth = 0;
  in_id0_s_depth = 0;
  in_id0_peek_depth = 0;
  in_dist1_s_depth = 0;
  in_dist1_peek_depth = 0;
  in_id1_s_depth = 0;
  in_id1_peek_depth = 0;
  in_dist2_s_depth = 0;
  in_dist2_peek_depth = 0;
  in_id2_s_depth = 0;
  in_id2_peek_depth = 0;
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
  total_list << "{in_dist0_s " << in_dist0_s_depth << "}\n";
  total_list << "{in_dist0_peek " << in_dist0_peek_depth << "}\n";
  total_list << "{in_id0_s " << in_id0_s_depth << "}\n";
  total_list << "{in_id0_peek " << in_id0_peek_depth << "}\n";
  total_list << "{in_dist1_s " << in_dist1_s_depth << "}\n";
  total_list << "{in_dist1_peek " << in_dist1_peek_depth << "}\n";
  total_list << "{in_id1_s " << in_id1_s_depth << "}\n";
  total_list << "{in_id1_peek " << in_id1_peek_depth << "}\n";
  total_list << "{in_dist2_s " << in_dist2_s_depth << "}\n";
  total_list << "{in_dist2_peek " << in_dist2_peek_depth << "}\n";
  total_list << "{in_id2_s " << in_id2_s_depth << "}\n";
  total_list << "{in_id2_peek " << in_id2_peek_depth << "}\n";
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
    int in_dist0_s_depth;
    int in_dist0_peek_depth;
    int in_id0_s_depth;
    int in_id0_peek_depth;
    int in_dist1_s_depth;
    int in_dist1_peek_depth;
    int in_id1_s_depth;
    int in_id1_peek_depth;
    int in_dist2_s_depth;
    int in_dist2_peek_depth;
    int in_id2_s_depth;
    int in_id2_peek_depth;
    int out_dist_depth;
    int out_id_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


extern "C" void krnl_globalSort_L1_L2_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_krnl_globalSort_L1_L2_hw(volatile void * __xlx_apatb_param_in_dist0_s, volatile void * __xlx_apatb_param_in_dist0_peek, volatile void * __xlx_apatb_param_in_id0_s, volatile void * __xlx_apatb_param_in_id0_peek, volatile void * __xlx_apatb_param_in_dist1_s, volatile void * __xlx_apatb_param_in_dist1_peek, volatile void * __xlx_apatb_param_in_id1_s, volatile void * __xlx_apatb_param_in_id1_peek, volatile void * __xlx_apatb_param_in_dist2_s, volatile void * __xlx_apatb_param_in_dist2_peek, volatile void * __xlx_apatb_param_in_id2_s, volatile void * __xlx_apatb_param_in_id2_peek, volatile void * __xlx_apatb_param_out_dist, volatile void * __xlx_apatb_param_out_id) {
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
long __xlx_apatb_param_in_dist0_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_dist0_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_dist0_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_dist0_s_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s)->read();
long __xlx_apatb_param_in_dist0_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_dist0_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_dist0_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_dist0_peek_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek)->read();
long __xlx_apatb_param_in_id0_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_id0_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_id0_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_id0_s_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_id0_s)->read();
long __xlx_apatb_param_in_id0_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_id0_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_id0_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_id0_peek_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek)->read();
long __xlx_apatb_param_in_dist1_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_dist1_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_dist1_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_dist1_s_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s)->read();
long __xlx_apatb_param_in_dist1_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_dist1_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_dist1_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_dist1_peek_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek)->read();
long __xlx_apatb_param_in_id1_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_id1_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_id1_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_id1_s_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_id1_s)->read();
long __xlx_apatb_param_in_id1_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_id1_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_id1_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_id1_peek_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek)->read();
long __xlx_apatb_param_in_dist2_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_dist2_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_dist2_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_dist2_s_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s)->read();
long __xlx_apatb_param_in_dist2_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_dist2_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_dist2_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_dist2_peek_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek)->read();
long __xlx_apatb_param_in_id2_s_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_id2_s);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_id2_s_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_id2_s_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_id2_s)->read();
long __xlx_apatb_param_in_id2_peek_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_id2_peek);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_id2_peek_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_id2_peek_stream_buf_final_size; ++i)((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek)->read();
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
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_dist0_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_dist0_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_dist0_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_dist0_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_id0_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_id0_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_id0_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_id0_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_dist1_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_dist1_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_dist1_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_dist1_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_id1_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_id1_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_id1_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_id1_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_dist2_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_dist2_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_dist2_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_dist2_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_id2_s);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_id2_s);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_id2_peek);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_id2_peek);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_dist);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_dist);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_id);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_id);
CodeState = DUMP_INPUTS;
std::vector<long long> __xlx_apatb_param_in_dist0_s_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s)->empty())
    __xlx_apatb_param_in_dist0_s_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s)->read());
  for (int i = 0; i < __xlx_apatb_param_in_dist0_s_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s)->write(__xlx_apatb_param_in_dist0_s_stream_buf[i]);
  }
long __xlx_apatb_param_in_dist0_s_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s)->size();
std::vector<long long> __xlx_apatb_param_in_dist0_peek_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek)->empty())
    __xlx_apatb_param_in_dist0_peek_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_in_dist0_peek_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek)->write(__xlx_apatb_param_in_dist0_peek_stream_buf[i]);
  }
long __xlx_apatb_param_in_dist0_peek_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek)->size();
std::vector<long long> __xlx_apatb_param_in_id0_s_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_id0_s)->empty())
    __xlx_apatb_param_in_id0_s_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_id0_s)->read());
  for (int i = 0; i < __xlx_apatb_param_in_id0_s_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_id0_s)->write(__xlx_apatb_param_in_id0_s_stream_buf[i]);
  }
long __xlx_apatb_param_in_id0_s_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_id0_s)->size();
std::vector<long long> __xlx_apatb_param_in_id0_peek_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek)->empty())
    __xlx_apatb_param_in_id0_peek_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_in_id0_peek_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek)->write(__xlx_apatb_param_in_id0_peek_stream_buf[i]);
  }
long __xlx_apatb_param_in_id0_peek_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek)->size();
std::vector<long long> __xlx_apatb_param_in_dist1_s_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s)->empty())
    __xlx_apatb_param_in_dist1_s_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s)->read());
  for (int i = 0; i < __xlx_apatb_param_in_dist1_s_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s)->write(__xlx_apatb_param_in_dist1_s_stream_buf[i]);
  }
long __xlx_apatb_param_in_dist1_s_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s)->size();
std::vector<long long> __xlx_apatb_param_in_dist1_peek_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek)->empty())
    __xlx_apatb_param_in_dist1_peek_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_in_dist1_peek_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek)->write(__xlx_apatb_param_in_dist1_peek_stream_buf[i]);
  }
long __xlx_apatb_param_in_dist1_peek_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek)->size();
std::vector<long long> __xlx_apatb_param_in_id1_s_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_id1_s)->empty())
    __xlx_apatb_param_in_id1_s_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_id1_s)->read());
  for (int i = 0; i < __xlx_apatb_param_in_id1_s_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_id1_s)->write(__xlx_apatb_param_in_id1_s_stream_buf[i]);
  }
long __xlx_apatb_param_in_id1_s_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_id1_s)->size();
std::vector<long long> __xlx_apatb_param_in_id1_peek_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek)->empty())
    __xlx_apatb_param_in_id1_peek_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_in_id1_peek_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek)->write(__xlx_apatb_param_in_id1_peek_stream_buf[i]);
  }
long __xlx_apatb_param_in_id1_peek_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek)->size();
std::vector<long long> __xlx_apatb_param_in_dist2_s_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s)->empty())
    __xlx_apatb_param_in_dist2_s_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s)->read());
  for (int i = 0; i < __xlx_apatb_param_in_dist2_s_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s)->write(__xlx_apatb_param_in_dist2_s_stream_buf[i]);
  }
long __xlx_apatb_param_in_dist2_s_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s)->size();
std::vector<long long> __xlx_apatb_param_in_dist2_peek_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek)->empty())
    __xlx_apatb_param_in_dist2_peek_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_in_dist2_peek_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek)->write(__xlx_apatb_param_in_dist2_peek_stream_buf[i]);
  }
long __xlx_apatb_param_in_dist2_peek_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek)->size();
std::vector<long long> __xlx_apatb_param_in_id2_s_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_id2_s)->empty())
    __xlx_apatb_param_in_id2_s_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_id2_s)->read());
  for (int i = 0; i < __xlx_apatb_param_in_id2_s_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_id2_s)->write(__xlx_apatb_param_in_id2_s_stream_buf[i]);
  }
long __xlx_apatb_param_in_id2_s_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_id2_s)->size();
std::vector<long long> __xlx_apatb_param_in_id2_peek_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek)->empty())
    __xlx_apatb_param_in_id2_peek_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek)->read());
  for (int i = 0; i < __xlx_apatb_param_in_id2_peek_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek)->write(__xlx_apatb_param_in_id2_peek_stream_buf[i]);
  }
long __xlx_apatb_param_in_id2_peek_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek)->size();
std::vector<long long> __xlx_apatb_param_out_dist_stream_buf;
long __xlx_apatb_param_out_dist_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_out_dist)->size();
std::vector<long long> __xlx_apatb_param_out_id_stream_buf;
long __xlx_apatb_param_out_id_stream_buf_size = ((hls::stream<long long>*)__xlx_apatb_param_out_id)->size();
CodeState = CALL_C_DUT;
krnl_globalSort_L1_L2_hw_stub_wrapper(__xlx_apatb_param_in_dist0_s, __xlx_apatb_param_in_dist0_peek, __xlx_apatb_param_in_id0_s, __xlx_apatb_param_in_id0_peek, __xlx_apatb_param_in_dist1_s, __xlx_apatb_param_in_dist1_peek, __xlx_apatb_param_in_id1_s, __xlx_apatb_param_in_id1_peek, __xlx_apatb_param_in_dist2_s, __xlx_apatb_param_in_dist2_peek, __xlx_apatb_param_in_id2_s, __xlx_apatb_param_in_id2_peek, __xlx_apatb_param_out_dist, __xlx_apatb_param_out_id);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_in_dist0_s_stream_buf_final_size = __xlx_apatb_param_in_dist0_s_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s)->size();
// print in_dist0_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_dist0_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_dist0_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_dist0_s_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_dist0_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_dist0_s_stream_buf_final_size, &tcl_file.in_dist0_s_depth);
aesl_fh.write(AUTOTB_TVIN_in_dist0_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_dist0_s_stream_buf_final_size > 0) {
  long in_dist0_s_stream_ingress_size = __xlx_apatb_param_in_dist0_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist0_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_dist0_s_stream_buf_final_size; j != e; j++) {
    in_dist0_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist0_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_s, __xlx_sprintf_buffer.data());
  }
} else {
  long in_dist0_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist0_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist0_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_dist0_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist0_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist0_s, end_str());
}
long __xlx_apatb_param_in_dist0_peek_stream_buf_final_size = __xlx_apatb_param_in_dist0_peek_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek)->size();
// print in_dist0_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_dist0_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_dist0_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_dist0_peek_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_dist0_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_dist0_peek_stream_buf_final_size, &tcl_file.in_dist0_peek_depth);
aesl_fh.write(AUTOTB_TVIN_in_dist0_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_dist0_peek_stream_buf_final_size > 0) {
  long in_dist0_peek_stream_ingress_size = __xlx_apatb_param_in_dist0_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist0_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_dist0_peek_stream_buf_final_size; j != e; j++) {
    in_dist0_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist0_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long in_dist0_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist0_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist0_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist0_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_dist0_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist0_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist0_peek, end_str());
}
long __xlx_apatb_param_in_id0_s_stream_buf_final_size = __xlx_apatb_param_in_id0_s_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_id0_s)->size();
// print in_id0_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_id0_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_id0_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_id0_s_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_id0_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_id0_s_stream_buf_final_size, &tcl_file.in_id0_s_depth);
aesl_fh.write(AUTOTB_TVIN_in_id0_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_id0_s_stream_buf_final_size > 0) {
  long in_id0_s_stream_ingress_size = __xlx_apatb_param_in_id0_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id0_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_id0_s_stream_buf_final_size; j != e; j++) {
    in_id0_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id0_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_s, __xlx_sprintf_buffer.data());
  }
} else {
  long in_id0_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id0_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id0_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_id0_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id0_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id0_s, end_str());
}
long __xlx_apatb_param_in_id0_peek_stream_buf_final_size = __xlx_apatb_param_in_id0_peek_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek)->size();
// print in_id0_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_id0_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_id0_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_id0_peek_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_id0_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_id0_peek_stream_buf_final_size, &tcl_file.in_id0_peek_depth);
aesl_fh.write(AUTOTB_TVIN_in_id0_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_id0_peek_stream_buf_final_size > 0) {
  long in_id0_peek_stream_ingress_size = __xlx_apatb_param_in_id0_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id0_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_id0_peek_stream_buf_final_size; j != e; j++) {
    in_id0_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id0_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long in_id0_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id0_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id0_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id0_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_id0_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id0_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id0_peek, end_str());
}
long __xlx_apatb_param_in_dist1_s_stream_buf_final_size = __xlx_apatb_param_in_dist1_s_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s)->size();
// print in_dist1_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_dist1_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_dist1_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_dist1_s_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_dist1_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_dist1_s_stream_buf_final_size, &tcl_file.in_dist1_s_depth);
aesl_fh.write(AUTOTB_TVIN_in_dist1_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_dist1_s_stream_buf_final_size > 0) {
  long in_dist1_s_stream_ingress_size = __xlx_apatb_param_in_dist1_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist1_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_dist1_s_stream_buf_final_size; j != e; j++) {
    in_dist1_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist1_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_s, __xlx_sprintf_buffer.data());
  }
} else {
  long in_dist1_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist1_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist1_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_dist1_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist1_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist1_s, end_str());
}
long __xlx_apatb_param_in_dist1_peek_stream_buf_final_size = __xlx_apatb_param_in_dist1_peek_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek)->size();
// print in_dist1_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_dist1_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_dist1_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_dist1_peek_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_dist1_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_dist1_peek_stream_buf_final_size, &tcl_file.in_dist1_peek_depth);
aesl_fh.write(AUTOTB_TVIN_in_dist1_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_dist1_peek_stream_buf_final_size > 0) {
  long in_dist1_peek_stream_ingress_size = __xlx_apatb_param_in_dist1_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist1_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_dist1_peek_stream_buf_final_size; j != e; j++) {
    in_dist1_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist1_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long in_dist1_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist1_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist1_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist1_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_dist1_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist1_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist1_peek, end_str());
}
long __xlx_apatb_param_in_id1_s_stream_buf_final_size = __xlx_apatb_param_in_id1_s_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_id1_s)->size();
// print in_id1_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_id1_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_id1_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_id1_s_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_id1_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_id1_s_stream_buf_final_size, &tcl_file.in_id1_s_depth);
aesl_fh.write(AUTOTB_TVIN_in_id1_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_id1_s_stream_buf_final_size > 0) {
  long in_id1_s_stream_ingress_size = __xlx_apatb_param_in_id1_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id1_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_id1_s_stream_buf_final_size; j != e; j++) {
    in_id1_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id1_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_s, __xlx_sprintf_buffer.data());
  }
} else {
  long in_id1_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id1_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id1_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_id1_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id1_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id1_s, end_str());
}
long __xlx_apatb_param_in_id1_peek_stream_buf_final_size = __xlx_apatb_param_in_id1_peek_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek)->size();
// print in_id1_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_id1_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_id1_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_id1_peek_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_id1_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_id1_peek_stream_buf_final_size, &tcl_file.in_id1_peek_depth);
aesl_fh.write(AUTOTB_TVIN_in_id1_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_id1_peek_stream_buf_final_size > 0) {
  long in_id1_peek_stream_ingress_size = __xlx_apatb_param_in_id1_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id1_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_id1_peek_stream_buf_final_size; j != e; j++) {
    in_id1_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id1_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long in_id1_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id1_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id1_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id1_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_id1_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id1_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id1_peek, end_str());
}
long __xlx_apatb_param_in_dist2_s_stream_buf_final_size = __xlx_apatb_param_in_dist2_s_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s)->size();
// print in_dist2_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_dist2_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_dist2_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_dist2_s_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_dist2_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_dist2_s_stream_buf_final_size, &tcl_file.in_dist2_s_depth);
aesl_fh.write(AUTOTB_TVIN_in_dist2_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_dist2_s_stream_buf_final_size > 0) {
  long in_dist2_s_stream_ingress_size = __xlx_apatb_param_in_dist2_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist2_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_dist2_s_stream_buf_final_size; j != e; j++) {
    in_dist2_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist2_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_s, __xlx_sprintf_buffer.data());
  }
} else {
  long in_dist2_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist2_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist2_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_dist2_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist2_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist2_s, end_str());
}
long __xlx_apatb_param_in_dist2_peek_stream_buf_final_size = __xlx_apatb_param_in_dist2_peek_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek)->size();
// print in_dist2_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_dist2_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_dist2_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_dist2_peek_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_dist2_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_dist2_peek_stream_buf_final_size, &tcl_file.in_dist2_peek_depth);
aesl_fh.write(AUTOTB_TVIN_in_dist2_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_dist2_peek_stream_buf_final_size > 0) {
  long in_dist2_peek_stream_ingress_size = __xlx_apatb_param_in_dist2_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist2_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_dist2_peek_stream_buf_final_size; j != e; j++) {
    in_dist2_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist2_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long in_dist2_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_dist2_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_dist2_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist2_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_dist2_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist2_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_dist2_peek, end_str());
}
long __xlx_apatb_param_in_id2_s_stream_buf_final_size = __xlx_apatb_param_in_id2_s_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_id2_s)->size();
// print in_id2_s Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_id2_s, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_id2_s_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_id2_s_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_id2_s, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_id2_s_stream_buf_final_size, &tcl_file.in_id2_s_depth);
aesl_fh.write(AUTOTB_TVIN_in_id2_s, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_s, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_id2_s_stream_buf_final_size > 0) {
  long in_id2_s_stream_ingress_size = __xlx_apatb_param_in_id2_s_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id2_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_s, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_id2_s_stream_buf_final_size; j != e; j++) {
    in_id2_s_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id2_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_s, __xlx_sprintf_buffer.data());
  }
} else {
  long in_id2_s_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id2_s_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_s, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_s, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id2_s, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_id2_s_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id2_s, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id2_s, end_str());
}
long __xlx_apatb_param_in_id2_peek_stream_buf_final_size = __xlx_apatb_param_in_id2_peek_stream_buf_size - ((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek)->size();
// print in_id2_peek Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_id2_peek, begin_str(AESL_transaction));
for (int i = 0; i < __xlx_apatb_param_in_id2_peek_stream_buf_final_size; ++i) {
unsigned char *pos = (unsigned char*)(__xlx_apatb_param_in_id2_peek_stream_buf.data()+i);
std::string s(formatData(pos, 45));
aesl_fh.write(AUTOTB_TVIN_in_id2_peek, s);
}

  tcl_file.set_num(__xlx_apatb_param_in_id2_peek_stream_buf_final_size, &tcl_file.in_id2_peek_depth);
aesl_fh.write(AUTOTB_TVIN_in_id2_peek, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_peek, begin_str(AESL_transaction));
if (__xlx_apatb_param_in_id2_peek_stream_buf_final_size > 0) {
  long in_id2_peek_stream_ingress_size = __xlx_apatb_param_in_id2_peek_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id2_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_peek, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_id2_peek_stream_buf_final_size; j != e; j++) {
    in_id2_peek_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id2_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_peek, __xlx_sprintf_buffer.data());
  }
} else {
  long in_id2_peek_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_id2_peek_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_peek, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_id2_peek, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id2_peek, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_id2_peek_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id2_peek, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_id2_peek, end_str());
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
