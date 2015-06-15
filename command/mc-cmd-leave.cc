#include "mc-cmd-leave.h"
#include <cstdio>

void mcCmdLeave::help(void){
	fprintf(stdout, "Usage: leave\n");
	fprintf(stdout, "  leave current url.\n");
	fprintf(stdout, "  the opened url is not closed.\n");
}

mcLanguageState mcCmdLeave::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
