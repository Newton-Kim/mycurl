#include "command/mc-cmd-follow.h"
#include <cstdio>

void mcCmdFollow::help(void) {
  fprintf(stdout, "  Usage: follow [on | off]\n");
  fprintf(stdout, "  Option:\n");
  fprintf(stdout, "    turn on or off a follow mode.\n");
  fprintf(stdout, "    it returns current mode of following location when no "
                  "argument is given.\n");
}

mcLanguageState mcCmdFollow::parse(mcScanner& scanner,
                                   mcIPerformer* performer) {
  mcIConnection* conn = performer->current();
  if(!conn) {
    fprintf(stderr, "invalid handle\n");
    return MC_LANG_CONTINUE;
  }
  mcToken token = scanner.scan();
  if (token.id == MC_TOKEN_EOL) {
    //grammatically OK, but nothing need doing.
  } else if (token.id == MC_TOKEN_ON) {
    conn->follow(true);
    token = scanner.tokenize();
    if (token.id != MC_TOKEN_EOL)
      fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
  } else if (token.id == MC_TOKEN_OFF) {
    conn->follow(false);
    token = scanner.tokenize();
    if (token.id != MC_TOKEN_EOL)
      fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
  } else {
    fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
  }
  bool onoff = conn->follow();
  fprintf(stdout, "follow %s\n", (onoff ? "on" : "off"));
  return MC_LANG_CONTINUE;
}
