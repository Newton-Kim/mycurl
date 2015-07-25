#include "command/mc-cmd-follow.h"
#include <iostream>

void mcCmdFollow::help(void) {
  cout << "  Usage: follow [on | off]" << endl;
  cout << "  Option:" << endl;
  cout << "    turn on or off a follow mode." << endl;
  cout << "    it returns current mode of following location when no "
          "argument is given." << endl;
}

mcLanguageState mcCmdFollow::parse(mcScanner& scanner,
                                   mcIPerformer* performer) {
  mcToken token = scanner.scan();
  if (token.id == MC_TOKEN_EOL) {
    //grammatically OK, but nothing need doing.
  } else if (token.id == MC_TOKEN_ON) {
    try {
      performer->follow_on();
    }
    catch (exception & e) {
      cerr << e.what() << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  } else if (token.id == MC_TOKEN_OFF) {
    try {
      performer->follow_off();
    }
    catch (exception & e) {
      cerr << e.what() << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  } else if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  bool onoff;
  try {
    performer->follow(onoff);
    cout << "follow " << (onoff ? "on" : "off") << endl;
  }
  catch (exception & e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
