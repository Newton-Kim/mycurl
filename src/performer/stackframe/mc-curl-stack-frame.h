#pragma once
#include <string>

using namespace std;

class mcIStackFrame {
 public:
  virtual mcIStackFrame* open(string url, string alias) = 0;
  virtual void verbose(bool onoff) = 0;
  virtual bool verbose(void) = 0;
  virtual void follow(bool onoff) = 0;
  virtual bool follow(void) = 0;
  virtual void list(ostream& stream) = 0;
  virtual string mnymonic(void) = 0;
  virtual void get(string path) = 0;
  virtual void del(void) = 0;
  virtual void post(string inpath, bool chunk, string outpath) = 0;
  virtual void put(string inpath, bool chunk, string outpath) = 0;
  virtual void add(string key, string value) = 0;
  virtual void rm(string key) = 0;
};
