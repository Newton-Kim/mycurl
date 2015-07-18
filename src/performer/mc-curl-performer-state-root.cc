#include "mc-curl-performer.h"
#include "mc-curl-performer-state-root.h"
#include "stackframe/mc-curl-performer-connection.h"
#include <cstdio>
#include <stdexcept>

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
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::leave(void) {
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::list(void) {
  for(map<string, vector<mcIStackFrame*> >::iterator it = m_pool.begin() ; it != m_pool.end() ; it++) {
    if(it->second.empty()) continue;
    fprintf(stdout, "%s\n", it->first.c_str());
  }
}

string mcCurlPerformerStateRoot::mnymonic(void){
  return "mycurl";
}

void mcCurlPerformerStateRoot::get(string path, string lst){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::del(string lst){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::put(string inpath, size_t chunk, string outpath, string lst){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::verbose_on(void){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::verbose_off(void){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::verbose(bool& onoff){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::follow_on(void){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::follow_off(void){
  throw runtime_error("invalid handle");
}

void mcCurlPerformerStateRoot::follow(bool& onoff){
  throw runtime_error("invalid handle");
}

