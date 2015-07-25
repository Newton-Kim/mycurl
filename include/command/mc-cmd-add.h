#pragma once

#include "mc-cmd.h"

class mcCmdAdd : public mcCommand {
 public:
  string command(void) { return "add"; }
  void help(void);
  mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
