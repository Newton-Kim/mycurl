#include "mc-cmd-list.h"
#include <cstdio>

void mcCmdList::help(void){
}

mcLanguageState mcCmdList::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
