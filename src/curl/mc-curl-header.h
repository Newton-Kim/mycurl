#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class mcCurlHeader {
	private:
		map<string, vector<string> >& m_header;
	public:
		mcCurlHeader(map<string, vector<string> >& header);
		void add(string key, string value);
		void add(string key, int value);
		void add(string hkey, string key, string value);
		void add(string hkey, string key, int value);
		void rm(string key);
		void list(ostream& os);
};
