#include "command/mc-cmd-post.h"
#include <cstdio>
#include <cstdlib>

void mcCmdPost::help(void) {
  fprintf(stdout, "  Usage: post [< file_in[:number]][ > file_out][ - list][ + form]\n");
  fprintf(stdout, "  Option:\n");
  fprintf(stdout, "    posts GET request to the server.\n");
  fprintf(stdout, "    < operator redirects the request body from the file if "
                  "there is any.\n");
  fprintf(stdout, "    :number specifies the size of the chunk.\n");
  fprintf(stdout, "    Transfer-Encoding:chunked header is automatically "
                  "attached when it is specified.\n");
  fprintf(stdout, "    > operator redirects the response body to the file if "
                  "there is any.\n");
  fprintf(stdout,
          "    list has headers for the request. Default list is defhdr.\n");
  fprintf(stdout,
          "    form has headers for the chunks of the request. Default form is deffrm.\n");
}

mcLanguageState mcCmdPost::parse(mcScanner& scanner, mcIPerformer* performer) {
  string inpath, outpath, lst = "defhdr", frm = "deffrm";
  size_t chunk = 0;
  mcToken token = scanner.tokenize();
  if (token.id == MC_TOKEN_LT) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      size_t pos = token.buffer.find(':');
      if (pos == string::npos) {
        inpath = token.buffer;
      } else {
        inpath = token.buffer.substr(0, pos);
        chunk = atoi(token.buffer.substr(pos + 1).c_str());
      }
    } else {
      fprintf(stderr, "in file path is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id == MC_TOKEN_GT) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      outpath = token.buffer;
    } else {
      fprintf(stderr, "out file path is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id == MC_TOKEN_HIPEN) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      lst = token.buffer;
    } else {
      fprintf(stderr, "list name is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id == MC_TOKEN_PLUS) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      frm = token.buffer;
    } else {
      fprintf(stderr, "form name is missing\n");
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id != MC_TOKEN_EOL) {
    fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
    return MC_LANG_CONTINUE;
  }
  mcIConnection* conn = performer->current();
  if(!conn) {
    fprintf(stderr, "invalid handle\n");
    return MC_LANG_CONTINUE;
  }
  conn->post(inpath, chunk, outpath, lst, frm);
  return MC_LANG_CONTINUE;
}
