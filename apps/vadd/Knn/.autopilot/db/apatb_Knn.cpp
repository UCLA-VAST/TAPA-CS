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
#define AUTOTB_TVIN_in_0 "../tv/cdatafile/c.Knn.autotvin_in_0.dat"
#define AUTOTB_TVOUT_in_0 "../tv/cdatafile/c.Knn.autotvout_in_0.dat"
#define AUTOTB_TVIN_in_1 "../tv/cdatafile/c.Knn.autotvin_in_1.dat"
#define AUTOTB_TVOUT_in_1 "../tv/cdatafile/c.Knn.autotvout_in_1.dat"
#define AUTOTB_TVIN_in_2 "../tv/cdatafile/c.Knn.autotvin_in_2.dat"
#define AUTOTB_TVOUT_in_2 "../tv/cdatafile/c.Knn.autotvout_in_2.dat"
#define AUTOTB_TVIN_in_3 "../tv/cdatafile/c.Knn.autotvin_in_3.dat"
#define AUTOTB_TVOUT_in_3 "../tv/cdatafile/c.Knn.autotvout_in_3.dat"
#define AUTOTB_TVIN_in_4 "../tv/cdatafile/c.Knn.autotvin_in_4.dat"
#define AUTOTB_TVOUT_in_4 "../tv/cdatafile/c.Knn.autotvout_in_4.dat"
#define AUTOTB_TVIN_in_5 "../tv/cdatafile/c.Knn.autotvin_in_5.dat"
#define AUTOTB_TVOUT_in_5 "../tv/cdatafile/c.Knn.autotvout_in_5.dat"
#define AUTOTB_TVIN_in_6 "../tv/cdatafile/c.Knn.autotvin_in_6.dat"
#define AUTOTB_TVOUT_in_6 "../tv/cdatafile/c.Knn.autotvout_in_6.dat"
#define AUTOTB_TVIN_in_7 "../tv/cdatafile/c.Knn.autotvin_in_7.dat"
#define AUTOTB_TVOUT_in_7 "../tv/cdatafile/c.Knn.autotvout_in_7.dat"
#define AUTOTB_TVIN_in_8 "../tv/cdatafile/c.Knn.autotvin_in_8.dat"
#define AUTOTB_TVOUT_in_8 "../tv/cdatafile/c.Knn.autotvout_in_8.dat"
#define AUTOTB_TVIN_in_9 "../tv/cdatafile/c.Knn.autotvin_in_9.dat"
#define AUTOTB_TVOUT_in_9 "../tv/cdatafile/c.Knn.autotvout_in_9.dat"
#define AUTOTB_TVIN_in_10 "../tv/cdatafile/c.Knn.autotvin_in_10.dat"
#define AUTOTB_TVOUT_in_10 "../tv/cdatafile/c.Knn.autotvout_in_10.dat"
#define AUTOTB_TVIN_in_11 "../tv/cdatafile/c.Knn.autotvin_in_11.dat"
#define AUTOTB_TVOUT_in_11 "../tv/cdatafile/c.Knn.autotvout_in_11.dat"
#define AUTOTB_TVIN_in_12 "../tv/cdatafile/c.Knn.autotvin_in_12.dat"
#define AUTOTB_TVOUT_in_12 "../tv/cdatafile/c.Knn.autotvout_in_12.dat"
#define AUTOTB_TVIN_in_13 "../tv/cdatafile/c.Knn.autotvin_in_13.dat"
#define AUTOTB_TVOUT_in_13 "../tv/cdatafile/c.Knn.autotvout_in_13.dat"
#define AUTOTB_TVIN_in_14 "../tv/cdatafile/c.Knn.autotvin_in_14.dat"
#define AUTOTB_TVOUT_in_14 "../tv/cdatafile/c.Knn.autotvout_in_14.dat"
#define AUTOTB_TVIN_in_15 "../tv/cdatafile/c.Knn.autotvin_in_15.dat"
#define AUTOTB_TVOUT_in_15 "../tv/cdatafile/c.Knn.autotvout_in_15.dat"
#define AUTOTB_TVIN_in_16 "../tv/cdatafile/c.Knn.autotvin_in_16.dat"
#define AUTOTB_TVOUT_in_16 "../tv/cdatafile/c.Knn.autotvout_in_16.dat"
#define AUTOTB_TVIN_in_17 "../tv/cdatafile/c.Knn.autotvin_in_17.dat"
#define AUTOTB_TVOUT_in_17 "../tv/cdatafile/c.Knn.autotvout_in_17.dat"
#define AUTOTB_TVIN_L3_out_dist "../tv/cdatafile/c.Knn.autotvin_L3_out_dist.dat"
#define AUTOTB_TVOUT_L3_out_dist "../tv/cdatafile/c.Knn.autotvout_L3_out_dist.dat"
#define AUTOTB_TVIN_L3_out_id "../tv/cdatafile/c.Knn.autotvin_L3_out_id.dat"
#define AUTOTB_TVOUT_L3_out_id "../tv/cdatafile/c.Knn.autotvout_L3_out_id.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_in_0 "../tv/rtldatafile/rtl.Knn.autotvout_in_0.dat"
#define AUTOTB_TVOUT_PC_in_1 "../tv/rtldatafile/rtl.Knn.autotvout_in_1.dat"
#define AUTOTB_TVOUT_PC_in_2 "../tv/rtldatafile/rtl.Knn.autotvout_in_2.dat"
#define AUTOTB_TVOUT_PC_in_3 "../tv/rtldatafile/rtl.Knn.autotvout_in_3.dat"
#define AUTOTB_TVOUT_PC_in_4 "../tv/rtldatafile/rtl.Knn.autotvout_in_4.dat"
#define AUTOTB_TVOUT_PC_in_5 "../tv/rtldatafile/rtl.Knn.autotvout_in_5.dat"
#define AUTOTB_TVOUT_PC_in_6 "../tv/rtldatafile/rtl.Knn.autotvout_in_6.dat"
#define AUTOTB_TVOUT_PC_in_7 "../tv/rtldatafile/rtl.Knn.autotvout_in_7.dat"
#define AUTOTB_TVOUT_PC_in_8 "../tv/rtldatafile/rtl.Knn.autotvout_in_8.dat"
#define AUTOTB_TVOUT_PC_in_9 "../tv/rtldatafile/rtl.Knn.autotvout_in_9.dat"
#define AUTOTB_TVOUT_PC_in_10 "../tv/rtldatafile/rtl.Knn.autotvout_in_10.dat"
#define AUTOTB_TVOUT_PC_in_11 "../tv/rtldatafile/rtl.Knn.autotvout_in_11.dat"
#define AUTOTB_TVOUT_PC_in_12 "../tv/rtldatafile/rtl.Knn.autotvout_in_12.dat"
#define AUTOTB_TVOUT_PC_in_13 "../tv/rtldatafile/rtl.Knn.autotvout_in_13.dat"
#define AUTOTB_TVOUT_PC_in_14 "../tv/rtldatafile/rtl.Knn.autotvout_in_14.dat"
#define AUTOTB_TVOUT_PC_in_15 "../tv/rtldatafile/rtl.Knn.autotvout_in_15.dat"
#define AUTOTB_TVOUT_PC_in_16 "../tv/rtldatafile/rtl.Knn.autotvout_in_16.dat"
#define AUTOTB_TVOUT_PC_in_17 "../tv/rtldatafile/rtl.Knn.autotvout_in_17.dat"
#define AUTOTB_TVOUT_PC_L3_out_dist "../tv/rtldatafile/rtl.Knn.autotvout_L3_out_dist.dat"
#define AUTOTB_TVOUT_PC_L3_out_id "../tv/rtldatafile/rtl.Knn.autotvout_L3_out_id.dat"


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
  in_0_depth = 0;
  in_1_depth = 0;
  in_2_depth = 0;
  in_3_depth = 0;
  in_4_depth = 0;
  in_5_depth = 0;
  in_6_depth = 0;
  in_7_depth = 0;
  in_8_depth = 0;
  in_9_depth = 0;
  in_10_depth = 0;
  in_11_depth = 0;
  in_12_depth = 0;
  in_13_depth = 0;
  in_14_depth = 0;
  in_15_depth = 0;
  in_16_depth = 0;
  in_17_depth = 0;
  L3_out_dist_depth = 0;
  L3_out_id_depth = 0;
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
  total_list << "{in_0 " << in_0_depth << "}\n";
  total_list << "{in_1 " << in_1_depth << "}\n";
  total_list << "{in_2 " << in_2_depth << "}\n";
  total_list << "{in_3 " << in_3_depth << "}\n";
  total_list << "{in_4 " << in_4_depth << "}\n";
  total_list << "{in_5 " << in_5_depth << "}\n";
  total_list << "{in_6 " << in_6_depth << "}\n";
  total_list << "{in_7 " << in_7_depth << "}\n";
  total_list << "{in_8 " << in_8_depth << "}\n";
  total_list << "{in_9 " << in_9_depth << "}\n";
  total_list << "{in_10 " << in_10_depth << "}\n";
  total_list << "{in_11 " << in_11_depth << "}\n";
  total_list << "{in_12 " << in_12_depth << "}\n";
  total_list << "{in_13 " << in_13_depth << "}\n";
  total_list << "{in_14 " << in_14_depth << "}\n";
  total_list << "{in_15 " << in_15_depth << "}\n";
  total_list << "{in_16 " << in_16_depth << "}\n";
  total_list << "{in_17 " << in_17_depth << "}\n";
  total_list << "{L3_out_dist " << L3_out_dist_depth << "}\n";
  total_list << "{L3_out_id " << L3_out_id_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int in_0_depth;
    int in_1_depth;
    int in_2_depth;
    int in_3_depth;
    int in_4_depth;
    int in_5_depth;
    int in_6_depth;
    int in_7_depth;
    int in_8_depth;
    int in_9_depth;
    int in_10_depth;
    int in_11_depth;
    int in_12_depth;
    int in_13_depth;
    int in_14_depth;
    int in_15_depth;
    int in_16_depth;
    int in_17_depth;
    int L3_out_dist_depth;
    int L3_out_id_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


