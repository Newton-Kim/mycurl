#pragma once

#include "mc-cmd.h"

class mcCmdGet : public mcCommand {
	public:
		string command(void) { return "get"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner);
};
