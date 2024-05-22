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
unsigned int ap_apatb_a_s_cap_bc;
static AESL_RUNTIME_BC __xlx_a_s_V_size_Reader("../tv/stream_size/stream_size_in_a_s.dat");
unsigned int ap_apatb_a_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_a_peek_V_size_Reader("../tv/stream_size/stream_size_in_a_peek.dat");
unsigned int ap_apatb_b_s_cap_bc;
static AESL_RUNTIME_BC __xlx_b_s_V_size_Reader("../tv/stream_size/stream_size_in_b_s.dat");
unsigned int ap_apatb_b_peek_cap_bc;
static AESL_RUNTIME_BC __xlx_b_peek_V_size_Reader("../tv/stream_size/stream_size_in_b_peek.dat");
unsigned int ap_apatb_c_cap_bc;
static AESL_RUNTIME_BC __xlx_c_V_size_Reader("../tv/stream_size/stream_size_out_c.dat");
extern "C" void Add(long long*, long long*, long long*, long long*, long long*, long long);
extern "C" void apatb_Add_hw(volatile void * __xlx_apatb_param_a_s, volatile void * __xlx_apatb_param_a_peek, volatile void * __xlx_apatb_param_b_s, volatile void * __xlx_apatb_param_b_peek, volatile void * __xlx_apatb_param_c, long long __xlx_apatb_param_n) {
auto* sa_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_a_s);
auto* sa_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_a_peek);
auto* sb_s = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_b_s);
auto* sb_peek = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_b_peek);
  //Create input buffer for c
  ap_apatb_c_cap_bc = __xlx_c_V_size_Reader.read_size();
  long long* __xlx_c_input_buffer= new long long[ap_apatb_c_cap_bc];
auto* sc = bcsim::createStream((hls::stream<long long>*)__xlx_apatb_param_c);
  // DUT call
  Add(sa_s->data<long long>(), sa_peek->data<long long>(), sb_s->data<long long>(), sb_peek->data<long long>(), sc->data<long long>(), __xlx_apatb_param_n);
sa_s->transfer((hls::stream<long long>*)__xlx_apatb_param_a_s);
sa_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_a_peek);
sb_s->transfer((hls::stream<long long>*)__xlx_apatb_param_b_s);
sb_peek->transfer((hls::stream<long long>*)__xlx_apatb_param_b_peek);
sc->transfer((hls::stream<long long>*)__xlx_apatb_param_c);
}
