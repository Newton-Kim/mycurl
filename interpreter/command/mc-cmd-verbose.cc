#include "command/mc-cmd-verbose.h"
#include <cstdio>

void mcCmdVerbose::help(void){
	fprintf(stdout, "Usage: verbose [on | off]\n");
	fprintf(stdout, "  turn on or off a verbose mode.\n");
	fprintf(stdout, "  it returns current mode of verbosness when no argument is given.\n");
}

mcLanguageState mcCmdVerbose::parse(mcScanner& scanner, mcIPerformer* performer){
	mcToken token = scanner.scan();
	if(token.id == MC_TOKEN_EOL) {
		bool onoff;
		performer->verbose(onoff);
		fprintf(stdout, "verbose %s\n", (onoff ? "on" : "off"));
	} else if(token.id == MC_TOKEN_ON) {
		performer->verbose_on();
		token = scanner.scan();
		if(token.id != MC_TOKEN_EOL) fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
	} else if(token.id == MC_TOKEN_OFF) {
		performer->verbose_off();
		token = scanner.scan();
		if(token.id != MC_TOKEN_EOL) fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
	} else {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
	}
	return MC_LANG_CONTINUE;
}
