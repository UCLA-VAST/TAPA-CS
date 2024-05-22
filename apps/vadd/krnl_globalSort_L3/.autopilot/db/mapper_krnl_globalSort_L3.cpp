#include <systemc>
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;

namespace bcsim
{
  struct Buffer {
    char *first;
    Buffer(char *addr) : first(addr)
    {
    }
  };

  struct DBuffer : public Buffer {
    size_t ufree;

    DBuffer(size_t usize) : Buffer(nullptr), ufree(1<<10)
    {
      first = new char[usize*ufree];
    }

    ~DBuffer()
    {
      delete[] first;
    }
  };

  struct CStream {
    char *front;
    char *back;
    size_t num;
    size_t usize;
    std::list<Buffer*> bufs;
    bool dynamic;

    CStream() : front(nullptr), back(nullptr),
                num(0), usize(0), dynamic(true)
    {
    }

    ~CStream()
    {
      for (Buffer *p : bufs) {
        delete p;
      }
    }

    template<typename T>
    T* data()
    {
      return (T*)front;
    }

    template<typename T>
    void transfer(hls::stream<T> *param)
    {
      while (!empty()) {
        param->write(*(T*)nextRead());
      }
    }

    bool empty();
    char* nextRead();
    char* nextWrite();
  };

  bool CStream::empty()
  {
    return num == 0;
  }

  char* CStream::nextRead()
  {
    assert(num > 0);
    char *res = front;
    front += usize;
    --num;
    return res;
  }

  char* CStream::nextWrite()
  {
    if (dynamic) {
      if (static_cast<DBuffer*>(bufs.back())->ufree == 0) {
        bufs.push_back(new DBuffer(usize));
        back = bufs.back()->first;
      }
      --static_cast<DBuffer*>(bufs.back())->ufree;
    }
    char *res = back;
    back += usize;
    ++num;
    return res;
  }

  std::list<CStream> streams;
  std::map<char*, CStream*> prebuilt;

  CStream* createStream(size_t usize)
  {
    streams.emplace_front();
    CStream &s = streams.front();
    {
      s.dynamic = true;
      s.bufs.push_back(new DBuffer(usize));
      s.front = s.bufs.back()->first;
      s.back = s.front;
      s.num = 0;
      s.usize = usize;
    }
    return &s;
  }

  template<typename T>
  CStream* createStream(hls::stream<T> *param)
  {
    CStream *s = createStream(sizeof(T));
    {
      s->dynamic = true;
      while (!param->empty()) {
        T data = param->read();
        memcpy(s->nextWrite(), (char*)&data, sizeof(T));
      }
      prebuilt[s->front] = s;
    }
    return s;
  }

  template<typename T>
  CStream* createStream(T *param, size_t usize)
  {
    streams.emplace_front();
    CStream &s = streams.front();
    {
      s.dynamic = false;
      s.bufs.push_back(new Buffer((char*)param));
      s.front = s.back = s.bufs.back()->first;
      s.usize = usize;
      s.num = ~0UL;
    }
    prebuilt[s.front] = &s;
    return &s;
  }

