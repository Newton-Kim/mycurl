#pragma once

#include "mc-cmd.h"

class mcCmdForm: public mcCommand {
 public:
  string command(void) { return "form"; }
  void help(void);
  mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
