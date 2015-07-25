#include "command/mc-cmd-rm.h"
#include <iostream>

void mcCmdRm::help(void) {
  cout << "  Usage: rm key" << endl;
  cout << "  Option:" << endl;
  cout << "    remove a key." << endl;
}

mcLanguageState mcCmdRm::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_STRING) {
    cerr << "key is missing" << endl;
    return MC_LANG_CONTINUE;
  }
  string key = token.buffer;
  token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  performer->rm(key);
  return MC_LANG_CONTINUE;
}