extern "C" void Knn_hw_stub_wrapper(long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long, long long);

extern "C" void apatb_Knn_hw(long long __xlx_apatb_param_in_0, long long __xlx_apatb_param_in_1, long long __xlx_apatb_param_in_2, long long __xlx_apatb_param_in_3, long long __xlx_apatb_param_in_4, long long __xlx_apatb_param_in_5, long long __xlx_apatb_param_in_6, long long __xlx_apatb_param_in_7, long long __xlx_apatb_param_in_8, long long __xlx_apatb_param_in_9, long long __xlx_apatb_param_in_10, long long __xlx_apatb_param_in_11, long long __xlx_apatb_param_in_12, long long __xlx_apatb_param_in_13, long long __xlx_apatb_param_in_14, long long __xlx_apatb_param_in_15, long long __xlx_apatb_param_in_16, long long __xlx_apatb_param_in_17, long long __xlx_apatb_param_L3_out_dist, long long __xlx_apatb_param_L3_out_id) {
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

    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
CodeState = DUMP_INPUTS;
// print in_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_0, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_0;
aesl_fh.write(AUTOTB_TVIN_in_0, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_0_depth);
aesl_fh.write(AUTOTB_TVIN_in_0, end_str());
}

// print in_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_1, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_1;
aesl_fh.write(AUTOTB_TVIN_in_1, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_1_depth);
aesl_fh.write(AUTOTB_TVIN_in_1, end_str());
}

