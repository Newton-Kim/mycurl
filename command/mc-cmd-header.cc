#include "mc-cmd-header.h"
#include <cstdio>

void mcCmdHeader::help(void){
	fprintf(stdout, "Usage: header key value [> list]\n");
	fprintf(stdout, "  sets a header to a list.\n");
	fprintf(stdout, "  Default list is defhdr.\n");
}

mcLanguageState mcCmdHeader::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
