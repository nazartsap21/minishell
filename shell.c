#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void start_shell(void)
{
  char *input = NULL;
  size_t len = 0;
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

    current_cmd = cmd;
    if (current_cmd && current_cmd->argc > 0)
    {
      if (current_cmd->input_file == NULL && current_cmd->output_file == NULL && current_cmd->pipe_to == NULL)
      {
        ExecuteCommand(current_cmd->argv[0], current_cmd->argv, current_cmd->argc);
      }
      else
      {
        // Handle redirection and piping here (not implemented yet)
        printf("Redirection and piping not implemented yet.\n");
      }
    }

    FreeCommand(cmd);
  }

  free(input);
}
