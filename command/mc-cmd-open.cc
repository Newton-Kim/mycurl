#include "mc-cmd-open.h"
#include <cstdio>

void mcCmdOpen::help(void){
	fprintf(stdout, "Usage: open url [! alias] \n");
	fprintf(stdout, "  opens new url.\n");
	fprintf(stdout, "  it enters existing url if it is opened.\n");
}

mcLanguageState mcCmdOpen::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
