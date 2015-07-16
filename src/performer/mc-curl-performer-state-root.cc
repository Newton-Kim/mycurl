#include "mc-curl-performer.h"
#include "mc-curl-performer-state-root.h"
#include "stackframe/mc-curl-performer-connection.h"
#include <cstdio>

mcCurlPerformerStateRoot::mcCurlPerformerStateRoot(mcICurlPerformerContext* context):m_context(context) {
}

mcCurlPerformerStateRoot::~mcCurlPerformerStateRoot() {
  for(map<string, vector<mcIStackFrame*> >::iterator it = m_pool.begin() ; it != m_pool.end() ; it++) {
    vector<mcIStackFrame*>& stack = it->second;
    for(vector<mcIStackFrame*>::iterator its = stack.begin() ; its != stack.end() ; its++)
      delete *its;
  }
}

mcLanguageState mcCurlPerformerStateRoot::open(string url, string alias) {
  string mnymonic = (alias.empty()) ? url : alias;
  if (m_pool.find(mnymonic) == m_pool.end()) {
    mcIStackFrame* stkfrm = new mcCurlPerformerConnection(url, mnymonic);
    m_pool[mnymonic].push_back(stkfrm);
  }
  m_context->set_context(MC_CURL_CONTEXT_CONNECT, &m_pool[mnymonic]);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::close(void) {
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::leave(void) {
  fprintf(stderr, "already in root\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::list(void) {
  for(map<string, vector<mcIStackFrame*> >::iterator it = m_pool.begin() ; it != m_pool.end() ; it++) {
    if(it->second.empty()) continue;
    fprintf(stdout, "%s\n", it->first.c_str());
  }
  return MC_LANG_CONTINUE;
}

string mcCurlPerformerStateRoot::mnymonic(void){
  return "mycurl";
}

mcLanguageState mcCurlPerformerStateRoot::get(string path, string lst){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::del(string lst){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::put(string inpath, size_t chunk, string outpath, string lst){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::verbose_on(void){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::verbose_off(void){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::verbose(bool& onoff){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::follow_on(void){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::follow_off(void){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateRoot::follow(bool& onoff){
  fprintf(stderr, "invalid handle\n");
  return MC_LANG_CONTINUE;
}

