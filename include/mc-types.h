#pragma once

#include <string>

using namespace std;

typedef enum {
  MC_LANG_END,       //quit is called
  MC_LANG_ERROR,     //an error has happened
  MC_LANG_CONTINUE,  //continue to the next line
  MC_LANG_HANG       //end of the process but more input is expected
} mcLanguageState;

class mcIConnection {
 public:
  virtual string mnymonic(void) = 0;
  virtual void get(string path, string lst) = 0;
  virtual void del(string lst) = 0;
  virtual void post(string inpath, size_t chunk, string outpath, string lst) = 0;
  virtual void put(string inpath, size_t chunk, string outpath, string lst) = 0;
  virtual void verbose(bool onoff) = 0;
  virtual bool verbose(void) = 0;
  virtual void follow(bool onoff) = 0;
  virtual bool follow(void) = 0;
  virtual void header(string key, string value, string lst) = 0;
  virtual void form(string key, string value, string lst) = 0;
};

class mcIPerformer {
 public:
  virtual mcLanguageState open(string url, string alias) = 0;
  virtual mcLanguageState close(mcIConnection* conn) = 0;
  virtual mcLanguageState leave(void) = 0;
  virtual mcLanguageState list(void) = 0;
  virtual mcIConnection* current(void) = 0;
};
