#include "mc-curl-performer-connection.h"
#include "mc-curl-performer-header.h"
#include "mc-curl-performer-form.h"

mcCurlPerformerConnection::mcCurlPerformerConnection(string url, string alias) :
	m_curl(new mcCurl(url, alias))
{}

mcCurlPerformerConnection::~mcCurlPerformerConnection() {
	delete m_curl;
}

mcIStackFrame* mcCurlPerformerConnection::open(string url, string alias) {
  if(url == "header") {
  } else if(url == "form") {
  }
  return NULL;
}

void mcCurlPerformerConnection::list(ostream& stream) {
  stream << "header" << endl << "form" << endl;
}

string mcCurlPerformerConnection::mnymonic(void){
  return m_curl->mnymonic();
}

void mcCurlPerformerConnection::get(string path){
  m_curl->get(path);
}

void mcCurlPerformerConnection::del(void){
  m_curl->del();
}

void mcCurlPerformerConnection::post(string inpath, bool chunk, string outpath){
  m_curl->post(inpath, chunk, outpath);
}

void mcCurlPerformerConnection::put(string inpath, bool chunk, string outpath){
  m_curl->put(inpath, chunk, outpath);
}

bool mcCurlPerformerConnection::verbose(void){
  return m_curl->verbose();
}

void mcCurlPerformerConnection::verbose(bool onoff){
  m_curl->verbose(onoff);
}

bool mcCurlPerformerConnection::follow(void){
  return m_curl->follow();
}

void mcCurlPerformerConnection::follow(bool onoff){
  m_curl->follow(onoff);
}

