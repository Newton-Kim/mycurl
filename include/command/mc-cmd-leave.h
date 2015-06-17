#pragma once

#include "mc-cmd.h"

class mcCmdLeave : public mcCommand {
	public:
		string command(void) { return "leave"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner, mcIPerformer* performer);
};
