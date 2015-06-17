#include "command/mc-cmd-open.h"
#include <cstdio>

void mcCmdOpen::help(void){
	fprintf(stdout, "Usage: open url [! alias] \n");
	fprintf(stdout, "  opens new url.\n");
	fprintf(stdout, "  it enters existing url if it is opened.\n");
}

mcLanguageState mcCmdOpen::parse(mcScanner& scanner, mcIPerformer* performer){
	string alias, url;
	mcLanguageState state = MC_LANG_CONTINUE;
	mcToken token = scanner.scan();
	if(token.id != MC_TOKEN_STRING) {
		fprintf(stderr, "url is missing\n");
		return MC_LANG_CONTINUE;
	} else {
		url = token.buffer;
	}
	token = scanner.scan();
	if(token.id == MC_TOKEN_EXCLAMATION) {
		token = scanner.scan();
		if(token.id != MC_TOKEN_STRING) {
			fprintf(stderr, "alias is missing:%s\n", token.buffer.c_str());
			return MC_LANG_CONTINUE;
		} else {
			alias = token.buffer;
		}
		token = scanner.scan();
	}
	if(token.id != MC_TOKEN_EOL) {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
		return MC_LANG_CONTINUE;
	}
	return performer->open(url, alias);
}