  CStream* findStream(char *buf)
  {
    return prebuilt.at(buf);
  }
}
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
unsigned int ap_apatb_in_dist0_s_cap_bc;
static AESL_RUNTIME_BC __xlx_in_dist0_s_V_size_Reader("../tv/stream_size/stream_size_in_in_dist0_s.dat");
unsigned int ap_apatb_in_dist0_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_in_dist0_peek_V_size_Reader("../tv/stream_size/stream_size_in_in_dist0_peek.dat");
unsigned int ap_apatb_in_id0_s_cap_bc;
static AESL_RUNTIME_BC __xlx_in_id0_s_V_size_Reader("../tv/stream_size/stream_size_in_in_id0_s.dat");
unsigned int ap_apatb_in_id0_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_in_id0_peek_V_size_Reader("../tv/stream_size/stream_size_in_in_id0_peek.dat");
unsigned int ap_apatb_in_dist1_s_cap_bc;
static AESL_RUNTIME_BC __xlx_in_dist1_s_V_size_Reader("../tv/stream_size/stream_size_in_in_dist1_s.dat");
unsigned int ap_apatb_in_dist1_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_in_dist1_peek_V_size_Reader("../tv/stream_size/stream_size_in_in_dist1_peek.dat");
unsigned int ap_apatb_in_id1_s_cap_bc;
static AESL_RUNTIME_BC __xlx_in_id1_s_V_size_Reader("../tv/stream_size/stream_size_in_in_id1_s.dat");
unsigned int ap_apatb_in_id1_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_in_id1_peek_V_size_Reader("../tv/stream_size/stream_size_in_in_id1_peek.dat");
unsigned int ap_apatb_output_knnDist_read_addr_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnDist_read_addr_V_size_Reader("../tv/stream_size/stream_size_out_output_knnDist_read_addr.dat");
unsigned int ap_apatb_output_knnDist_read_data_s_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnDist_read_data_s_V_size_Reader("../tv/stream_size/stream_size_in_output_knnDist_read_data_s.dat");
unsigned int ap_apatb_output_knnDist_read_data_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnDist_read_data_peek_V_size_Reader("../tv/stream_size/stream_size_in_output_knnDist_read_data_peek.dat");
unsigned int ap_apatb_output_knnDist_write_addr_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnDist_write_addr_V_size_Reader("../tv/stream_size/stream_size_out_output_knnDist_write_addr.dat");
unsigned int ap_apatb_output_knnDist_write_data_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnDist_write_data_V_size_Reader("../tv/stream_size/stream_size_out_output_knnDist_write_data.dat");
unsigned int ap_apatb_output_knnDist_write_resp_s_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnDist_write_resp_s_V_size_Reader("../tv/stream_size/stream_size_in_output_knnDist_write_resp_s.dat");
unsigned int ap_apatb_output_knnDist_write_resp_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnDist_write_resp_peek_V_size_Reader("../tv/stream_size/stream_size_in_output_knnDist_write_resp_peek.dat");
unsigned int ap_apatb_output_knnId_read_addr_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnId_read_addr_V_size_Reader("../tv/stream_size/stream_size_out_output_knnId_read_addr.dat");
unsigned int ap_apatb_output_knnId_read_data_s_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnId_read_data_s_V_size_Reader("../tv/stream_size/stream_size_in_output_knnId_read_data_s.dat");
unsigned int ap_apatb_output_knnId_read_data_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnId_read_data_peek_V_size_Reader("../tv/stream_size/stream_size_in_output_knnId_read_data_peek.dat");
unsigned int ap_apatb_output_knnId_write_addr_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnId_write_addr_V_size_Reader("../tv/stream_size/stream_size_out_output_knnId_write_addr.dat");
unsigned int ap_apatb_output_knnId_write_data_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnId_write_data_V_size_Reader("../tv/stream_size/stream_size_out_output_knnId_write_data.dat");
unsigned int ap_apatb_output_knnId_write_resp_s_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnId_write_resp_s_V_size_Reader("../tv/stream_size/stream_size_in_output_knnId_write_resp_s.dat");
unsigned int ap_apatb_output_knnId_write_resp_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_output_knnId_write_resp_peek_V_size_Reader("../tv/stream_size/stream_size_in_output_knnId_write_resp_peek.dat");
struct __cosim_s9__ { char data[16]; };
struct __cosim_s16__ { char data[16]; };
extern "C" void krnl_globalSort_L3(long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*, __cosim_s9__*, long long*, long long*, __cosim_s9__*, long long*, short*, short*, __cosim_s9__*, long long*, long long*, __cosim_s9__*, long long*, short*, short*);
extern "C" void apatb_krnl_globalSort_L3_hw(volatile void * __xlx_apatb_param_in_dist0_s, volatile void * __xlx_apatb_param_in_dist0_peek, volatile void * __xlx_apatb_param_in_id0_s, volatile void * __xlx_apatb_param_in_id0_peek, volatile void * __xlx_apatb_param_in_dist1_s, volatile void * __xlx_apatb_param_in_dist1_peek, volatile void * __xlx_apatb_param_in_id1_s, volatile void * __xlx_apatb_param_in_id1_peek, volatile void * __xlx_apatb_param_output_knnDist_read_addr, volatile void * __xlx_apatb_param_output_knnDist_read_data_s, volatile void * __xlx_apatb_param_output_knnDist_read_data_peek, volatile void * __xlx_apatb_param_output_knnDist_write_addr, volatile void * __xlx_apatb_param_output_knnDist_write_data, volatile void * __xlx_apatb_param_output_knnDist_write_resp_s, volatile void * __xlx_apatb_param_output_knnDist_write_resp_peek, volatile void * __xlx_apatb_param_output_knnId_read_addr, volatile void * __xlx_apatb_param_output_knnId_read_data_s, volatile void * __xlx_apatb_param_output_knnId_read_data_peek, volatile void * __xlx_apatb_param_output_knnId_write_addr, volatile void * __xlx_apatb_param_output_knnId_write_data, volatile void * __xlx_apatb_param_output_knnId_write_resp_s, volatile void * __xlx_apatb_param_output_knnId_write_resp_peek) {
auto* sin_dist0_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s);
auto* sin_dist0_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek);
auto* sin_id0_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id0_s);
auto* sin_id0_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek);
auto* sin_dist1_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s);
auto* sin_dist1_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek);
auto* sin_id1_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id1_s);
auto* sin_id1_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek);
  //Create input buffer for output_knnDist_read_addr
  ap_apatb_output_knnDist_read_addr_cap_bc = __xlx_output_knnDist_read_addr_V_size_Reader.read_size();
  __cosim_s9__* __xlx_output_knnDist_read_addr_input_buffer= new __cosim_s9__[ap_apatb_output_knnDist_read_addr_cap_bc];
