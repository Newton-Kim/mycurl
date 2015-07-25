#include "command/mc-cmd-open.h"
#include <iostream>

void mcCmdOpen::help(void) {
  cout << "  Usage: open url [! alias] " << endl;
  cout << "  Option:" << endl;
  cout << "    opens new url." << endl;
  cout << "    it enters existing url if it is opened." << endl;
}

mcLanguageState mcCmdOpen::parse(mcScanner& scanner, mcIPerformer* performer) {
  string alias, url;
  mcLanguageState state = MC_LANG_CONTINUE;
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_STRING) {
    cerr << "url is missing" << endl;
    return MC_LANG_CONTINUE;
  } else {
    url = token.buffer;
  }
  token = scanner.tokenize();
  if (token.id == MC_TOKEN_EXCLAMATION) {
    token = scanner.tokenize();
    if (token.id != MC_TOKEN_STRING) {
      cerr << "alias is missing:" << token.buffer << endl;
      return MC_LANG_CONTINUE;
    } else {
      alias = token.buffer;
    }
    token = scanner.tokenize();
  }
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->open(url, alias);
  }
  catch (exception & e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
