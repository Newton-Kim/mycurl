#pragma once

#include "mc-cmd.h"

class mcCmdList : public mcCommand {
	public:
		string command(void) { return "list"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner);
};
