#pragma once

#include "mc-cmd.h"

class mcCmdHeader : public mcCommand {
	public:
		string command(void) { return "header"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner);
};
