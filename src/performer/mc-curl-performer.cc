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

void mcCurlPerformer::open(string url, string alias) {
  m_current_state->open(url, alias);
}

void mcCurlPerformer::close(void) {
  m_current_state->close();
}

void mcCurlPerformer::leave(void) {
  m_current_state->leave();
}

void mcCurlPerformer::list(void) {
  m_current_state->list();
}

string mcCurlPerformer::mnymonic(void){
  m_current_state->mnymonic();
}

void mcCurlPerformer::get(string path, string lst){
  m_current_state->get(path, lst);
}

void mcCurlPerformer::del(string lst){
  m_current_state->del(lst);
}

void mcCurlPerformer::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  m_current_state->post(inpath, chunk, outpath, lst, frm);
}

void mcCurlPerformer::put(string inpath, size_t chunk, string outpath, string lst){
  m_current_state->put(inpath, chunk, outpath, lst);
}

void mcCurlPerformer::verbose_on(void){
  m_current_state->verbose_on();
}

void mcCurlPerformer::verbose_off(void){
  m_current_state->verbose_off();
}

void mcCurlPerformer::verbose(bool& onoff){
  m_current_state->verbose(onoff);
}

void mcCurlPerformer::follow_on(void){
  m_current_state->follow_on();
}

void mcCurlPerformer::follow_off(void){
  m_current_state->follow_off();
}

void mcCurlPerformer::follow(bool& onoff){
  m_current_state->follow(onoff);
}

