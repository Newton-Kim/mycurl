#include "mc-curl-performer.h"
#include "stackframe/mc-curl-performer-connection.h"
#include <cstdio>

mcCurlPerformer::mcCurlPerformer() : m_stack(NULL) {
}

mcCurlPerformer::~mcCurlPerformer() {
  for(map<string, vector<mcIStackFrame*> >::iterator it = m_pool.begin() ; it != m_pool.end() ; it++) {
    vector<mcIStackFrame*>& stack = it->second;
    for(vector<mcIStackFrame*>::iterator its = stack.begin() ; its != stack.end() ; its++)
      delete *its;
  }
}

mcLanguageState mcCurlPerformer::open(string url, string alias) {
  string mnymonic = (alias.empty()) ? url : alias;
  if(m_stack) {
    mcIStackFrame* stkfrm = m_stack->back()->open(url, mnymonic);
    if(stkfrm) m_stack->push_back(stkfrm);
    return MC_LANG_CONTINUE;
  }
  if (m_pool.find(mnymonic) == m_pool.end()) {
    mcIStackFrame* stkfrm = new mcCurlPerformerConnection(url, mnymonic);
    m_pool[mnymonic].push_back(stkfrm);
  }
  m_stack = &m_pool[mnymonic];
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::close(void) {
  if(!m_stack) {
    fprintf(stderr, "invalid handle\n");
    return MC_LANG_CONTINUE;
  } else {
    mcIStackFrame* stkfrm = m_stack->back();
    delete stkfrm;
    m_stack->pop_back();
    if (m_stack->empty()) m_stack = NULL;
  }
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::leave(void) {
  if(m_stack) m_stack = NULL;
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::list(void) {
  if(m_stack) {
    m_stack->back()->list();
  } else {
    for(map<string, vector<mcIStackFrame*> >::iterator it = m_pool.begin() ; it != m_pool.end() ; it++) {
      if(it->second.empty()) continue;
      fprintf(stdout, "%s\n", it->first.c_str());
    }
  }
  return MC_LANG_CONTINUE;
}

string mcCurlPerformer::mnymonic(void){
  string ret = "mycurl";
  if(m_stack) {
    for(vector<mcIStackFrame*>::iterator it = m_stack->begin() ; it != m_stack->end() ; it++) {
      ret += "/";
      ret += (*it)->mnymonic();
    }
  }
  return ret;
}

mcLanguageState mcCurlPerformer::get(string path, string lst){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::del(string lst){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::put(string inpath, size_t chunk, string outpath, string lst){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose_on(void){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose_off(void){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose(bool& onoff){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::follow_on(void){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::follow_off(void){
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::follow(bool& onoff){
  return MC_LANG_CONTINUE;
}

