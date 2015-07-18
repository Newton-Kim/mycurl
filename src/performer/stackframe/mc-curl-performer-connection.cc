#include "mc-curl-performer-connection.h"
#include "mc-curl-performer-header.h"
#include "mc-curl-performer-form.h"
#include <iostream>

mcCurlPerformerConnection::mcCurlPerformerConnection(string url, string alias) :
	m_curl(new mcCurl(url, alias))
{}

mcCurlPerformerConnection::~mcCurlPerformerConnection() {
	delete m_curl;
}

mcIStackFrame* mcCurlPerformerConnection::open(string url, string alias) {
  return NULL;
}

void mcCurlPerformerConnection::list(ostream& stream) {
  stream << "header" << endl << "form" << endl;
}

string mcCurlPerformerConnection::mnymonic(void){
  return m_curl->mnymonic();
}

void mcCurlPerformerConnection::get(string path, string lst){
  m_curl->get(path, lst);
}

void mcCurlPerformerConnection::del(string lst){
  m_curl->del(lst);
}

void mcCurlPerformerConnection::post(string inpath, size_t chunk, string outpath, string lst, string frm){
  m_curl->post(inpath, chunk, outpath, lst, frm);
}

void mcCurlPerformerConnection::put(string inpath, size_t chunk, string outpath, string lst){
  m_curl->put(inpath, chunk, outpath, lst);
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

