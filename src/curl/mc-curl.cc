#include "mc-curl.h"
#include "mc-curl-file.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstring>
#include <cerrno>

size_t mcCurlWriteCallback(char *ptr, size_t size, size_t nmemb,
                           void *userdata) {
  FILE *fd = (FILE *)userdata;
  if (!fd) throw runtime_error("invalid userdata in the write callback");
  size_t len = fwrite(ptr, size, nmemb, fd);
  if (len != nmemb) throw runtime_error("fwrite failed");
  return size * nmemb;
}

size_t mcCurlReadCallback(char *buffer, size_t size, size_t nitems,
                          void *instream) {
  mcCurlFile *fd = (mcCurlFile *)instream;
  if (!fd) throw runtime_error("invalid userdata in the write callback");
  return fd->fread(buffer, size, nitems);
}
int mcCurlDebugCallback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr) {
  switch (type) {
    case CURLINFO_TEXT:
      for(size_t i = 0 ; i < size ; i++) {
        cout << data[i];
        if (data[i] == '\n') cout <<  "* ";
      }
      break;
    case CURLINFO_HEADER_IN:
      for(size_t i = 0 ; i < size ; i++) {
        cout << data[i];
        if (data[i] == '\n') cout <<  "< ";
      }
      break;
    case CURLINFO_HEADER_OUT:
      for(size_t i = 0 ; i < size ; i++) {
        cout << data[i];
        if (data[i] == '\n') cout <<  "> ";
      }
      break;
    case CURLINFO_DATA_IN:
    case CURLINFO_DATA_OUT:
    case CURLINFO_SSL_DATA_IN:
    case CURLINFO_SSL_DATA_OUT:
      for(size_t i = 0 ; i < size ; i++) cout << data[i];
      break;
  }
}

mcCurl::mcCurl(string url, string mnymonic)
    : m_url(url), m_mnymonic(mnymonic), m_verbose(false), m_follow(false) {
  m_curl = curl_easy_init();
  if (!m_curl) throw runtime_error("curl_easy_init failed");
  curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
}

mcCurl::~mcCurl() {
  for (map<string, pair<struct curl_httppost*, struct curl_httppost*> >::iterator it = m_form.begin();
       it != m_form.end(); it++)
    curl_formfree(it->second.second);
  if (m_curl) curl_easy_cleanup(m_curl);
}

string mcCurl::mnymonic(void) { return m_mnymonic; }

void mcCurl::verbose(bool onoff) {
  if (!m_curl) throw runtime_error("invalid curl handle");
  m_verbose = onoff;
  curl_easy_setopt(m_curl, CURLOPT_VERBOSE, (m_verbose ? 1 : 0));
  curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, (m_verbose ? mcCurlDebugCallback : NULL));
}

bool mcCurl::verbose(void) { return m_verbose; }

void mcCurl::follow(bool onoff) {
  if (!m_curl) throw runtime_error("invalid curl handle");
  m_follow = onoff;
  curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, (m_follow ? 1 : 0));
}

bool mcCurl::follow(void) { return m_follow; }

void mcCurl::set_form(string lst) {
  map<string, pair<struct curl_httppost*, struct curl_httppost*> >::iterator it = m_form.find(lst);
  if (it == m_form.end()) return;
  pair<struct curl_httppost *, struct curl_httppost *> post = it->second;
  if (post.first) curl_easy_setopt(m_curl, CURLOPT_HTTPPOST, post.first);
}

void mcCurl::perform(string hdr) {
  curl_slist* slist = NULL;
  map<string, map<string, string> >::iterator it = m_headers.find(hdr);
  if(it != m_headers.end()) {
    map<string, string>& headers = it->second;
    for(map<string, string>::iterator ith = headers.begin() ; ith != headers.end() ; ith++) {
      string line = ith->first + ": " + ith->second;
      slist = curl_slist_append(slist, line.c_str());
    }
    if (slist) curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, slist);
  }
  CURLcode ret = curl_easy_perform(m_curl);
  if (ret != CURLE_OK) cerr << curl_easy_strerror(ret);
  if(slist) curl_slist_free_all(slist);
}

