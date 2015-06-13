#pragma once

#include "mc-scan.h"

typedef enum {
	MC_LANG_END,
	MC_LANG_ERROR,
	MC_LANG_CONTINUE
} mcLanguageState;

class mcLanguage {
	private:
		mcLanguageState parse_open(mcScanner& scanner);
		mcLanguageState parse_get(mcScanner& scanner);
		mcLanguageState parse_put(mcScanner& scanner);
		mcLanguageState parse_post(mcScanner& scanner);
		mcLanguageState parse_delete(mcScanner& scanner);
		mcLanguageState parse_opt(mcScanner& scanner);
		mcLanguageState parse_close(mcScanner& scanner);
		mcLanguageState parse_help(mcScanner& scanner);
	public:
		mcLanguageState parse(const char* line);
};
