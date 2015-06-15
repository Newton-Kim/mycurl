#include "mc-cmd-put.h"
#include <cstdio>

void mcCmdPut::help(void){
	fprintf(stdout, "Usage: put [< file_in[:number]][ > file_out][ - list]\n");
	fprintf(stdout, "  posts GET request to the server.\n");
	fprintf(stdout, "  < operator redirects the request body from the file if there is any.\n");
	fprintf(stdout, "  :number specifies the size of the chunk.\n");
	fprintf(stdout, "  Transfer-Encoding:chunked header is automatically attached when specified.\n");
	fprintf(stdout, "  > operator redirects the response body to the file if there is any.\n");
	fprintf(stdout, "  list has headers for the request. Default list is defhdr.\n");
}

mcLanguageState mcCmdPut::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