void mcCurl::get(string path, string lst) {
  if (!m_curl) throw runtime_error("invalid curl handle");
  FILE *fd = NULL;
  if (path.size()) {
    fd = fopen(path.c_str(), "wb");
    if (!fd) throw runtime_error(strerror(errno));
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, mcCurlWriteCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, fd);
  } else {
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, stdout);
  }
  perform(lst);
  if (fd) fclose(fd);
}

void mcCurl::del(string lst) {
  if (!m_curl) throw runtime_error("invalid curl handle");
  curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "DELETE");
  perform(lst);
}

void mcCurl::post(string inpath, size_t chunk, string outpath, string lst, string frm) {
  if (!m_curl) throw runtime_error("invalid curl handle");
  curl_easy_setopt(m_curl, CURLOPT_POST, 1);
  mcCurlFile *infd = NULL, *outfd = NULL;
  if (inpath.size()) {
    infd = new mcCurlFile(inpath.c_str(), (const char *)"rb", chunk);
    if (!infd) throw runtime_error(strerror(errno));
    curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, mcCurlReadCallback);
    curl_easy_setopt(m_curl, CURLOPT_READDATA, infd);
  } else {
    curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(m_curl, CURLOPT_READDATA, stdout);
  }
  if (outpath.size()) {
//    outfd = fopen(outpath.c_str(), "wb");
    outfd = new mcCurlFile(outpath.c_str(), (const char *)"wb", chunk);
    if (!infd) throw runtime_error(strerror(errno));
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, mcCurlWriteCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, outfd);
  } else {
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, stdout);
  }
  header("Content-Type", "multipart/form-data;boundary=----mycurl", lst);
  if(chunk) {
    header("Transfer-Encoding", "chunked", lst);
  } else {
    header("Content-Length", infd->fsize(), lst);
    header("Expect", "", lst);
  }
  set_form(frm);
  perform(lst);
  if (infd) delete infd;
  if (outfd) delete outfd;
}

void mcCurl::put(string inpath, size_t chunk, string outpath, string lst) {
  if (!m_curl) throw runtime_error("invalid curl handle");
  curl_easy_setopt(m_curl, CURLOPT_PUT, 1);
  FILE *infd = NULL;
  mcCurlFile *outfd = NULL;
  if (inpath.size()) {
    infd = fopen(inpath.c_str(), "wb");
    if (!infd) throw runtime_error(strerror(errno));
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, mcCurlWriteCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, infd);
  } else {
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, stdout);
  }
  if (outpath.size()) {
    outfd = new mcCurlFile(outpath.c_str(), (const char *)"rb", chunk);
    if (!outfd) throw runtime_error(strerror(errno));
    curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, mcCurlReadCallback);
    curl_easy_setopt(m_curl, CURLOPT_READDATA, outfd);
  } else {
    curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(m_curl, CURLOPT_READDATA, stdout);
  }
  perform(lst);
  if (infd) fclose(infd);
  if (outfd) delete outfd;
}

void mcCurl::header(string key, size_t value, string lst) {
  stringstream ss;
  ss << value;
  header(key, ss.str(), lst);
}

void mcCurl::header(string key, string value, string lst) {
  map<string, map<string, string> >::iterator it = m_headers.find(lst);
  if(it == m_headers.end()) {
    map<string, string> headers;
    headers[key] = value;
    m_headers[lst] = headers;
  } else {
    map<string, string>& headers = it->second;
    headers[key] = value;
  }
}

void mcCurl::form(string key, string value, string lst) {
  map<string, pair<struct curl_httppost *, struct curl_httppost *> >::iterator it = m_form.find(lst);
  curl_httppost *post = (it != m_form.end()) ? it->second.first : NULL;
  curl_httppost *end = (it != m_form.end()) ? it->second.second : NULL;
  curl_formadd(&post, &end, CURLFORM_COPYNAME, key.c_str(), CURLFORM_COPYCONTENTS, value.c_str(), CURLFORM_END);
  m_form[lst] = make_pair<struct curl_httppost *, struct curl_httppost *>(post, end);
}

void mcCurl::list_header(ostream& stream){
}

void mcCurl::list_form(ostream& stream){
}

