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
  MC_TOKEN_FOLLOW,
  //parsing tokens
  MC_TOKEN_STRING,
  MC_TOKEN_EXCLAMATION,
  MC_TOKEN_HIPEN,
  MC_TOKEN_LT,
  MC_TOKEN_GT,
  MC_TOKEN_ON,
  MC_TOKEN_OFF,
  MC_TOKEN_EOL
} mcTokenID;

class mcToken {
 public:
  string buffer;
  mcTokenID id;
  mcToken(mcTokenID tid = MC_TOKEN_NONE, string str = "")
      : id(tid), buffer(str) {}
  mcToken(const mcToken& token) : id(token.id), buffer(token.buffer) {}
  mcToken operator=(mcToken token) {
    id = token.id;
    buffer = token.buffer;
    return *this;
  }
};

class mcScanner {
 private:
  const char* m_line;
  char* m_pos;

 public:
  mcScanner(const char* line);
  mcToken tokenize(void);
  mcToken scan(void);
};
