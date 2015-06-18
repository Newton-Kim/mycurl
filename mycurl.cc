#include "mc-lang.h"
#include "performer/mc-curl-performer.h"
#include <cstdio>

#define LINE_SIZE	1024
void show_banner(void) {
	fprintf(stdout, "mycurl version 1.0 by Newton Kim\n");
}

int main(int argc, char* argv[]) {
	char buffer[LINE_SIZE];
	mcCurlPerformer performer;
	mcLanguage language(&performer);
	mcLanguageState state = MC_LANG_CONTINUE;
	for(int i = 1 ; i < argc && state == MC_LANG_CONTINUE ; i++) {
		state = language.run(argv[i]);
	}
	if(state != MC_LANG_CONTINUE && state != MC_LANG_HANG) return state;
	show_banner();
	return language.prompt();
}
