#include "mc-cmd-get.h"
#include <cstdio>

void mcCmdGet::help(void){
}

mcLanguageState mcCmdGet::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
