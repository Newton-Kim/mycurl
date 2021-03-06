#include "mc-curl-file.h"
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

mcCurlFile::mcCurlFile(const char* path, const char* mode, size_t chunk) {
  m_fd = fopen(path, mode);
  if (!m_fd) throw runtime_error(strerror(errno));
  m_chunk = chunk;
}

mcCurlFile::~mcCurlFile() {
  if (m_fd) fclose(m_fd);
}

size_t mcCurlFile::fread(void* buffer, size_t size, size_t nmemb) {
  size_t nitems = (m_chunk) ? min(nmemb, m_chunk) : nmemb;
  return ::fread(buffer, size, nmemb, m_fd);
}

size_t mcCurlFile::fwrite(void* buffer, size_t size, size_t nmemb) {
  return ::fread(buffer, size, nmemb, m_fd);
}

size_t mcCurlFile::fsize(void) {
  size_t pos = ftell(m_fd);
  fseek(m_fd, 0, SEEK_END);
  size_t sz = ftell(m_fd);
  fseek(m_fd, pos, SEEK_SET);
  return sz;
}
