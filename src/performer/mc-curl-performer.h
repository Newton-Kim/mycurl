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
  mcLanguageState close(void);
  mcLanguageState verbose(bool& onoff);
  mcLanguageState verbose_on(void);
  mcLanguageState verbose_off(void);
  mcLanguageState follow(bool& onoff);
  mcLanguageState follow_on(void);
  mcLanguageState follow_off(void);
  mcLanguageState leave(void);
  mcLanguageState list(void);
  mcLanguageState get(string path, string lst);
  mcLanguageState del(string lst);
  mcLanguageState post(string inpath, size_t chunk, string outpath, string lst);
  mcLanguageState put(string inpath, size_t chunk, string outpath, string lst);
  string current(void);
  mcLanguageState header(string key, string value, string lst);
};
