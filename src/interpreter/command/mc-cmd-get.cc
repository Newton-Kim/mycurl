#include "command/mc-cmd-get.h"
#include <iostream>

void mcCmdGet::help(void) {
  cout << "  Usage: get [> file]" << endl;
  cout << "  Option:" << endl;
  cout << "    posts GET request to the server." << endl;
  cout << "    > operator redirects the response body to the file if "
          "there is any." << endl;
  cout << "    list has headers for the request. Default list is defhdr."
       << endl;
}

mcLanguageState mcCmdGet::parse(mcScanner& scanner, mcIPerformer* performer) {
  string path;
  mcToken token = scanner.tokenize();
  if (token.id == MC_TOKEN_GT) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      path = token.buffer;
    } else {
      cerr << "file path is missing" << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->get(path);
  }
  catch (exception & e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
