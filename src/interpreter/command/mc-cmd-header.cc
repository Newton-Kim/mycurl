#include "command/mc-cmd-header.h"
#include <cstdio>

void mcCmdHeader::help(void) {
  fprintf(stdout, "  Usage: header key value [> list]\n");
  fprintf(stdout, "  Option:\n");
  fprintf(stdout, "    sets a header to a list.\n");
  fprintf(stdout, "    Default list is defhdr.\n");
}

mcLanguageState mcCmdHeader::parse(mcScanner& scanner,
                                   mcIPerformer* performer) {
  string key, val, lst = "defhdr";
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_STRING) {
    fprintf(stderr, "key is missing\n");
    return MC_LANG_CONTINUE;
  } else {
    key = token.buffer;
  }
  token = scanner.tokenize();
  if (token.id != MC_TOKEN_STRING) {
    fprintf(stderr, "value is missing\n");
    return MC_LANG_CONTINUE;
  } else {
    val = token.buffer;
  }
  token = scanner.tokenize();
  if (token.id == MC_TOKEN_GT) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      lst = token.buffer;
    } else {
      fprintf(stderr, "list name is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  mcIConnection* conn = performer->current();
  if(!conn) {
    fprintf(stderr, "invalid handle\n");
    return MC_LANG_CONTINUE;
  }
  conn->header(key, val, lst);
  return MC_LANG_CONTINUE;
}
