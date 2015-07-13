#pragma once
#include "mc-types.h"
#include "stackframe/mc-curl-stack-frame.h"
#include <vector>
#include <map>

using namespace std;

class mcCurlPerformer : public mcIPerformer {
 private:
  map<string, vector<mcIStackFrame*> > m_pool;
  vector<mcIStackFrame*>* m_stack;

 public:
  mcCurlPerformer();
  ~mcCurlPerformer();
  mcLanguageState open(string url, string alias);
  mcLanguageState close(void);
  mcLanguageState verbose(bool& onoff);
  mcLanguageState verbose_on(void);
  mcLanguageState verbose_off(void);
  mcLanguageState follow(bool& onoff);
  mcLanguageState follow_on(void);
  mcLanguageState follow_off(void);
  mcLanguageState leave(void);
  mcLanguageState list(void);
  string mnymonic(void);
  mcLanguageState get(string path, string lst);
  mcLanguageState del(string lst);
  mcLanguageState post(string inpath, size_t chunk, string outpath, string lst, string frm);
  mcLanguageState put(string inpath, size_t chunk, string outpath, string lst);
  bool follow(void);
};
