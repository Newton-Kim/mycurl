#include "command/mc-cmd-form.h"
#include <cstdio>

void mcCmdForm::help(void) {
  fprintf(stdout, "  Usage: form key value [> list]\n");
  fprintf(stdout, "  Option:\n");
  fprintf(stdout, "    sets a form header to a list.\n");
  fprintf(stdout, "    Default list is deffrm.\n");
}

mcLanguageState mcCmdForm::parse(mcScanner& scanner,
                                   mcIPerformer* performer) {
  string key, val, lst = "deffrm";
  mcToken token = scanner.tokenize();
  if (token.id != MC_TOKEN_STRING) {
    fprintf(stderr, "key is missing\n");
    return MC_LANG_CONTINUE;
  } else {
    key = token.buffer;
  }
  token = scanner.tokenize();
  if (token.id != MC_TOKEN_STRING) {
    fprintf(stderr, "value is missing\n");
    return MC_LANG_CONTINUE;
  } else {
    val = token.buffer;
  }
  token = scanner.tokenize();
  if (token.id == MC_TOKEN_GT) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      lst = token.buffer;
    } else {
      fprintf(stderr, "list name is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  return performer->form(key, val, lst);
}
