#include "mc-curl-performer-form.h"
#include <stdexcept>

mcCurlPerformerForm::mcCurlPerformerForm(mcCurlHeader* header) : m_header(header) {}

void mcCurlPerformerForm::list(ostream& stream) {
  m_header->list(stream);
}

string mcCurlPerformerForm::mnymonic(void){
  return "header";
}

mcIStackFrame* mcCurlPerformerForm::open(string url, string alias) {
  return NULL;
}

void mcCurlPerformerForm::get(string path){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::del(void){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::post(string inpath, bool chunk, string outpath){
  throw runtime_error("invalid command");
}

void mcCurlPerformerForm::put(string inpath, bool chunk, string outpath){
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

