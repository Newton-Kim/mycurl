#include "mc-curl.h"

mcCurl::mcCurl(string url, string mnymonic):m_url(url), m_mnymonic(mnymonic){
}

string mcCurl::mnymonic(void){
	return m_mnymonic;
}

void mcCurl::verbose(bool onoff){
}

bool mcCurl::verbose(void){
}

void mcCurl::get(string path, string lst){
}

void mcCurl::del(string lst){
}

void mcCurl::post(string inpath, size_t chunk, string outpath, string lst){
}

void mcCurl::put(string inpath, size_t chunk, string outpath, string lst){
}

void mcCurl::header(string key, string value, string lst){
}
