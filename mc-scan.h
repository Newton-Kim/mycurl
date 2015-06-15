#pragma once
#include <string>

using namespace std;

typedef enum {
	//General commands
	MC_TOKEN_NONE,
	MC_TOKEN_LIST,
	MC_TOKEN_RUN,
	MC_TOKEN_OPEN,
	MC_TOKEN_CLOSE,
	MC_TOKEN_LEAVE,
	MC_TOKEN_QUIT,
	MC_TOKEN_HELP,
	//CURL commands
	MC_TOKEN_GET,
	MC_TOKEN_PUT,
	MC_TOKEN_POST,
	MC_TOKEN_DELETE,
	//CURL setting commands
	MC_TOKEN_HEADER,
	MC_TOKEN_VERBOSE,
	//parsing tokens
	MC_TOKEN_STRING,
	MC_TOKEN_EOL
} mcTokenID;

class mcToken {
	public:
		const string buffer;
		const mcTokenID id;
		mcToken(mcTokenID tid = MC_TOKEN_NONE, string str = ""): id(tid), buffer(str) {}
		mcToken(const mcToken& token):id(token.id), buffer(token.buffer) {}
};

class mcScanner {
	private:
		const char* m_line;
		char* m_pos;
	public:
		mcScanner(const char* line);
		mcToken scan(void);
};
