#include "mc-lang.h"
#include "performer/mc-curl-performer.h"
#include "version.h"
#include <cstdio>
#include <ctime>
#include <cstring>

#define LINE_SIZE 1024
void show_banner(void) {
  fprintf(stdout, "mycurl %s\n", VERSION);
  {
    time_t rawtime;
    time (&rawtime);
    struct tm * timeinfo = localtime(&rawtime);
    fprintf(stdout, "Copyright(C) %d Newton Kim (newton.s.kim@gmail.com)\n", timeinfo->tm_year + 1900);
    fprintf(stdout, "License MIT: MIT License(http://opensource.org/licenses/MIT)\n");
  }
  fprintf(stdout, "\n");
}

void show_version(void) {
    fprintf(stdout, "%s\n", VERSION);
}

void show_help(void) {
  fprintf(stdout, "Usage: mycurl [option]... [script]...\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "Option:\n");
  fprintf(stdout, "  -h, --help     shows this help screen.\n");
  fprintf(stdout, "  -v, --version  shows the version.\n");
}

int main(int argc, char* argv[]) {
  char buffer[LINE_SIZE];
  mcCurlPerformer performer;
  mcLanguage language(&performer);
  mcLanguageState state = MC_LANG_CONTINUE;
  for (int i = 1; i < argc && state == MC_LANG_CONTINUE; i++) {
    if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
      show_banner();
      show_help();
      return 0;
    } else if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-v")) {
      show_version();
      return 0;
    } else if (argv[i][0] == '-') {
      fprintf(stderr, "invalid argument %s\n", argv[i]);
      return 1;
    }
    state = language.run(argv[i]);
  }
  if (state != MC_LANG_CONTINUE && state != MC_LANG_HANG) return state;
  show_banner();
  return language.prompt();
}
