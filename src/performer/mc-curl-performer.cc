#include "mc-curl-performer.h"
#include "mc-curl-performer-state-root.h"
#include "mc-curl-performer-state-connected.h"
#include "stackframe/mc-curl-performer-connection.h"
#include <cstdio>

mcCurlPerformer::mcCurlPerformer() : m_state_root(new mcCurlPerformerStateRoot(this)), m_state_connected(NULL), m_current_state(m_state_root) {
}

mcCurlPerformer::~mcCurlPerformer() {
  delete m_state_root;
  delete m_state_connected;
}

void mcCurlPerformer::set_context(mcContextState state, vector<mcIStackFrame*>* stack){
  switch (state) {
	  case MC_CURL_CONTEXT_ROOT:
		  if(m_current_state != m_state_root) delete m_current_state;
		  m_current_state = m_state_root;
		  break;
	  case MC_CURL_CONTEXT_CONNECT:
		  if(m_current_state != m_state_root) delete m_current_state;
		  m_current_state = new mcCurlPerformerStateConnected(this, stack);
		  break;
  }
}

mcLanguageState mcCurlPerformer::open(string url, string alias) {
  return m_current_state->open(url, alias);
}

mcLanguageState mcCurlPerformer::close(void) {
  return m_current_state->close();
}

mcLanguageState mcCurlPerformer::leave(void) {
  return m_current_state->leave();
}

mcLanguageState mcCurlPerformer::list(void) {
  return m_current_state->list();
}

string mcCurlPerformer::mnymonic(void){
  return m_current_state->mnymonic();
}

mcLanguageState mcCurlPerformer::get(string path, string lst){
  return m_current_state->get(path, lst);
}

mcLanguageState mcCurlPerformer::del(string lst){
  return m_current_state->del(lst);
}

mcLanguageState mcCurlPerformer::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  return m_current_state->post(inpath, chunk, outpath, lst, frm);
}

mcLanguageState mcCurlPerformer::put(string inpath, size_t chunk, string outpath, string lst){
  return m_current_state->put(inpath, chunk, outpath, lst);
}

mcLanguageState mcCurlPerformer::verbose_on(void){
  return m_current_state->verbose_on();
}

mcLanguageState mcCurlPerformer::verbose_off(void){
  return m_current_state->verbose_off();
}

mcLanguageState mcCurlPerformer::verbose(bool& onoff){
  return m_current_state->verbose(onoff);
}

mcLanguageState mcCurlPerformer::follow_on(void){
  return m_current_state->follow_on();
}

mcLanguageState mcCurlPerformer::follow_off(void){
  return m_current_state->follow_off();
}

mcLanguageState mcCurlPerformer::follow(bool& onoff){
  return m_current_state->follow(onoff);
}

