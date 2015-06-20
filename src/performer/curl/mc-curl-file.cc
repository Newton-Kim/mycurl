#include "mc-curl-file.h"
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <cmath>

using namespace std;

mcCurlFile::mcCurlFile(const char* path, const char* mode, size_t chunk) {
	m_fd = fopen(path, mode);
	if(!m_fd) throw runtime_error(strerror(errno));
	m_chunk = chunk;
}

mcCurlFile::~mcCurlFile() {
	if(m_fd) fclose(m_fd);
}

size_t mcCurlFile::fread(void* buffer, size_t size, size_t nmemb){
	size_t nitems = min(nmemb, m_chunk);
	return ::fread(buffer, size, nmemb, m_fd);
}
