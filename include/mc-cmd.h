#pragma once

#include "mc-scan.h"
#include "mc-types.h"
#include "mc-scan.h"
#include <string>

using namespace std;

class mcCommand {
 public:
  virtual string command(void) = 0;
  virtual void help(void) = 0;
  virtual mcLanguageState parse(mcScanner& scanner,
                                mcIPerformer* performer) = 0;
};
