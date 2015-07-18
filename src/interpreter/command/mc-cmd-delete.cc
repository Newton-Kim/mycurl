#include "command/mc-cmd-delete.h"
#include <iostream>

void mcCmdDelete::help(void) {
  cout << "  Usage: delete [- list]" << endl;
  cout << "  Option:" << endl;
  cout << "    posts DELETE request to the server." << endl;
  cout << 
          "    list has headers for the request. Default list is defhdr." << endl;
}

mcLanguageState mcCmdDelete::parse(mcScanner& scanner,
                                   mcIPerformer* performer) {
  string path, lst = "defhdr";
  mcToken token = scanner.tokenize();
  if (token.id == MC_TOKEN_HIPEN) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      lst = token.buffer;
    } else {
      cerr << "list name is missing" << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->del(lst);
  } catch (exception& e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}

