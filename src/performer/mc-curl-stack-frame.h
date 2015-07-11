#pragma once
#include <string>

using namespace std;

class mcIStackFrame {
 public:
  virtual void verbose(bool& onoff) = 0;
  virtual bool verbose(void) = 0;
  virtual void follow(bool& onoff) = 0;
  virtual bool follow(void) = 0;
  virtual void list(void) = 0;
  virtual string mnymonic(void) = 0;
  virtual void get(string path, string lst) = 0;
  virtual void del(string lst) = 0;
  virtual void post(string inpath, size_t chunk, string outpath, string lst, string frm) = 0;
  virtual void put(string inpath, size_t chunk, string outpath, string lst) = 0;
  virtual mcIStackFrame* header(void) = 0;
  virtual mcIStackFrame* form(void) = 0;
};
