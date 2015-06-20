#include "mc-curl.h"
#include "mc-curl-file.h"
#include <stdexcept>
#include <cstring>
#include <cerrno>

size_t mcCurlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata){
	FILE* fd = (FILE*)userdata;
	if(!fd) throw runtime_error("invalid userdata in the write callback");
	size_t len = fwrite(ptr, size, nmemb, fd);
	if (len != nmemb) throw runtime_error("fwrite failed");
	return size * nmemb;
}

size_t mcCurlReadCallback(char *buffer, size_t size, size_t nitems, void *instream){
	mcCurlFile* fd = (mcCurlFile*)instream;
	if(!fd) throw runtime_error("invalid userdata in the write callback");
	return fd->fread(buffer, size, nitems);
}

mcCurl::mcCurl(string url, string mnymonic):m_url(url), m_mnymonic(mnymonic), m_verbose(false){
	m_curl = curl_easy_init();
	if(!m_curl) throw runtime_error("curl_easy_init failed");
	curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
}

mcCurl::~mcCurl(){
	for (map<string, curl_slist*>::iterator it = m_headers.begin() ; it != m_headers.end() ; it++)
		curl_slist_free_all(it->second);
	if(m_curl) curl_easy_cleanup(m_curl);
}

string mcCurl::mnymonic(void){
	return m_mnymonic;
}

void mcCurl::verbose(bool onoff){
	if(!m_curl) throw runtime_error("invalid curl handle");
	m_verbose = onoff;
	curl_easy_setopt(m_curl, CURLOPT_VERBOSE, (m_verbose ? 1 : 0));
}

bool mcCurl::verbose(void){
	return m_verbose;
}

void mcCurl::set_header(string lst){
	map<string, curl_slist*>::iterator it = m_headers.find(lst);
	curl_slist* slist = (it != m_headers.end()) ? it->second : NULL;
	if(slist) curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, slist);
}

void mcCurl::get(string path, string lst){
	if(!m_curl) throw runtime_error("invalid curl handle");
	set_header(lst);
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);
	curl_easy_setopt(m_curl, CURLOPT_PUT, 0);
	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, NULL);
	FILE* fd = NULL;
	if(path.size()) {
		fd = fopen(path.c_str(), "wb");
		if(!fd) throw runtime_error(strerror(errno));
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, mcCurlWriteCallback);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, fd);
	} else {
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, NULL);
	}
	curl_easy_perform(m_curl);
	if(fd) fclose(fd);
}

void mcCurl::del(string lst){
	if(!m_curl) throw runtime_error("invalid curl handle");
	set_header(lst);
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);
	curl_easy_setopt(m_curl, CURLOPT_PUT, 0);
	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "DELETE");
	curl_easy_perform(m_curl);
}

void mcCurl::post(string inpath, size_t chunk, string outpath, string lst){
	if(!m_curl) throw runtime_error("invalid curl handle");
	set_header(lst);
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);
	curl_easy_setopt(m_curl, CURLOPT_POST, 1);
	curl_easy_setopt(m_curl, CURLOPT_PUT, 0);
	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, NULL);
	FILE *infd = NULL;
	mcCurlFile *outfd = NULL;
	if(inpath.size()) {
		infd = fopen(inpath.c_str(), "wb");
		if(!infd) throw runtime_error(strerror(errno));
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, mcCurlWriteCallback);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, infd);
	} else {
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, NULL);
	}
	if(outpath.size()) {
		outfd = new mcCurlFile (outpath.c_str(), (const char*)"rb", chunk);
		if(!outfd) throw runtime_error(strerror(errno));
		curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, mcCurlReadCallback);
		curl_easy_setopt(m_curl, CURLOPT_READDATA, outfd);
	} else {
		curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
		curl_easy_setopt(m_curl, CURLOPT_READDATA, NULL);
	}
	curl_easy_perform(m_curl);
	if(infd) fclose(infd);
	if(outfd) delete outfd;
}

void mcCurl::put(string inpath, size_t chunk, string outpath, string lst){
	if(!m_curl) throw runtime_error("invalid curl handle");
	set_header(lst);
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);
	curl_easy_setopt(m_curl, CURLOPT_PUT, 1);
	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, NULL);
	FILE *infd = NULL;
	mcCurlFile *outfd = NULL;
	if(inpath.size()) {
		infd = fopen(inpath.c_str(), "wb");
		if(!infd) throw runtime_error(strerror(errno));
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, mcCurlWriteCallback);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, infd);
	} else {
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, NULL);
	}
	if(outpath.size()) {
		outfd = new mcCurlFile (outpath.c_str(), (const char*)"rb", chunk);
		if(!outfd) throw runtime_error(strerror(errno));
		curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, mcCurlReadCallback);
		curl_easy_setopt(m_curl, CURLOPT_READDATA, outfd);
	} else {
		curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
		curl_easy_setopt(m_curl, CURLOPT_READDATA, NULL);
	}
	curl_easy_perform(m_curl);
	if(infd) fclose(infd);
	if(outfd) delete outfd;
}

void mcCurl::header(string key, string value, string lst){
	map<string, curl_slist*>::iterator it = m_headers.find(lst);
	string hdr = key + ": " + value;
	curl_slist* slist = (it != m_headers.end()) ? it->second : NULL;
	slist = curl_slist_append(slist, hdr.c_str());
	m_headers[lst] = slist;
}
