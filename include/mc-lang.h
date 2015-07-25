#pragma once

#include "mc-types.h"
#include "mc-scan.h"
#include "command/mc-cmd-list.h"
#include "command/mc-cmd-open.h"
#include "command/mc-cmd-close.h"
#include "command/mc-cmd-leave.h"
#include "command/mc-cmd-quit.h"
#include "command/mc-cmd-get.h"
#include "command/mc-cmd-put.h"
#include "command/mc-cmd-post.h"
#include "command/mc-cmd-delete.h"
#include "command/mc-cmd-verbose.h"
#include "command/mc-cmd-follow.h"
#include "command/mc-cmd-add.h"
#include "command/mc-cmd-rm.h"
#include <vector>

using namespace std;

class mcLanguage {
 private:
  mcIPerformer* m_performer;
  vector<mcCommand*> m_commands;
  mcCmdList m_cmd_list;
  mcCmdOpen m_cmd_open;
  mcCmdClose m_cmd_close;
  mcCmdLeave m_cmd_leave;
  mcCmdQuit m_cmd_quit;
  mcCmdGet m_cmd_get;
  mcCmdPut m_cmd_put;
  mcCmdPost m_cmd_post;
  mcCmdDelete m_cmd_delete;
  mcCmdVerbose m_cmd_verbose;
  mcCmdFollow m_cmd_follow;
  mcCmdAdd m_cmd_add;
  mcCmdRm m_cmd_rm;
  mcLanguageState parse_run(mcScanner& scanner);
  mcLanguageState parse_help(mcScanner& scanner);
  mcLanguageState parse(const char* line);

 public:
  mcLanguage(mcIPerformer* performer);
  mcLanguageState run(string path);
  mcLanguageState prompt(void);
  void show_help(void);
};
