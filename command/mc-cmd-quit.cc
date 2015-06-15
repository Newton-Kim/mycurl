#include "mc-cmd-quit.h"
#include <cstdio>

void mcCmdQuit::help(void){
}

mcLanguageState mcCmdQuit::parse(mcScanner& scanner){
	return MC_LANG_END;
}
