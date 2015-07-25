#include "mc-curl-performer-connection.h"
#include "mc-curl-performer-header.h"
#include "mc-curl-performer-form.h"
#include <stdexcept>

mcCurlPerformerConnection::mcCurlPerformerConnection(string url, string alias) :
	m_curl(new mcCurl(url, alias))
{}

mcCurlPerformerConnection::~mcCurlPerformerConnection() {
	delete m_curl;
}

mcIStackFrame* mcCurlPerformerConnection::open(string url, string alias) {
	mcCurlHeader* header = NULL;
	if(url == "header") {
		header = m_curl->header();
	} else if(url == "form") {
		header = m_curl->form();
	} else {
		throw runtime_error("invalid handle");
	}
  return new mcCurlPerformerHeader(header, url);
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

void mcCurlPerformerConnection::add(string key, string value){
  throw runtime_error("invalid command");
}

void mcCurlPerformerConnection::rm(string key){
  throw runtime_error("invalid command");
}

