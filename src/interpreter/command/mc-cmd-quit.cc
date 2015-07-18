#include "command/mc-cmd-quit.h"
#include <iostream>

void mcCmdQuit::help(void) {
  cout <<  "  Usage: quit" << endl;
  cout <<  "    end this program." << endl;
}

mcLanguageState mcCmdQuit::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  return MC_LANG_END;
}
