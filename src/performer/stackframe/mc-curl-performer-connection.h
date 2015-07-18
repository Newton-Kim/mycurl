#pragma once
#include "mc-curl-stack-frame.h"
#include "mc-curl.h"

class mcCurlPerformerConnection : public mcIStackFrame{
 private:
  mcCurl* m_curl;

 public:
  mcCurlPerformerConnection(string url, string alias);
  ~mcCurlPerformerConnection();
  mcIStackFrame* open(string url, string alias);
  void verbose(bool onoff);
  bool verbose(void);
  void follow(bool onoff);
  bool follow(void);
  void list(ostream& stream);
  string mnymonic(void);
  void get(string path, string lst);
  void del(string lst);
  void post(string inpath, size_t chunk, string outpath, string lst, string frm);
  void put(string inpath, size_t chunk, string outpath, string lst);
};
