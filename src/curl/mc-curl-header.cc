#include "mc-curl-header.h"
#include <sstream>

mcCurlHeader::mcCurlHeader(map<string, vector<string> >& header)
    : m_header(header) {}

void mcCurlHeader::add(string key, string value) {
  map<string, vector<string> >::iterator it = m_header.find(key);
  if (it == m_header.end()) {
    m_header[key].push_back(value);
  } else {
    it->second.push_back(value);
  }
}

void mcCurlHeader::rm(string key) {
  map<string, vector<string> >::iterator it = m_header.find(key);
  if (it != m_header.end()) it->second.clear();
}

void mcCurlHeader::list(ostream& os) {
  for (map<string, vector<string> >::iterator itm = m_header.begin();
       itm != m_header.end(); itm++) {
    vector<string>& values = itm->second;
    os << itm->first;
    if (values.size()) os << ":";
    for (vector<string>::iterator itv = values.begin(); itv != values.end();
         itv++) {
      if (itv != values.begin()) os << ";";
      os << *itv;
    }
    os << endl;
  }
}
