#pragma once

#include <map>
#include <string>
#include <curl/curl.h>

using namespace std;

class mcCurl {
	private:
		map<string, curl_slist*> m_headers;
		CURL* m_curl;
		string m_url;
		string m_mnymonic;
		bool m_verbose;
		void set_header(string lst);
	public:
		mcCurl(string url, string mnymonic);
		~mcCurl();
		string mnymonic(void);
		void verbose(bool onoff);
		bool verbose(void);
		void get(string path, string lst);
		void del(string lst);
		void post(string inpath, size_t chunk, string outpath, string lst);
		void put(string inpath, size_t chunk, string outpath, string lst);
		void header(string key, string value, string lst);
};
