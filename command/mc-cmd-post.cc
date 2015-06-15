#include "mc-cmd-post.h"
#include <cstdio>

void mcCmdPost::help(void){
	fprintf(stdout, "Usage: post [< file_in[:number]][ > file_out][ - list]\n");
	fprintf(stdout, "  posts GET request to the server.\n");
	fprintf(stdout, "  < operator redirects the request body from the file if there is any.\n");
	fprintf(stdout, "  :number specifies the size of the chunk.\n");
	fprintf(stdout, "  Transfer-Encoding:chunked header is automatically attached when specified.\n");
	fprintf(stdout, "  > operator redirects the response body to the file if there is any.\n");
	fprintf(stdout, "  list has headers for the request. Default list is defhdr.\n");
}

mcLanguageState mcCmdPost::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
