#include "command/mc-cmd-follow.h"
#include <cstdio>

void mcCmdFollow::help(void){
	fprintf(stdout, "Usage: follow [on | off]\n");
	fprintf(stdout, "  turn on or off a follow mode.\n");
	fprintf(stdout, "  it returns current mode of following location when no argument is given.\n");
}

mcLanguageState mcCmdFollow::parse(mcScanner& scanner, mcIPerformer* performer){
	mcToken token = scanner.scan();
	if(token.id == MC_TOKEN_EOL) {
		//grammatically OK, but nothing need doing.
	} else if(token.id == MC_TOKEN_ON) {
		performer->follow_on();
		token = scanner.tokenize();
		if(token.id != MC_TOKEN_EOL) fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
	} else if(token.id == MC_TOKEN_OFF) {
		performer->follow_off();
		token = scanner.tokenize();
		if(token.id != MC_TOKEN_EOL) fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
	} else {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
	}
	bool onoff;
	performer->follow(onoff);
	fprintf(stdout, "follow %s\n", (onoff ? "on" : "off"));
	return MC_LANG_CONTINUE;
}