// print in_2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_2, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_2;
aesl_fh.write(AUTOTB_TVIN_in_2, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_2_depth);
aesl_fh.write(AUTOTB_TVIN_in_2, end_str());
}

// print in_3 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_3, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_3;
aesl_fh.write(AUTOTB_TVIN_in_3, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_3_depth);
aesl_fh.write(AUTOTB_TVIN_in_3, end_str());
}

// print in_4 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_4, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_4;
aesl_fh.write(AUTOTB_TVIN_in_4, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_4_depth);
aesl_fh.write(AUTOTB_TVIN_in_4, end_str());
}

// print in_5 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_5, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_5;
aesl_fh.write(AUTOTB_TVIN_in_5, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_5_depth);
aesl_fh.write(AUTOTB_TVIN_in_5, end_str());
}

// print in_6 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_6, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_6;
aesl_fh.write(AUTOTB_TVIN_in_6, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_6_depth);
aesl_fh.write(AUTOTB_TVIN_in_6, end_str());
}

// print in_7 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_7, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_7;
aesl_fh.write(AUTOTB_TVIN_in_7, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_7_depth);
aesl_fh.write(AUTOTB_TVIN_in_7, end_str());
}

// print in_8 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_8, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_8;
aesl_fh.write(AUTOTB_TVIN_in_8, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_8_depth);
aesl_fh.write(AUTOTB_TVIN_in_8, end_str());
}