auto* soutput_knnDist_read_addr = bcsim::createStream((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnDist_read_addr);
auto* soutput_knnDist_read_data_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_output_knnDist_read_data_s);
auto* soutput_knnDist_read_data_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_output_knnDist_read_data_peek);
  //Create input buffer for output_knnDist_write_addr
  ap_apatb_output_knnDist_write_addr_cap_bc = __xlx_output_knnDist_write_addr_V_size_Reader.read_size();
  __cosim_s9__* __xlx_output_knnDist_write_addr_input_buffer= new __cosim_s9__[ap_apatb_output_knnDist_write_addr_cap_bc];
auto* soutput_knnDist_write_addr = bcsim::createStream((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnDist_write_addr);
  //Create input buffer for output_knnDist_write_data
  ap_apatb_output_knnDist_write_data_cap_bc = __xlx_output_knnDist_write_data_V_size_Reader.read_size();
  long long* __xlx_output_knnDist_write_data_input_buffer= new long long[ap_apatb_output_knnDist_write_data_cap_bc];
auto* soutput_knnDist_write_data = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_output_knnDist_write_data);
auto* soutput_knnDist_write_resp_s = bcsim::createStream((hls::stream<short>*)__xlx_apatb_param_output_knnDist_write_resp_s);
auto* soutput_knnDist_write_resp_peek = bcsim::createStream((hls::stream<short>*)__xlx_apatb_param_output_knnDist_write_resp_peek);
  //Create input buffer for output_knnId_read_addr
  ap_apatb_output_knnId_read_addr_cap_bc = __xlx_output_knnId_read_addr_V_size_Reader.read_size();
  __cosim_s9__* __xlx_output_knnId_read_addr_input_buffer= new __cosim_s9__[ap_apatb_output_knnId_read_addr_cap_bc];
auto* soutput_knnId_read_addr = bcsim::createStream((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnId_read_addr);
auto* soutput_knnId_read_data_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_output_knnId_read_data_s);
auto* soutput_knnId_read_data_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_output_knnId_read_data_peek);
  //Create input buffer for output_knnId_write_addr
  ap_apatb_output_knnId_write_addr_cap_bc = __xlx_output_knnId_write_addr_V_size_Reader.read_size();
  __cosim_s9__* __xlx_output_knnId_write_addr_input_buffer= new __cosim_s9__[ap_apatb_output_knnId_write_addr_cap_bc];
