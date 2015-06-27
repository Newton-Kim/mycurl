#include "command/mc-cmd-leave.h"
#include <cstdio>

void mcCmdLeave::help(void) {
  fprintf(stdout, "Usage: leave\n");
  fprintf(stdout, "  leave current url.\n");
  fprintf(stdout, "  the opened url is not closed.\n");
}

mcLanguageState mcCmdLeave::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
    return MC_LANG_CONTINUE;
  }
  return performer->leave();
}
