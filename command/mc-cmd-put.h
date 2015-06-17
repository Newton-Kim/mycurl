#pragma once

#include "mc-cmd.h"

class mcCmdPut : public mcCommand {
	public:
		string command(void) { return "put"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
