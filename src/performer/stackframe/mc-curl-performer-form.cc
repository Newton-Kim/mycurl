#include "mc-curl-performer-form.h"
#include <cstdio>
#include <stdexcept>

mcCurlPerformerForm::mcCurlPerformerForm(mcCurl* curl) : m_curl(curl) {}

void mcCurlPerformerForm::list(ostream& stream) {
  m_curl->list_form(stream);
}

string mcCurlPerformerForm::mnymonic(void){
  return "header";
}

mcIStackFrame* mcCurlPerformerForm::open(string url, string alias) {
  return NULL;
}

void mcCurlPerformerForm::get(string path, string lst){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::del(string lst){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::put(string inpath, size_t chunk, string outpath, string lst){
  throw runtime_error("invalid command");
}

bool mcCurlPerformerForm::verbose(void){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::verbose(bool onoff){
  throw runtime_error("invalid command");
}

bool mcCurlPerformerForm::follow(void){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::follow(bool onoff){
  throw runtime_error("invalid command");
}

