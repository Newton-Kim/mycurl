#include "command/mc-cmd-list.h"
#include <cstdio>

void mcCmdList::help(void) {
  fprintf(stdout, "  Usage: list\n");
  fprintf(stdout, "    lists opend urls or alias\n");
}

mcLanguageState mcCmdList::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
    return MC_LANG_CONTINUE;
  }
  try {
    performer->list();
  } catch (exception& e) {
    fprintf(stderr, "%s\n", e.what());
  }
  return MC_LANG_CONTINUE;
}
