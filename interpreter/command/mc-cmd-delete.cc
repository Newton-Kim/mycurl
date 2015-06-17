#include "command/mc-cmd-delete.h"
#include <cstdio>

void mcCmdDelete::help(void){
	fprintf(stdout, "Usage: delete [- list]\n");
	fprintf(stdout, "  posts DELETE request to the server.");
	fprintf(stdout, "  list has headers for the request. Default list is defhdr.\n");
}

mcLanguageState mcCmdDelete::parse(mcScanner& scanner, mcIPerformer* performer){
	string path, lst = "defhdr";
	mcToken token = scanner.scan();
	if(token.id == MC_TOKEN_HIPEN) {
		token = scanner.scan();
		if(token.id == MC_TOKEN_STRING) {
			lst = token.buffer;
		} else {
			fprintf(stderr, "list name is missing\n");
			return MC_LANG_CONTINUE;
		}
		token = scanner.scan();
	}
	if(token.id != MC_TOKEN_EOL) {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
		return MC_LANG_CONTINUE;
	}
	return performer->del(lst);
}
