#include "mc-curl-performer.h"
#include "mc-curl-performer-state-connected.h"
#include "stackframe/mc-curl-performer-connection.h"
#include <cstdio>

mcCurlPerformerStateConnected::mcCurlPerformerStateConnected(mcICurlPerformerContext* context, vector<mcIStackFrame*>* stack) : m_context(context), m_stack(stack) {
}

mcCurlPerformerStateConnected::~mcCurlPerformerStateConnected() {
}

mcLanguageState mcCurlPerformerStateConnected::open(string url, string alias) {
  mcIStackFrame* stkfrm = m_stack->back()->open(url, alias);
  if(stkfrm) m_stack->push_back(stkfrm);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::close(void) {
  mcIStackFrame* stkfrm = m_stack->back();
  delete stkfrm;
  m_stack->pop_back();
  if (m_stack->empty()) m_context->set_context(MC_CURL_CONTEXT_ROOT);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::leave(void) {
  m_context->set_context(MC_CURL_CONTEXT_ROOT);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::list(void) {
  m_stack->back()->list();
  return MC_LANG_CONTINUE;
}

string mcCurlPerformerStateConnected::mnymonic(void){
  string ret = "mycurl";
  if(m_stack) {
    for(vector<mcIStackFrame*>::iterator it = m_stack->begin() ; it != m_stack->end() ; it++) {
      ret += "/";
      ret += (*it)->mnymonic();
    }
  }
  return ret;
}

mcLanguageState mcCurlPerformerStateConnected::get(string path, string lst){
  m_stack->back()->get(path, lst);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::del(string lst){
  m_stack->back()->del(lst);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  m_stack->back()->post(inpath, chunk, outpath, lst, frm);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::put(string inpath, size_t chunk, string outpath, string lst){
  m_stack->back()->put(inpath, chunk, outpath, lst);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::verbose_on(void){
  m_stack->back()->verbose(true);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::verbose_off(void){
  m_stack->back()->verbose(false);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::verbose(bool& onoff){
  onoff = m_stack->back()->verbose();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::follow_on(void){
  m_stack->back()->follow(true);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::follow_off(void){
  m_stack->back()->follow(false);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformerStateConnected::follow(bool& onoff){
  onoff =m_stack->back()->follow();
  return MC_LANG_CONTINUE;
}

