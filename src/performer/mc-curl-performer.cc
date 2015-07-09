#include "mc-curl-performer.h"
#include <cstdio>

mcCurlPerformer::mcCurlPerformer() : {
  m_prompt.push_back(new mcCurlPerformerRoot);
}

mcCurlPerformer::~mcCurlPerformer() : {
  for(vector<mcIPerformer*>::iterator it = m_prompt.begin() ; it != m_prompt.end() ; it++)
    delete *it;
}

mcLanguageState mcCurlPerformer::open(string url, string alias) {
  mcIPerformer* performer = m_prompt.back()->open(url, alias);
  if(performer) m_prompt.push_back(performer);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::close(void) {
  m_prompt.back()->close();
  mcIPerformer* performer = m_prompt.top();
  delete performer;
  m_prompt.pop();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::leave(void) {
  mcIPerformer* performer = m_prompt.top();
  delete performer;
  m_prompt.pop();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::list(void) {
  m_prompt.back()->list();
  return MC_LANG_CONTINUE;
}

string mcCurlPerformer::mnymonic(void){
  string ret;
  for(vector<mcIPerformer*>::iterator it = m_prompt.begin() ; it != m_prompt.end() ; it++) {
    ret += (*it)->mnymonic();
    ret += "/";
  }
  return ret;
}

mcLanguageState mcCurlPerformer::get(string path, string lst){
  m_prompt.back()->get();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::del(string lst){
  m_prompt.back()->del(lst);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  m_prompt.back()->post(inpath, chunk, outpath, lst, frm);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::put(string inpath, size_t chunk, string outpath, string lst){
  m_prompt.back()->put(inpath, chunk, outpath, lst);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose_on(void){
  m_prompt.back()->verbose_on();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose_off(void){
  m_prompt.back()->verbose_off();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose(bool& onoff){
  m_prompt.back()->verbose(onoff);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::follow_on(void){
  m_prompt.back()->follow_on();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::follow_off(void){
  m_prompt.back()->follow_off();
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::follow(bool& onoff){
  m_prompt.back()->follow(onoff);
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::header(string key, string value, string lst){
  m_prompt.back()->header(key, value, lst);
  if (!m_current) {
    fprintf(stderr, "invalid handle\n");
  } else {
    m_current = NULL;
  }
  return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::form(string key, string value, string lst){
  m_prompt.back()->form(key, value, lst);
  return MC_LANG_CONTINUE;
}


