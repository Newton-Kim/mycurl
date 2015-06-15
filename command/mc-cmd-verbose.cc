#include "mc-cmd-verbose.h"
#include <cstdio>

void mcCmdVerbose::help(void){
	fprintf(stdout, "Usage: verbose [on | off]\n");
	fprintf(stdout, "  turn on or off a verbose mode.\n");
	fprintf(stdout, "  it returns current mode of verbosness when no argument is given.\n");
}

mcLanguageState mcCmdVerbose::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
