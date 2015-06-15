#include "mc-lang.h"
#include <cstring>
#include <cstdio>

mcLanguage::mcLanguage() {
	m_commands.push_back(NULL);		//MC_TOKEN_NONE
	m_commands.push_back(&m_cmd_list);	//MC_TOKEN_LIST
	m_commands.push_back(NULL);		//MC_TOKEN_RUN
	m_commands.push_back(&m_cmd_open);	//MC_TOKEN_OPEN
	m_commands.push_back(&m_cmd_close);	//MC_TOKEN_CLOSE
	m_commands.push_back(&m_cmd_leave);	//MC_TOKEN_LEAVE
	m_commands.push_back(&m_cmd_quit);	//MC_TOKEN_QUIT
	m_commands.push_back(NULL);		//MC_TOKEN_HELP
	m_commands.push_back(&m_cmd_get);	//MC_TOKEN_GET
	m_commands.push_back(&m_cmd_put);	//MC_TOKEN_PUT
	m_commands.push_back(&m_cmd_post);	//MC_TOKEN_POST
	m_commands.push_back(&m_cmd_delete);	//MC_TOKEN_DELETE
	m_commands.push_back(&m_cmd_header);	//MC_TOKEN_HEADER
	m_commands.push_back(&m_cmd_verbose);	//MC_TOKEN_VERBOSE
}

mcLanguageState mcLanguage::parse(const char* line){
	mcScanner scanner(line);
	mcToken token = scanner.scan();
	mcLanguageState state;
	switch(token.id) {
		case MC_TOKEN_RUN:
			state = parse_run(scanner);
			break;
		case MC_TOKEN_HELP:
			state = parse_help(scanner);
			break;
		case MC_TOKEN_LIST:
		case MC_TOKEN_OPEN:
		case MC_TOKEN_CLOSE:
		case MC_TOKEN_LEAVE:
		case MC_TOKEN_QUIT:
		case MC_TOKEN_GET:
		case MC_TOKEN_PUT:
		case MC_TOKEN_POST:
		case MC_TOKEN_DELETE:
		case MC_TOKEN_HEADER:
		case MC_TOKEN_VERBOSE:
			{
				mcCommand* cmd = m_commands[token.id];
				if(!cmd) {
					fprintf(stderr, "%s is not available\n", token.buffer.c_str());
					state = MC_LANG_CONTINUE;
				} else {
					state = cmd->parse(scanner);
				}
			}
			break;
		default:
			fprintf(stderr, "unknown instruction %s\n", token.buffer.c_str());
			state = MC_LANG_CONTINUE;
			break;
	}
	return state;
}

mcLanguageState mcLanguage::parse_run(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}

mcLanguageState mcLanguage::parse_help(mcScanner& scanner){
	mcToken token = scanner.scan();
	switch(token.id) {
		case MC_TOKEN_EOL:
			fprintf(stdout, "type help <command> for help on a specific command\n");
			fprintf(stdout, "Available sub commands:\n");
			for(vector<mcCommand*>::iterator it = m_commands.begin() ; it != m_commands.end() ; it++)
				if (*it) fprintf(stdout, "%s\n", (*it)->command().c_str());
			break;
		case MC_TOKEN_LIST:
		case MC_TOKEN_OPEN:
		case MC_TOKEN_CLOSE:
		case MC_TOKEN_LEAVE:
		case MC_TOKEN_QUIT:
		case MC_TOKEN_GET:
		case MC_TOKEN_PUT:
		case MC_TOKEN_POST:
		case MC_TOKEN_DELETE:
		case MC_TOKEN_HEADER:
		case MC_TOKEN_VERBOSE:
			if(m_commands[token.id]) m_commands[token.id]->help();
			break;
		default:
			fprintf(stderr, "Invalid command %s\n", token.buffer.c_str());
			break;
	}
	return MC_LANG_CONTINUE;
}

