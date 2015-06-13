#include "mc-lang.h"
#include <cstdio>

#define LINE_SIZE	1024
int main(int argc, char* argv[]) {
	char buffer[LINE_SIZE];
	mcLanguage language;
	mcLanguageState state = MC_LANG_CONTINUE;
	do {
		fprintf(stdout, "mycurl> ");
		char* line = fgets(buffer, LINE_SIZE, stdin);
		if(!line) {
			fprintf(stderr, "IO error\n");
			return 1;
		}
		state = language.parse(line);
	} while (state == MC_LANG_CONTINUE);
	return state;
}
