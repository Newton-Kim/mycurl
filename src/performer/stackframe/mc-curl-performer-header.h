#pragma once
#include "mc-curl-stack-frame.h"
#include "mc-curl-header.h"

class mcCurlPerformerHeader : public mcIStackFrame {
 private:
  mcCurlHeader* m_header;
  string m_mnymonic;

 public:
  mcCurlPerformerHeader(mcCurlHeader* header, string mnymonic);
  mcIStackFrame* open(string url, string alias);
  void verbose(bool onoff);
  bool verbose(void);
  void follow(bool onoff);
  bool follow(void);
  void list(ostream& stream);
  string mnymonic(void);
  void get(string path);
  void del(void);
  void post(string inpath, bool chunk, string outpath);
  void put(string inpath, bool chunk, string outpath);
  void add(string key, string value);
  void rm(string key);
};
