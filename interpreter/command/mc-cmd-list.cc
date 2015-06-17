#include "command/mc-cmd-list.h"
#include <cstdio>

void mcCmdList::help(void){
	fprintf(stdout, "Usage: list\n");
	fprintf(stdout, "  lists opend urls or alias\n");
}

mcLanguageState mcCmdList::parse(mcScanner& scanner, mcIPerformer* performer){
	mcToken token = scanner.scan();
	if(token.id != MC_TOKEN_EOL) {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
		return MC_LANG_CONTINUE;
	}
	return performer->list();
}
