#include "mc-curl-performer-header.h"
#include <cstdio>

mcCurlPerformerHeader::mcCurlPerformerHeader(mcCurl* curl) : m_curl(curl) {}

void mcCurlPerformerHeader::list(void) {
  //TODO:print headers
}

string mcCurlPerformerHeader::mnymonic(void){
  return "header";
}

void mcCurlPerformerHeader::get(string path, string lst){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerHeader::del(string lst){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerHeader::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerHeader::put(string inpath, size_t chunk, string outpath, string lst){
  fprintf(stderr, "invalid\n");
}

bool mcCurlPerformerHeader::verbose(void){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerHeader::verbose(bool& onoff){
  fprintf(stderr, "invalid\n");
}

bool mcCurlPerformerHeader::follow(void){
  fprintf(stderr, "invalid\n");
}

void mcCurlPerformerHeader::follow(bool& onoff){
  fprintf(stderr, "invalid\n");
}

mcIStackFrame* mcCurlPerformerHeader::header(void){
  fprintf(stderr, "invalid\n");
  return NULL;
}

mcIStackFrame* mcCurlPerformerHeader::form(void){
  fprintf(stderr, "invalid\n");
  return NULL;
}


