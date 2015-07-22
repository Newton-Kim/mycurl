#include "command/mc-cmd-put.h"
#include <iostream>
#include <cstdlib>

void mcCmdPut::help(void) {
  cout <<  "  Usage: put [< file_in[:number]][ > file_out]" << endl;
  cout <<  "  Option:" << endl;
  cout <<  "    posts GET request to the server." << endl;
  cout <<  "    < operator redirects the request body from the file if "
                  "there is any." << endl;
  cout <<  "    :number specifies the size of the chunk." << endl;
  cout <<  "    Transfer-Encoding:chunked header is automatically "
                  "attached when specified." << endl;
  cout <<  "    > operator redirects the response body to the file if "
                  "there is any." << endl;
}

mcLanguageState mcCmdPut::parse(mcScanner& scanner, mcIPerformer* performer) {
  string inpath, outpath;
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
      cerr <<  "in file path is missing" << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id == MC_TOKEN_GT) {
    token = scanner.tokenize();
    if (token.id == MC_TOKEN_STRING) {
      outpath = token.buffer;
    } else {
      cerr <<  "out file path is missing" << endl;
      return MC_LANG_CONTINUE;
    }
    token = scanner.tokenize();
  }
  if (token.id != MC_TOKEN_EOL) {
    cerr <<  "invalid argument " << token.buffer << endl;
    return MC_LANG_CONTINUE;
  }
  try {
    performer->put(inpath, chunk, outpath);
  } catch (exception& e) {
    cerr << e.what() << endl;
  }
  return MC_LANG_CONTINUE;
}
