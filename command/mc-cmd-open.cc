#include "mc-cmd-open.h"
#include <cstdio>

void mcCmdOpen::help(void){
}

mcLanguageState mcCmdOpen::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
