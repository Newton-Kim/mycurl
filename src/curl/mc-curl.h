#pragma once

#include "mc-types.h"
#include "mc-curl-header.h"
#include <map>
#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;

class mcCurl {
 private:
//  map<string, curl_slist*> m_headers;
  map<string, vector<string> > m_headers;
  map<string, vector<string> > m_forms;
  CURL* m_curl;
  string m_url;
  string m_mnymonic;
  bool m_verbose;
  bool m_follow;
  void perform(void);

 public:
  mcCurl(string url, string mnymonic);
  ~mcCurl();
  string mnymonic(void);
  void verbose(bool onoff);
  bool verbose(void);
  void follow(bool onoff);
  bool follow(void);
  void get(string path);
  void del(void);
  void post(string inpath, bool chunk, string outpath);
  void put(string inpath, bool chunk, string outpath);
  mcCurlHeader* header(void);
  mcCurlHeader* form(void);
};
