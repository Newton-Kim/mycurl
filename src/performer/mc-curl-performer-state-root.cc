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

void mcCurlPerformerStateRoot::open(string url, string alias) {
  string mnymonic = (alias.empty()) ? url : alias;
  if (m_pool.find(mnymonic) == m_pool.end()) {
    mcIStackFrame* stkfrm = new mcCurlPerformerConnection(url, mnymonic);
    m_pool[mnymonic].push_back(stkfrm);
  }
  m_context->set_context(MC_CURL_CONTEXT_CONNECT, &m_pool[mnymonic]);
}

void mcCurlPerformerStateRoot::close(void) {
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::leave(void) {
  fprintf(stderr, "already in root\n");
}

void mcCurlPerformerStateRoot::list(void) {
  for(map<string, vector<mcIStackFrame*> >::iterator it = m_pool.begin() ; it != m_pool.end() ; it++) {
    if(it->second.empty()) continue;
    fprintf(stdout, "%s\n", it->first.c_str());
  }
}

string mcCurlPerformerStateRoot::mnymonic(void){
}

void mcCurlPerformerStateRoot::get(string path, string lst){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::del(string lst){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::put(string inpath, size_t chunk, string outpath, string lst){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::verbose_on(void){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::verbose_off(void){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::verbose(bool& onoff){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::follow_on(void){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::follow_off(void){
  fprintf(stderr, "invalid handle\n");
}

void mcCurlPerformerStateRoot::follow(bool& onoff){
  fprintf(stderr, "invalid handle\n");
}

