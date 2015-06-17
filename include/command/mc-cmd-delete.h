#pragma once

#include "mc-cmd.h"

class mcCmdDelete : public mcCommand {
	public:
		string command(void) { return "delete"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
