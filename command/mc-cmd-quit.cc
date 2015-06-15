#include "mc-cmd-quit.h"
#include <cstdio>

void mcCmdQuit::help(void){
	fprintf(stdout, "Usage: quit\n");
	fprintf(stdout, "  end this program.\n");
}

mcLanguageState mcCmdQuit::parse(mcScanner& scanner){
	return MC_LANG_END;
}
