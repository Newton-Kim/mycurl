#include "mc-lang.h"
#include "performer/mc-curl-performer.h"
#include "version.h"
#include <cstdio>

#define LINE_SIZE	1024
void show_banner(void) {
	fprintf(stdout, "mycurl version %s by Newton Kim\n", VERSION);
}

int main(int argc, char* argv[]) {
	char buffer[LINE_SIZE];
	mcCurlPerformer performer;
	mcLanguage language(&performer);
	mcLanguageState state = MC_LANG_CONTINUE;
	for(int i = 1 ; i < argc && state == MC_LANG_CONTINUE ; i++) {
		if(argv[i][0] == '-') {
			fprintf(stderr, "invalid argument %s\n", argv[i]);
			return 1;
		}
		state = language.run(argv[i]);
	}
	if(state != MC_LANG_CONTINUE && state != MC_LANG_HANG) return state;
	show_banner();
	return language.prompt();
}
