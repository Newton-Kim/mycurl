#include "command/mc-cmd-verbose.h"
#include <cstdio>

void mcCmdVerbose::help(void) {
  fprintf(stdout, "  Usage: verbose [on | off]\n");
  fprintf(stdout, "  Option:\n");
  fprintf(stdout, "    turn on or off a verbose mode.\n");
  fprintf(
      stdout,
      "  it returns current mode of verbosness when no argument is given.\n");
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
      fprintf(stderr, "%s\n", e.what());
      return MC_LANG_CONTINUE;
    }
  } else if (token.id == MC_TOKEN_OFF) {
    try {
      performer->verbose_off();
    } catch (exception& e) {
      fprintf(stderr, "%s\n", e.what());
      return MC_LANG_CONTINUE;
    }
  } else if (token.id != MC_TOKEN_EOL) {
    fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
    return MC_LANG_CONTINUE;
  }
  token = scanner.tokenize();
  if (token.id != MC_TOKEN_EOL) {
    fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
    return MC_LANG_CONTINUE;
  }
  bool onoff;
  try {
    performer->verbose(onoff);
    fprintf(stdout, "verbose %s\n", (onoff ? "on" : "off"));
  } catch (exception& e) {
    fprintf(stderr, "%s\n", e.what());
  }
  return MC_LANG_CONTINUE;
}
