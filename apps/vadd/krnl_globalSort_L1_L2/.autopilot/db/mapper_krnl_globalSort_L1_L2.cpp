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
unsigned int ap_apatb_in_dist2_s_cap_bc;
static AESL_RUNTIME_BC __xlx_in_dist2_s_V_size_Reader("../tv/stream_size/stream_size_in_in_dist2_s.dat");
unsigned int ap_apatb_in_dist2_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_in_dist2_peek_V_size_Reader("../tv/stream_size/stream_size_in_in_dist2_peek.dat");
unsigned int ap_apatb_in_id2_s_cap_bc;
static AESL_RUNTIME_BC __xlx_in_id2_s_V_size_Reader("../tv/stream_size/stream_size_in_in_id2_s.dat");
unsigned int ap_apatb_in_id2_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_in_id2_peek_V_size_Reader("../tv/stream_size/stream_size_in_in_id2_peek.dat");
unsigned int ap_apatb_out_dist_cap_bc;
static AESL_RUNTIME_BC __xlx_out_dist_V_size_Reader("../tv/stream_size/stream_size_out_out_dist.dat");
unsigned int ap_apatb_out_id_cap_bc;
static AESL_RUNTIME_BC __xlx_out_id_V_size_Reader("../tv/stream_size/stream_size_out_out_id.dat");
extern "C" void krnl_globalSort_L1_L2(long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*, long long*);
extern "C" void apatb_krnl_globalSort_L1_L2_hw(volatile void * __xlx_apatb_param_in_dist0_s, volatile void * __xlx_apatb_param_in_dist0_peek, volatile void * __xlx_apatb_param_in_id0_s, volatile void * __xlx_apatb_param_in_id0_peek, volatile void * __xlx_apatb_param_in_dist1_s, volatile void * __xlx_apatb_param_in_dist1_peek, volatile void * __xlx_apatb_param_in_id1_s, volatile void * __xlx_apatb_param_in_id1_peek, volatile void * __xlx_apatb_param_in_dist2_s, volatile void * __xlx_apatb_param_in_dist2_peek, volatile void * __xlx_apatb_param_in_id2_s, volatile void * __xlx_apatb_param_in_id2_peek, volatile void * __xlx_apatb_param_out_dist, volatile void * __xlx_apatb_param_out_id) {
auto* sin_dist0_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s);
auto* sin_dist0_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek);
auto* sin_id0_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id0_s);
auto* sin_id0_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek);
auto* sin_dist1_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s);
auto* sin_dist1_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek);
auto* sin_id1_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id1_s);
auto* sin_id1_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek);
auto* sin_dist2_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s);
auto* sin_dist2_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek);
auto* sin_id2_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id2_s);
auto* sin_id2_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek);
  //Create input buffer for out_dist
  ap_apatb_out_dist_cap_bc = __xlx_out_dist_V_size_Reader.read_size();
  long long* __xlx_out_dist_input_buffer= new long long[ap_apatb_out_dist_cap_bc];
auto* sout_dist = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_out_dist);
  //Create input buffer for out_id
  ap_apatb_out_id_cap_bc = __xlx_out_id_V_size_Reader.read_size();
  long long* __xlx_out_id_input_buffer= new long long[ap_apatb_out_id_cap_bc];
auto* sout_id = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_out_id);
  // DUT call
  krnl_globalSort_L1_L2(sin_dist0_s->data<long long>(), sin_dist0_peek->data<long long>(), sin_id0_s->data<long long>(), sin_id0_peek->data<long long>(), sin_dist1_s->data<long long>(), sin_dist1_peek->data<long long>(), sin_id1_s->data<long long>(), sin_id1_peek->data<long long>(), sin_dist2_s->data<long long>(), sin_dist2_peek->data<long long>(), sin_id2_s->data<long long>(), sin_id2_peek->data<long long>(), sout_dist->data<long long>(), sout_id->data<long long>());
sin_dist0_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist0_s);
sin_dist0_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist0_peek);
sin_id0_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id0_s);
sin_id0_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id0_peek);
sin_dist1_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist1_s);
sin_dist1_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist1_peek);
sin_id1_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id1_s);
sin_id1_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id1_peek);
sin_dist2_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist2_s);
sin_dist2_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_dist2_peek);
sin_id2_s->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id2_s);
sin_id2_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_in_id2_peek);
sout_dist->transfer((hls::stream<long long>*)__xlx_apatb_param_out_dist);
sout_id->transfer((hls::stream<long long>*)__xlx_apatb_param_out_id);
}
