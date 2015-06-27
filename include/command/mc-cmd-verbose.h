#pragma once

#include "mc-cmd.h"

class mcCmdVerbose : public mcCommand {
 public:
  string command(void) { return "verbose"; }
  void help(void);
  mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
