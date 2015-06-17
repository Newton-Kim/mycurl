#include "mc-lang.h"
#include "mc-curl-performer.h"
#include <cstdio>

#define LINE_SIZE	1024
int main(int argc, char* argv[]) {
	char buffer[LINE_SIZE];
	mcCurlPerformer performer;
	mcLanguage language(&performer);
	mcLanguageState state = MC_LANG_CONTINUE;
	for(int i = 1 ; i < argc && state == MC_LANG_CONTINUE ; i++) {
		state = language.run(argv[i]);
	}
	if(state != MC_LANG_CONTINUE && state != MC_LANG_HANG) return state;
	return language.prompt();
}
