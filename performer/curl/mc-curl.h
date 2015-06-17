#pragma once

#include <map>
#include <string>

using namespace std;

class mcCurl {
	private:
		string m_url;
		string m_mnymonic;
	public:
		mcCurl(string url, string mnymonic);
		string mnymonic(void);
		void verbose(bool onoff);
		bool verbose(void);
		void get(string path, string lst);
		void del(string lst);
		void post(string inpath, size_t chunk, string outpath, string lst);
		void put(string inpath, size_t chunk, string outpath, string lst);
		void header(string key, string value, string lst);
};
