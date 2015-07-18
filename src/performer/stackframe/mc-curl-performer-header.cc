#include "mc-curl-performer-header.h"
#include <iostream>

mcCurlPerformerHeader::mcCurlPerformerHeader(mcCurl* curl) : m_curl(curl) {}

void mcCurlPerformerHeader::list(ostream& stream) {
  m_curl->list_header(stream);
}

string mcCurlPerformerHeader::mnymonic(void){
  return "header";
}

mcIStackFrame* mcCurlPerformerHeader::open(string url, string alias){
  return NULL;
}

void mcCurlPerformerHeader::get(string path, string lst){
  cerr <<  "invalid" << endl;
}

void mcCurlPerformerHeader::del(string lst){
  cerr <<  "invalid" << endl;
}

void mcCurlPerformerHeader::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  cerr <<  "invalid" << endl;
}

void mcCurlPerformerHeader::put(string inpath, size_t chunk, string outpath, string lst){
  cerr <<  "invalid" << endl;
}

bool mcCurlPerformerHeader::verbose(void){
  cerr <<  "invalid" << endl;
}

void mcCurlPerformerHeader::verbose(bool onoff){
  cerr <<  "invalid" << endl;
}

bool mcCurlPerformerHeader::follow(void){
  cerr <<  "invalid" << endl;
}

void mcCurlPerformerHeader::follow(bool onoff){
  cerr <<  "invalid" << endl;
}

