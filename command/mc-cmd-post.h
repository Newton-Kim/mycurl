#pragma once

#include "mc-cmd.h"

class mcCmdPost : public mcCommand {
	public:
		string command(void) { return "post"; }
		void help(void);
		mcLanguageState parse(mcScanner& scanner);
};
