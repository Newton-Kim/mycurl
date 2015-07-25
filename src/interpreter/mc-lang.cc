#include "mc-lang.h"
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <stdexcept>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

#define MC_LINE_SIZE 1024

static vector<string> s_commands;

/* Generator function for command completion.  STATE lets us know whether
   to start from scratch; without any state (i.e. STATE == 0), then we
   start at the top of the list. */
char* mycurl_command_generator(const char* text, int state) {
  static int list_index, len;

  /* If this is a new word to complete, initialize now.  This includes
 	   saving the length of TEXT for efficiency, and initializing the index
 	   variable to 0. */
  if (!state) {
    list_index = 0;
    len = strlen(text);
  }

  /* Return the next name which partially matches from the command list. */
  //	while (name = s_commands[list_index].name.c_str()) {
  while (list_index < s_commands.size()) {
    const char* name = s_commands[list_index].c_str();
    list_index++;

    if (strncmp(name, text, len) == 0) return (strdup(name));
  }

  /* If no names matched, then return NULL. */
  return ((char*)NULL);
}

/* Attempt to complete on the contents of TEXT.  START and END show the
   region of TEXT that contains the word to complete.  We can use the
   entire line in case we want to do some simple parsing.  Return the
   array of matches, or NULL if there aren't any. */
char** mycurl_completion(const char* text, int start, int end) {
  char** matches = (char**)NULL;

  /* If this word is at the start of the line, then it is a command
 	   to complete.  Otherwise it is the name of a file in the current
 	   directory. */
  if (start == 0)
    matches = rl_completion_matches(text, mycurl_command_generator);

  return (matches);
}

mcLanguage::mcLanguage(mcIPerformer* performer) : m_performer(performer) {
  if (!m_performer) throw runtime_error("invalid performer");
  m_commands.push_back(NULL);            //MC_TOKEN_NONE
  m_commands.push_back(&m_cmd_list);     //MC_TOKEN_LIST
  m_commands.push_back(NULL);            //MC_TOKEN_RUN
  m_commands.push_back(&m_cmd_open);     //MC_TOKEN_OPEN
  m_commands.push_back(&m_cmd_close);    //MC_TOKEN_CLOSE
  m_commands.push_back(&m_cmd_leave);    //MC_TOKEN_LEAVE
  m_commands.push_back(&m_cmd_quit);     //MC_TOKEN_QUIT
  m_commands.push_back(NULL);            //MC_TOKEN_HELP
  m_commands.push_back(&m_cmd_get);      //MC_TOKEN_GET
  m_commands.push_back(&m_cmd_put);      //MC_TOKEN_PUT
  m_commands.push_back(&m_cmd_post);     //MC_TOKEN_POST
  m_commands.push_back(&m_cmd_delete);   //MC_TOKEN_DELETE
  m_commands.push_back(NULL);            //MC_TOKEN_HEADER
  m_commands.push_back(&m_cmd_verbose);  //MC_TOKEN_VERBOSE
  m_commands.push_back(&m_cmd_follow);   //MC_TOKEN_FOLLOW
  m_commands.push_back(NULL);            //MC_TOKEN_FORM
  m_commands.push_back(&m_cmd_add);      //MC_TOKEN_ADD
  m_commands.push_back(&m_cmd_rm);       //MC_TOKEN_RM
}

mcLanguageState mcLanguage::run(string path) {
  mcLanguageState state;
  FILE* fd = fopen(path.c_str(), "rb");
  if (!fd) {
    cerr << strerror(errno) << endl;
    return MC_LANG_HANG;
  }
  char buffer[MC_LINE_SIZE];
  do {
    char* line = fgets(buffer, MC_LINE_SIZE, fd);
    if (!line) {
      return MC_LANG_HANG;
    } else if (!line[0] || line[0] == '\n' || line[0] == '#') {
      state = MC_LANG_CONTINUE;
    } else {
      state = parse(line);
    }
  } while (state == MC_LANG_CONTINUE);
  return state;
}

mcLanguageState mcLanguage::prompt(void) {
  mcLanguageState state;
  if (s_commands.empty()) {
    for (vector<mcCommand*>::iterator it = m_commands.begin();
         it != m_commands.end(); it++)
      if (*it) s_commands.push_back((*it)->command());
  }
  /* Tell the completer that we want a crack first. */
  rl_attempted_completion_function = mycurl_completion;
  char* line = NULL;
  do {
    if (line) {
      delete line;
      line = NULL;
    }
    string prompt = m_performer->mnymonic() + "> ";
    line = readline(prompt.c_str());
    if (!line) {
      cerr << "IO error" << endl;
      return MC_LANG_HANG;
    }
    add_history(line);
    if (!line[0] || line[0] == '\n' || line[0] == '#') {
      state = MC_LANG_CONTINUE;
    } else {
      state = parse(line);
    }
  } while (state == MC_LANG_CONTINUE);
  return state;
}

mcLanguageState mcLanguage::parse(const char* line) {
  mcScanner scanner(line);
  mcToken token = scanner.scan();
  mcLanguageState state;
  switch (token.id) {
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
    case MC_TOKEN_FOLLOW:
    case MC_TOKEN_FORM:
    case MC_TOKEN_ADD:
    case MC_TOKEN_RM:
      {
      mcCommand* cmd = m_commands[token.id];
      if (!cmd) {
        cerr << token.buffer << " is not available" << endl;
        state = MC_LANG_CONTINUE;
      } else {
        state = cmd->parse(scanner, m_performer);
      }
    } break;
    default:
      cerr << "unknown instruction " << token.buffer << endl;
      state = MC_LANG_CONTINUE;
      break;
  }
  return state;
}

mcLanguageState mcLanguage::parse_run(mcScanner& scanner) {
  mcLanguageState state;
  mcToken token;
  while (token = scanner.scan(), token.id == MC_TOKEN_STRING) {
    state = run(token.buffer);
  }
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    state = MC_LANG_ERROR;
  }
  return state;
}

mcLanguageState mcLanguage::parse_help(mcScanner& scanner) {
  mcToken token = scanner.scan();
  switch (token.id) {
    case MC_TOKEN_EOL:
      cout << "type help <command> for help on a specific command" << endl;
      cout << "Available sub commands:" << endl;
      for (vector<mcCommand*>::iterator it = m_commands.begin();
           it != m_commands.end(); it++)
        if (*it) cout << (*it)->command() << endl;
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
    case MC_TOKEN_FOLLOW:
      if (m_commands[token.id]) {
        cout <<  m_commands[token.id]->command() << " command:" << endl;
        m_commands[token.id]->help();
      }
      break;
    case MC_TOKEN_RUN:
      cout <<  "  Usage: run [file]..." << endl;
      cout <<  "    runs macro files" << endl;
      break;
    default:
      cerr << "Invalid command " << token.buffer << endl;
      break;
  }
  mcLanguageState state = MC_LANG_CONTINUE;
  token = scanner.scan();
  if (token.id != MC_TOKEN_EOL) {
    cerr << "invalid argument " << token.buffer << endl;
    state = MC_LANG_ERROR;
  }
  return state;
}

void mcLanguage::show_help(void) {
  for (vector<mcCommand*>::iterator it = m_commands.begin();
      it != m_commands.end(); it++) {
    if (*it) {
      cout <<  "  " << (*it)->command() << " command:" << endl ;
      (*it)->help();
    }
  }
}
