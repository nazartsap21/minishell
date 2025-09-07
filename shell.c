#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void start_shell(void)
{
  char*      input = NULL;
  size_t     len   = 0;
  Command_t* cmd;

  while (1) 
  {
    printf("shell> ");

    getline(&input, &len, stdin);
    
    if (strcmp(input, "exit\n") == 0)
    {
      break;
    }

    cmd = Parse(input);

    Command_t* current_cmd = cmd;
    while (current_cmd != NULL)
    {
      ExpandVariables(&current_cmd->argv, &current_cmd->argc);
      current_cmd = current_cmd->pipe_to;
    }

    if (cmd && cmd->argc > 0)
    {
      ExecuteCommand(cmd);
    }

    FreeCommand(cmd);
  }

  free(input);
}
