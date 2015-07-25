#include "command/mc-cmd-list.h"
#include <iostream>

void mcCmdList::help(void) {
  cout << "  Usage: list" << endl;
  cout << "    lists opend urls or alias" << endl;
}

mcLanguageState mcCmdList::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->list();
  }
  catch (exception & e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
