#pragma once

#include "mc-cmd.h"

class mcCmdFollow : public mcCommand {
 public:
  string command(void) { return "follow"; }
  void help(void);
  mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
