#pragma once

#include "mc-cmd.h"

class mcCmdQuit : public mcCommand {
	public:
		string command(void) { return "quit"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner);
};
