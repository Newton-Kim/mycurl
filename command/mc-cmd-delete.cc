#include "mc-cmd-delete.h"
#include <cstdio>

void mcCmdDelete::help(void){
	fprintf(stdout, "Usage: delete\n");
	fprintf(stdout, "  posts DELETE request to the server.");
}

mcLanguageState mcCmdDelete::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
