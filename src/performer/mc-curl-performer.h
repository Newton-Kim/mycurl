#pragma once
#include "mc-types.h"
#include "curl/mc-curl.h"

class mcCurlPerformer : public mcIPerformer {
 private:
  map<string, mcCurl*> m_map;
  mcCurl* m_current;

 public:
  mcCurlPerformer();
  mcLanguageState open(string url, string alias);
  mcLanguageState close(mcIConnection* conn);
  mcLanguageState verbose(bool& onoff);
  mcLanguageState verbose_on(void);
  mcLanguageState verbose_off(void);
  mcLanguageState follow(bool& onoff);
  mcLanguageState follow_on(void);
  mcLanguageState follow_off(void);
  mcLanguageState leave(void);
  mcLanguageState list(void);
  mcIConnection* current(void);
};
