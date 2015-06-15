#include "mc-cmd-put.h"
#include <cstdio>

void mcCmdPut::help(void){
}

mcLanguageState mcCmdPut::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
