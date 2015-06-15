#pragma once

#include "mc-cmd.h"

class mcCmdOpen : public mcCommand {
	public:
		string command(void) { return "open"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner);
};
