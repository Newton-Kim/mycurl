#include "command/mc-cmd-quit.h"
#include <cstdio>

void mcCmdQuit::help(void) {
  fprintf(stdout, "Usage: quit\n");
  fprintf(stdout, "  end this program.\n");
}

mcLanguageState mcCmdQuit::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    fprintf(stderr, "invalid argument \"%s\"\n", token.buffer.c_str());
    return MC_LANG_CONTINUE;
  }
  return MC_LANG_END;
}
