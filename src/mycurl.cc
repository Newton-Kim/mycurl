#include "mc-lang.h"
#include "performer/mc-curl-performer-factory.h"
#include "version.h"
#include <iostream>
#include <ctime>
#include <cstring>

#define LINE_SIZE 1024
void show_banner(void) {
  cout << "mycurl %s\n", VERSION;
  {
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);
    cout << "Copyright(C) " << timeinfo->tm_year + 1900;
    cout << " Newton Kim (newton.s.kim@gmail.com)" << endl;
    cout << "License MIT: MIT License(http://opensource.org/licenses/MIT)"
         << endl;
  }
  cout << endl;
}

void show_version(void) { cout << VERSION << endl; }

void show_help(mcLanguage& language) {
  cout << "Usage: mycurl [option]... [script]..." << endl;
  cout << endl;
  cout << "Option:" << endl;
  cout << "  -h, --help     shows this help screen." << endl;
  cout << "  -v, --version  shows the version." << endl;
  cout << endl;
  cout << "Mycul langugage:" << endl;
  language.show_help();
  cout << endl;
  cout << "Report bugs to <newton.s.kim@gmail.com>" << endl;
}

int main(int argc, char* argv[]) {
  char buffer[LINE_SIZE];
  mcIPerformer* performer = mcCurlPerformerFactory::create();
  mcLanguage language(performer);
  mcLanguageState state = MC_LANG_CONTINUE;
  for (int i = 1; i < argc && state == MC_LANG_CONTINUE; i++) {
    if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
      show_banner();
      show_help(language);
      return 0;
    } else if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-v")) {
      show_version();
      return 0;
    } else if (argv[i][0] == '-') {
      cerr << "invalid argument " << argv[i] << endl;
      return 1;
    }
    state = language.run(argv[i]);
  }
  if (state != MC_LANG_CONTINUE && state != MC_LANG_HANG) return state;
  show_banner();
  int ret = language.prompt();
  delete performer;
  return ret;
}
