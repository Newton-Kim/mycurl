#include "mc-cmd-get.h"
#include <cstdio>

void mcCmdGet::help(void){
	fprintf(stdout, "Usage: get [> file] [- list]\n");
	fprintf(stdout, "  posts GET request to the server.\n");
	fprintf(stdout, "  > operator redirects the response body to the file if there is any.\n");
	fprintf(stdout, "  list has headers for the request. Default list is defhdr.\n");
}

mcLanguageState mcCmdGet::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
