#pragma once

#include "mc-types.h"
#include <map>
#include <string>
#include <curl/curl.h>

using namespace std;

class mcCurl : public mcIConnection {
 private:
//  map<string, curl_slist*> m_headers;
  map<string, map<string, string> > m_headers;
  map<string, pair<struct curl_httppost*, struct curl_httppost*> > m_form;
  CURL* m_curl;
  string m_url;
  string m_mnymonic;
  bool m_verbose;
  bool m_follow;
  void set_form(string lst);
  void perform(string hdr);

 public:
  mcCurl(string url, string mnymonic);
  ~mcCurl();
  string mnymonic(void);
  void verbose(bool onoff);
  bool verbose(void);
  void follow(bool onoff);
  bool follow(void);
  void get(string path, string lst);
  void del(string lst);
  void post(string inpath, size_t chunk, string outpath, string lst, string frm);
  void put(string inpath, size_t chunk, string outpath, string lst);
  void header(string key, string value, string lst);
  void header(string key, size_t value, string lst);
  void form(string key, string value, string lst);
};
