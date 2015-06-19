#include "mc-lang.h"
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <stdexcept>
#include <readline/readline.h>
#include <readline/history.h>

#define MC_LINE_SIZE	1024

mcLanguage::mcLanguage(mcIPerformer* performer):m_performer(performer) {
	if(!m_performer) throw runtime_error("invalid performer");
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

mcLanguageState mcLanguage::run(string path){
	mcLanguageState state;
	FILE* fd = fopen(path.c_str(), "rb");
	if(!fd) {
		fprintf(stderr, "%s\n", strerror(errno));
		return MC_LANG_HANG;
	}
	char buffer[MC_LINE_SIZE];
	do {
		char* line = fgets(buffer, MC_LINE_SIZE, fd);
		if(!line) {
			return MC_LANG_HANG;
		} else if(!line[0] || line[0] == '\n' || line[0] == '#') {
			state = MC_LANG_CONTINUE;
		} else {
			state = parse(line);
		}
	} while (state == MC_LANG_CONTINUE);
	return state;
}

mcLanguageState mcLanguage::prompt(void){
	mcLanguageState state;
	char* line = NULL;
	do {
		if(line) {
			delete line;
			line = NULL;
		}
		string prompt = m_performer->current() + "> ";
		line = readline(prompt.c_str());
		if(!line) {
			fprintf(stderr, "IO error\n");
			return MC_LANG_HANG;
		}
		add_history(line);
		if(!line[0] || line[0] == '\n' || line[0] == '#') {
			state = MC_LANG_CONTINUE;
		} else {
			state = parse(line);
		}
	} while (state == MC_LANG_CONTINUE);
	return state;
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
					state = cmd->parse(scanner, m_performer);
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
	mcLanguageState state;
	mcToken token;
	while(token = scanner.scan(), token.id == MC_TOKEN_STRING) {
		state = run(token.buffer);
	}
	if (token.id != MC_TOKEN_EOL) {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
		state = MC_LANG_ERROR;
	}
	return state;
}

mcLanguageState mcLanguage::parse_help(mcScanner& scanner){
	mcToken token = scanner.scan();
	switch(token.id) {
		case MC_TOKEN_EOL:
			fprintf(stdout, "type help <command> for help on a specific command\n");
			fprintf(stdout, "Available sub commands:\n");
			for(vector<mcCommand*>::iterator it = m_commands.begin() ; it != m_commands.end() ; it++)
				if (*it) fprintf(stdout, "%s\n", (*it)->command().c_str());
			return MC_LANG_CONTINUE;
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
		case MC_TOKEN_RUN:
			fprintf(stdout, "Usage: run [file]...\n");
			fprintf(stdout, "  runs macro files\n");
			break;
		default:
			fprintf(stderr, "Invalid command %s\n", token.buffer.c_str());
			break;
	}
	mcLanguageState state = MC_LANG_CONTINUE;
	token = scanner.scan();
	if (token.id != MC_TOKEN_EOL) {
		fprintf(stderr, "invalid argument %s\n", token.buffer.c_str());
		state = MC_LANG_ERROR;
	}
	return state;
}

