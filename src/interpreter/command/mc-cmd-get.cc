#include "command/mc-cmd-get.h"
#include <cstdio>

void mcCmdGet::help(void) {
  fprintf(stdout, "  Usage: get [> file] [- list]\n");
  fprintf(stdout, "  Option:\n");
  fprintf(stdout, "    posts GET request to the server.\n");
  fprintf(stdout, "    > operator redirects the response body to the file if "
                  "there is any.\n");
  fprintf(stdout,
          "    list has headers for the request. Default list is defhdr.\n");
}

mcLanguageState mcCmdGet::parse(mcScanner& scanner, mcIPerformer* performer) {
  string path, lst = "defhdr";
  mcToken token = scanner.tokenize();
  if (token.id == MC_TOKEN_GT) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      path = token.buffer;
    } else {
      fprintf(stderr, "file path is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id == MC_TOKEN_HIPEN) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      lst = token.buffer;
    } else {
      fprintf(stderr, "list name is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id != MC_TOKEN_EOL) {
    fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
    return MC_LANG_CONTINUE;
  }
  performer->get(path, lst);
  return MC_LANG_CONTINUE;
}
