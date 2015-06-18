#include "command/mc-cmd-close.h"
#include <cstdio>

void mcCmdClose::help(void){
	fprintf(stdout, "Usage: close\n");
	fprintf(stdout, "  closes current url.\n");
}

mcLanguageState mcCmdClose::parse(mcScanner& scanner, mcIPerformer* performer){
	mcToken token = scanner.tokenize();
	if(token.id != MC_TOKEN_EOL) {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
		return MC_LANG_CONTINUE;
	}
	return performer->close();
}
