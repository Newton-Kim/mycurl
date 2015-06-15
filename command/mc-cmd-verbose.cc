#include "mc-cmd-verbose.h"
#include <cstdio>

void mcCmdVerbose::help(void){
}

mcLanguageState mcCmdVerbose::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
