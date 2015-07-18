#pragma once
#include "mc-types.h"
#include "mc-curl-performer-context.h"
#include "stackframe/mc-curl-stack-frame.h"
#include <vector>
#include <map>

using namespace std;

class mcCurlPerformer : public mcIPerformer, public mcICurlPerformerContext {
 private:
  mcIPerformer* m_state_root;
  mcIPerformer* m_state_connected;
  mcIPerformer* m_current_state;

 public:
  mcCurlPerformer();
  ~mcCurlPerformer();
  void set_context(mcContextState state, vector<mcIStackFrame*>* stack);
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
  void get(string path, string lst);
  void del(string lst);
  void post(string inpath, size_t chunk, string outpath, string lst, string frm);
  void put(string inpath, size_t chunk, string outpath, string lst);
  bool follow(void);
};
