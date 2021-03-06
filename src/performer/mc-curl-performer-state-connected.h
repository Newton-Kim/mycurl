#pragma once
#include "mc-types.h"
#include "mc-curl-performer-context.h"
#include "stackframe/mc-curl-stack-frame.h"
#include <vector>
#include <map>

using namespace std;

class mcCurlPerformerStateConnected : public mcIPerformer {
 private:
  mcICurlPerformerContext* m_context;
  vector<mcIStackFrame*>* m_stack;

 public:
  mcCurlPerformerStateConnected(mcICurlPerformerContext* context,
                                vector<mcIStackFrame*>* stack);
  ~mcCurlPerformerStateConnected();
  void open(string url, string alias);
  void close(void);
  void verbose(bool& onoff);
  void verbose_on(void);
  void verbose_off(void);
  void follow(bool& onoff);
  void follow_on(void);
  void follow_off(void);
  void leave(void);
  void list(void);
  string mnymonic(void);
  void get(string path);
  void del(void);
  void post(string inpath, bool chunk, string outpath);
  void put(string inpath, bool chunk, string outpath);
  bool follow(void);
  void add(string key, string value);
  void rm(string key);
};
