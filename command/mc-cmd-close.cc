#include "mc-cmd-close.h"
#include <cstdio>

void mcCmdClose::help(void){
	fprintf(stdout, "Usage: close\n");
	fprintf(stdout, "  closes current url.\n");
}

mcLanguageState mcCmdClose::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
