#pragma once
#include <string>

using namespace std;

typedef enum {
	MC_TOKEN_NONE,
	MC_TOKEN_OPEN,
	MC_TOKEN_GET,
	MC_TOKEN_PUT,
	MC_TOKEN_POST,
	MC_TOKEN_DELETE,
	MC_TOKEN_CLOSE,
	MC_TOKEN_OPT,
	MC_TOKEN_QUIT,
	MC_TOKEN_STRING,
	MC_TOKEN_EOL,
	MC_TOKEN_HELP
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
