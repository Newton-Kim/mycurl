#include "mc-scan.h"
#include <cstdio>
#include <map>

struct mcSymbolTable {
  const char* str;
  mcTokenID id;
} s_table[] = { { "list", MC_TOKEN_LIST }, { "run", MC_TOKEN_RUN },
                { "open", MC_TOKEN_OPEN }, { "close", MC_TOKEN_CLOSE },
                { "leave", MC_TOKEN_LEAVE }, { "quit", MC_TOKEN_QUIT },
                { "help", MC_TOKEN_HELP }, { "get", MC_TOKEN_GET },
                { "put", MC_TOKEN_PUT }, { "post", MC_TOKEN_POST },
                { "verbose", MC_TOKEN_VERBOSE }, { "follow", MC_TOKEN_FOLLOW },
                { "add", MC_TOKEN_ADD }, { "rm", MC_TOKEN_RM },
                { "delete", MC_TOKEN_DELETE }, { "on", MC_TOKEN_ON },
                { "off", MC_TOKEN_OFF }, { NULL, MC_TOKEN_NONE } };

map<string, mcTokenID> s_map;

mcScanner::mcScanner(const char* line) : m_line(line), m_pos((char*)line) {
  if (s_map.empty()) {
    for (size_t i = 0; s_table[i].str; i++)
      s_map[s_table[i].str] = s_table[i].id;
  }
}

mcToken mcScanner::scan(void) {
  mcToken token = tokenize();
  if (token.id == MC_TOKEN_STRING) {
    map<string, mcTokenID>::iterator it = s_map.find(token.buffer);
    if (it != s_map.end()) token.id = it->second;
  }
  return token;
}

mcToken mcScanner::tokenize(void) {
  mcTokenID id;
  string buffer;

  while (*m_pos == ' ' || *m_pos == '\t')
    m_pos++;
  if (*m_pos == '#') while (*m_pos && *m_pos != '\n')
      m_pos++;
  switch (*m_pos) {
    case '!':
      id = MC_TOKEN_EXCLAMATION;
      buffer += *m_pos;
      m_pos++;
      break;
    case '<':
      id = MC_TOKEN_LT;
      buffer += *m_pos;
      m_pos++;
      break;
    case '>':
      id = MC_TOKEN_GT;
      buffer += *m_pos;
      m_pos++;
      break;
    case '-':
      id = MC_TOKEN_HIPEN;
      buffer += *m_pos;
      m_pos++;
      break;
    case '+':
      id = MC_TOKEN_PLUS;
      buffer += *m_pos;
      m_pos++;
      break;
    default:
      if (*m_pos == '\n' || !*m_pos) {
        id = MC_TOKEN_EOL;
        m_pos++;
      } else {
        while (*m_pos && *m_pos != '#' && *m_pos != '\n' && *m_pos != ' ' &&
               *m_pos != '\t') {
          buffer += *m_pos;
          m_pos++;
        }
        id = MC_TOKEN_STRING;
      }
      break;
  }
  mcToken token(id, buffer);
  return token;
}
