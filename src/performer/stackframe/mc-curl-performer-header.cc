#include "mc-curl-performer-header.h"
#include <stdexcept>

mcCurlPerformerHeader::mcCurlPerformerHeader(mcCurlHeader* header,
                                             string mnymonic)
    : m_header(header), m_mnymonic(mnymonic) {}

void mcCurlPerformerHeader::list(ostream& stream) { m_header->list(stream); }

string mcCurlPerformerHeader::mnymonic(void) { return m_mnymonic; }

mcIStackFrame* mcCurlPerformerHeader::open(string url, string alias) {
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::get(string path) {
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::del(void) {
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::post(string inpath, bool chunk, string outpath) {
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::put(string inpath, bool chunk, string outpath) {
  throw runtime_error("invalid command");
}

bool mcCurlPerformerHeader::verbose(void) {
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::verbose(bool onoff) {
  throw runtime_error("invalid command");
}

bool mcCurlPerformerHeader::follow(void) {
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::follow(bool onoff) {
  throw runtime_error("invalid command");
}

void mcCurlPerformerHeader::add(string key, string value) {
  m_header->add(key, value);
}

void mcCurlPerformerHeader::rm(string key) { m_header->rm(key); }
