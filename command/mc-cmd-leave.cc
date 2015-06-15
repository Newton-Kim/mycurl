#include "mc-cmd-leave.h"
#include <cstdio>

void mcCmdLeave::help(void){
}

mcLanguageState mcCmdLeave::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
