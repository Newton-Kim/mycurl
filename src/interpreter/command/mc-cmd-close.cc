#include "command/mc-cmd-close.h"
#include <iostream>

void mcCmdClose::help(void) {
  cout << "  Usage: close" << endl;
  cout << "    closes current url." << endl;
}

mcLanguageState mcCmdClose::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument %s" << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->close();
  }
  catch (exception & e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
