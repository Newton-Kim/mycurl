#include "mc-cmd-header.h"
#include <cstdio>

void mcCmdHeader::help(void){
}

mcLanguageState mcCmdHeader::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
