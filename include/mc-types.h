#pragma once

#include <string>

using namespace std;

typedef enum {
	MC_LANG_END,		//quit is called
	MC_LANG_ERROR,		//an error has happened
	MC_LANG_CONTINUE,	//continue to the next line
	MC_LANG_HANG		//end of the process but more input is expected
} mcLanguageState;

class mcIPerformer {
	public:
		virtual mcLanguageState open(string url, string alias) = 0;
		virtual mcLanguageState close(void) = 0;
		virtual mcLanguageState verbose(bool& onoff) = 0;
		virtual mcLanguageState verbose_on(void) = 0;
		virtual mcLanguageState verbose_off(void) = 0;
		virtual mcLanguageState leave(void) = 0;
		virtual mcLanguageState list(void) = 0;
		virtual mcLanguageState get(string path, string lst) = 0;
		virtual mcLanguageState del(string lst) = 0;
		virtual mcLanguageState post(string inpath, size_t chunk, string outpath, string lst) = 0;
		virtual mcLanguageState put(string inpath, size_t chunk, string outpath, string lst) = 0;
		virtual string current(void) = 0;
		virtual mcLanguageState header(string key, string value, string lst) = 0;
};
