#include "command/mc-cmd-verbose.h"
#include <iostream>

void mcCmdVerbose::help(void) {
  cout <<  "  Usage: verbose [on | off]" << endl;
  cout <<  "  Option:" << endl;
  cout <<  "    turn on or off a verbose mode." << endl;
  cout <<
      "  it returns current mode of verbosness when no argument is given." << endl;
}

mcLanguageState mcCmdVerbose::parse(mcScanner& scanner,
                                    mcIPerformer* performer) {
  mcToken token = scanner.scan();
  if (token.id == MC_TOKEN_EOL) {
    //grammatically OK, but nothing need doing.
  } else if (token.id == MC_TOKEN_ON) {
    try {
      performer->verbose_on();
    } catch (exception& e) {
      cerr <<  e.what() << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  } else if (token.id == MC_TOKEN_OFF) {
    try {
      performer->verbose_off();
    } catch (exception& e) {
      cerr <<  e.what() << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  } else if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument "<< token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  bool onoff;
  try {
    performer->verbose(onoff);
    cout <<  "verbose " << (onoff ? "on" : "off") << endl;
  } catch (exception& e) {
    cerr <<  e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
