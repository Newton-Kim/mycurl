#include "mc-curl-performer-form.h"
#include <cstdio>

mcCurlPerformerForm::mcCurlPerformerForm(mcCurl* curl) : m_curl(curl) {}

void mcCurlPerformerForm::list(void) {
  //TODO:print headers
}

string mcCurlPerformerForm::mnymonic(void){
  return "header";
}

mcIStackFrame* mcCurlPerformerForm::open(string url, string alias) {
  return NULL;
}

void mcCurlPerformerForm::get(string path, string lst){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerForm::del(string lst){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerForm::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerForm::put(string inpath, size_t chunk, string outpath, string lst){
  fprintf(stderr, "invalid\n");
}

bool mcCurlPerformerForm::verbose(void){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerForm::verbose(bool& onoff){
  fprintf(stderr, "invalid\n");
}

bool mcCurlPerformerForm::follow(void){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerForm::follow(bool& onoff){
  fprintf(stderr, "invalid\n");
}

