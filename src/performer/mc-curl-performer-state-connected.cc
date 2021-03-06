#include "mc-curl-performer.h"
#include "mc-curl-performer-state-connected.h"
#include "stackframe/mc-curl-performer-connection.h"
#include <iostream>

mcCurlPerformerStateConnected::mcCurlPerformerStateConnected(
    mcICurlPerformerContext* context, vector<mcIStackFrame*>* stack)
    : m_context(context), m_stack(stack) {}

mcCurlPerformerStateConnected::~mcCurlPerformerStateConnected() {}

void mcCurlPerformerStateConnected::open(string url, string alias) {
  mcIStackFrame* stkfrm = m_stack->back()->open(url, alias);
  if (stkfrm) m_stack->push_back(stkfrm);
}

void mcCurlPerformerStateConnected::close(void) {
  mcIStackFrame* stkfrm = m_stack->back();
  delete stkfrm;
  m_stack->pop_back();
  if (m_stack->empty()) m_context->set_context(MC_CURL_CONTEXT_ROOT);
}

void mcCurlPerformerStateConnected::leave(void) {
  m_context->set_context(MC_CURL_CONTEXT_ROOT);
}

void mcCurlPerformerStateConnected::list(void) { m_stack->back()->list(cout); }

string mcCurlPerformerStateConnected::mnymonic(void) {
  string ret = "mycurl";
  if (m_stack) {
    for (vector<mcIStackFrame*>::iterator it = m_stack->begin();
         it != m_stack->end(); it++) {
      ret += "/";
      ret += (*it)->mnymonic();
    }
  }
  return ret;
}

void mcCurlPerformerStateConnected::get(string path) {
  m_stack->back()->get(path);
}

void mcCurlPerformerStateConnected::del(void) { m_stack->back()->del(); }

void mcCurlPerformerStateConnected::post(string inpath, bool chunk,
                                         string outpath) {
  m_stack->back()->post(inpath, chunk, outpath);
}

void mcCurlPerformerStateConnected::put(string inpath, bool chunk,
                                        string outpath) {
  m_stack->back()->put(inpath, chunk, outpath);
}

void mcCurlPerformerStateConnected::verbose_on(void) {
  m_stack->back()->verbose(true);
}

void mcCurlPerformerStateConnected::verbose_off(void) {
  m_stack->back()->verbose(false);
}

void mcCurlPerformerStateConnected::verbose(bool& onoff) {
  onoff = m_stack->back()->verbose();
}

void mcCurlPerformerStateConnected::follow_on(void) {
  m_stack->back()->follow(true);
}

void mcCurlPerformerStateConnected::follow_off(void) {
  m_stack->back()->follow(false);
}

void mcCurlPerformerStateConnected::follow(bool& onoff) {
  onoff = m_stack->back()->follow();
}

void mcCurlPerformerStateConnected::add(string key, string value) {
  m_stack->back()->add(key, value);
}

void mcCurlPerformerStateConnected::rm(string key) { m_stack->back()->rm(key); }
