#pragma once

#include <string>

using namespace std;

typedef enum {
  MC_LANG_END,       //quit is called
  MC_LANG_ERROR,     //an error has happened
  MC_LANG_CONTINUE,  //continue to the next line
  MC_LANG_HANG       //end of the process but more input is expected
} mcLanguageState;

class mcIPerformer {
 public:
  virtual void open(string url, string alias) = 0;
  virtual void close(void) = 0;
  virtual void leave(void) = 0;
  virtual void list(void) = 0;
  virtual string mnymonic(void) = 0;
  virtual void get(string path) = 0;
  virtual void del(void) = 0;
  virtual void post(string inpath, bool chunk, string outpath) = 0;
  virtual void put(string inpath, bool chunk, string outpath) = 0;
  virtual void verbose_on(void) = 0;
  virtual void verbose_off(void) = 0;
  virtual void verbose(bool& onoff) = 0;
  virtual void follow_on(void) = 0;
  virtual void follow_off(void) = 0;
  virtual void follow(bool& onoff) = 0;
  virtual void add(string key, string value) = 0;
  virtual void rm(string key) = 0;
};