auto* soutput_knnId_write_addr = bcsim::createStream((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnId_write_addr);
  //Create input buffer for output_knnId_write_data
  ap_apatb_output_knnId_write_data_cap_bc = __xlx_output_knnId_write_data_V_size_Reader.read_size();
  long long* __xlx_output_knnId_write_data_input_buffer= new long long[ap_apatb_output_knnId_write_data_cap_bc];
auto* soutput_knnId_write_data = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_output_knnId_write_data);
auto* soutput_knnId_write_resp_s = bcsim::createStream((hls::stream<short>*)__xlx_apatb_param_output_knnId_write_resp_s);
auto* soutput_knnId_write_resp_peek = bcsim::createStream((hls::stream<short>*)__xlx_apatb_param_output_knnId_write_resp_peek);
  // DUT call
  krnl_globalSort_L3(sin_dist0_s->data<long long>(), sin_dist0_peek->data<long long>(), sin_id0_s->data<long long>(), sin_id0_peek->data<long long>(), sin_dist1_s->data<long long>(), sin_dist1_peek->data<long long>(), sin_id1_s->data<long long>(), sin_id1_peek->data<long long>(), soutput_knnDist_read_addr->data<__cosim_s9__>(), soutput_knnDist_read_data_s->data<long long>(), soutput_knnDist_read_data_peek->data<long long>(), soutput_knnDist_write_addr->data<__cosim_s9__>(), soutput_knnDist_write_data->data<long long>(), soutput_knnDist_write_resp_s->data<short>(), soutput_knnDist_write_resp_peek->data<short>(), soutput_knnId_read_addr->data<__cosim_s9__>(), soutput_knnId_read_data_s->data<long long>(), soutput_knnId_read_data_peek->data<long long>(), soutput_knnId_write_addr->data<__cosim_s9__>(), soutput_knnId_write_data->data<long long>(), soutput_knnId_write_resp_s->data<short>(), soutput_knnId_write_resp_peek->data<short>());
sin_dist0_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s);
sin_dist0_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek);
sin_id0_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id0_s);
sin_id0_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek);
sin_dist1_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s);
sin_dist1_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek);
sin_id1_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id1_s);
sin_id1_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek);
soutput_knnDist_read_addr->transfer((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnDist_read_addr);
soutput_knnDist_read_data_s->transfer((hls::stream<long long>*)__xlx_apatb_param_output_knnDist_read_data_s);
soutput_knnDist_read_data_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_output_knnDist_read_data_peek);
soutput_knnDist_write_addr->transfer((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnDist_write_addr);
soutput_knnDist_write_data->transfer((hls::stream<long long>*)__xlx_apatb_param_output_knnDist_write_data);
soutput_knnDist_write_resp_s->transfer((hls::stream<short>*)__xlx_apatb_param_output_knnDist_write_resp_s);
soutput_knnDist_write_resp_peek->transfer((hls::stream<short>*)__xlx_apatb_param_output_knnDist_write_resp_peek);
soutput_knnId_read_addr->transfer((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnId_read_addr);
soutput_knnId_read_data_s->transfer((hls::stream<long long>*)__xlx_apatb_param_output_knnId_read_data_s);
soutput_knnId_read_data_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_output_knnId_read_data_peek);
soutput_knnId_write_addr->transfer((hls::stream<__cosim_s9__>*)__xlx_apatb_param_output_knnId_write_addr);
soutput_knnId_write_data->transfer((hls::stream<long long>*)__xlx_apatb_param_output_knnId_write_data);
soutput_knnId_write_resp_s->transfer((hls::stream<short>*)__xlx_apatb_param_output_knnId_write_resp_s);
soutput_knnId_write_resp_peek->transfer((hls::stream<short>*)__xlx_apatb_param_output_knnId_write_resp_peek);
}
