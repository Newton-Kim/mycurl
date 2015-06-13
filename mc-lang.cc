#include "mc-lang.h"
#include <cstring>
#include <cstdio>

mcLanguageState mcLanguage::parse(const char* line){
	mcScanner scanner(line);
	mcToken token = scanner.scan();
	mcLanguageState state;
	switch(token.id) {
		case MC_TOKEN_OPEN:
			state = parse_open(scanner);
			break;
		case MC_TOKEN_GET:
			state = parse_get(scanner);
			break;
		case MC_TOKEN_PUT:
			state = parse_put(scanner);
			break;
		case MC_TOKEN_POST:
			state = parse_post(scanner);
			break;
		case MC_TOKEN_DELETE:
			state = parse_delete(scanner);
			break;
		case MC_TOKEN_CLOSE:
			state = parse_close(scanner);
			break;
		case MC_TOKEN_OPT:
			state = parse_opt(scanner);
			break;
		case MC_TOKEN_HELP:
			state = parse_help(scanner);
			break;
		case MC_TOKEN_QUIT:
			state = MC_LANG_END;
			break;
		default:
			fprintf(stderr, "unknown instruction %s\n", token.buffer.c_str());
			state = MC_LANG_CONTINUE;
	}
	return state;
}

mcLanguageState mcLanguage::parse_open(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_get(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_put(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_post(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_delete(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_opt(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_close(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_help(mcScanner& scanner){
	fprintf(stdout, "Not implemented\n");
	return MC_LANG_CONTINUE;
}


