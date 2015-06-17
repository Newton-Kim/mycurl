#pragma once

#include "mc-cmd.h"

class mcCmdClose: public mcCommand {
	public:
		string command(void) { return "close"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
