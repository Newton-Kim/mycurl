#include "command/mc-cmd-add.h"
#include <iostream>

void mcCmdAdd::help(void) {
  cout <<  "  Usage: add key value" << endl;
  cout <<  "  Option:" << endl;
  cout <<  "    add a value to a key. If there is a value or values, this value is appended." << endl;
}

mcLanguageState mcCmdAdd::parse(mcScanner& scanner,
                                    mcIPerformer* performer) {
  mcToken token = scanner.scan();
  if (token.id != MC_TOKEN_STRING) {
	  cerr << "key is missing" << endl;
    return MC_LANG_CONTINUE;
  }
  string key = token.buffer;
  if (token.id != MC_TOKEN_STRING) {
	  cerr << "value is missing" << endl;
    return MC_LANG_CONTINUE;
  }
  string value = token.buffer;
  if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  performer->add(key, value);
  return MC_LANG_CONTINUE;
}
