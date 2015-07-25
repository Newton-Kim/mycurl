#pragma once

#include "mc-cmd.h"

class mcCmdRm : public mcCommand {
 public:
  string command(void) { return "rm"; }
  void help(void);
  mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
