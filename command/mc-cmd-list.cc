#include "mc-cmd-list.h"
#include <cstdio>

void mcCmdList::help(void){
	fprintf(stdout, "Usage: list\n");
	fprintf(stdout, "  lists opend urls or alias\n");
}

mcLanguageState mcCmdList::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