// print in_9 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_9, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_9;
aesl_fh.write(AUTOTB_TVIN_in_9, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_9_depth);
aesl_fh.write(AUTOTB_TVIN_in_9, end_str());
}

// print in_10 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_10, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_10;
aesl_fh.write(AUTOTB_TVIN_in_10, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_10_depth);
aesl_fh.write(AUTOTB_TVIN_in_10, end_str());
}

// print in_11 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_11, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_11;
aesl_fh.write(AUTOTB_TVIN_in_11, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_11_depth);
aesl_fh.write(AUTOTB_TVIN_in_11, end_str());
}

// print in_12 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_12, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_12;
aesl_fh.write(AUTOTB_TVIN_in_12, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_12_depth);
aesl_fh.write(AUTOTB_TVIN_in_12, end_str());
}

// print in_13 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_13, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_13;
aesl_fh.write(AUTOTB_TVIN_in_13, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_13_depth);
aesl_fh.write(AUTOTB_TVIN_in_13, end_str());
}

// print in_14 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_14, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_14;
aesl_fh.write(AUTOTB_TVIN_in_14, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_14_depth);
aesl_fh.write(AUTOTB_TVIN_in_14, end_str());
}

// print in_15 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_15, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_15;
aesl_fh.write(AUTOTB_TVIN_in_15, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_15_depth);
aesl_fh.write(AUTOTB_TVIN_in_15, end_str());
}

// print in_16 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_16, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_16;
aesl_fh.write(AUTOTB_TVIN_in_16, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_16_depth);
aesl_fh.write(AUTOTB_TVIN_in_16, end_str());
}

// print in_17 Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_17, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_in_17;
aesl_fh.write(AUTOTB_TVIN_in_17, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.in_17_depth);
aesl_fh.write(AUTOTB_TVIN_in_17, end_str());
}

// print L3_out_dist Transactions
{
aesl_fh.write(AUTOTB_TVIN_L3_out_dist, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_L3_out_dist;
aesl_fh.write(AUTOTB_TVIN_L3_out_dist, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.L3_out_dist_depth);
aesl_fh.write(AUTOTB_TVIN_L3_out_dist, end_str());
}

// print L3_out_id Transactions
{
aesl_fh.write(AUTOTB_TVIN_L3_out_id, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_L3_out_id;
aesl_fh.write(AUTOTB_TVIN_L3_out_id, formatData(pos, 64));
}
  tcl_file.set_num(1, &tcl_file.L3_out_id_depth);
aesl_fh.write(AUTOTB_TVIN_L3_out_id, end_str());
}

CodeState = CALL_C_DUT;
Knn_hw_stub_wrapper(__xlx_apatb_param_in_0, __xlx_apatb_param_in_1, __xlx_apatb_param_in_2, __xlx_apatb_param_in_3, __xlx_apatb_param_in_4, __xlx_apatb_param_in_5, __xlx_apatb_param_in_6, __xlx_apatb_param_in_7, __xlx_apatb_param_in_8, __xlx_apatb_param_in_9, __xlx_apatb_param_in_10, __xlx_apatb_param_in_11, __xlx_apatb_param_in_12, __xlx_apatb_param_in_13, __xlx_apatb_param_in_14, __xlx_apatb_param_in_15, __xlx_apatb_param_in_16, __xlx_apatb_param_in_17, __xlx_apatb_param_L3_out_dist, __xlx_apatb_param_L3_out_id);
CodeState = DUMP_OUTPUTS;
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
