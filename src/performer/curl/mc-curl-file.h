#pragma once
#include <cstdio>

class mcCurlFile {
 private:
  FILE* m_fd;
  size_t m_chunk;

 public:
  mcCurlFile(const char* path, const char* mode, size_t chunk);
  ~mcCurlFile();
  size_t fread(void* buffer, size_t size, size_t nmemb);
};
