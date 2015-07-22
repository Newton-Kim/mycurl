#include "command/mc-cmd-delete.h"
#include <iostream>

void mcCmdDelete::help(void) {
  cout << "  Usage: delete" << endl;
  cout << "  Option:" << endl;
  cout << "    posts DELETE request to the server." << endl;
}

mcLanguageState mcCmdDelete::parse(mcScanner& scanner,
                                   mcIPerformer* performer) {
  string path;
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->del();
  } catch (exception& e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}

