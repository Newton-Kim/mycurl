#include "command/mc-cmd-leave.h"
#include <iostream>

void mcCmdLeave::help(void) {
  cout <<  "  Usage: leave" << endl;
  cout <<  "    leave current url." << endl;
  cout <<  "    the opened url is not closed." << endl;
}

mcLanguageState mcCmdLeave::parse(mcScanner& scanner, mcIPerformer* performer) {
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->leave();
  } catch (exception& e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
