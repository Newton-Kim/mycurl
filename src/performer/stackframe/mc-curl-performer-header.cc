#include "mc-curl-performer-header.h"
#include <stdexcept>

mcCurlPerformerHeader::mcCurlPerformerHeader(mcCurlHeader* header) : m_header(header) {}

void mcCurlPerformerHeader::list(ostream& stream) {
  m_header->list(stream);
}

string mcCurlPerformerHeader::mnymonic(void){
  return "header";
}

mcIStackFrame* mcCurlPerformerHeader::open(string url, string alias){
  return NULL;
}

void mcCurlPerformerHeader::get(string path){
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::del(void){
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::post(string inpath, bool chunk, string outpath){
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::put(string inpath, bool chunk, string outpath){
  throw runtime_error("invalid command");
}

bool mcCurlPerformerHeader::verbose(void){
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::verbose(bool onoff){
  throw runtime_error("invalid command");
}

bool mcCurlPerformerHeader::follow(void){
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::follow(bool onoff){
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::add(string key, string value){
	m_header->add(key, value);
}

void mcCurlPerformerHeader::rm(string key, string value){
	m_header->rm(key);
}

