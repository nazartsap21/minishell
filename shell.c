#include "shell.h"
#include "parser.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void start_shell(void)
{
  char *input = NULL;
  size_t len = 0;
  char* command;
  char** args;
  int arg_count;

  while (1) 
  {
    printf("shell> ");

    getline(&input, &len, stdin);
    
    if (strcmp(input, "exit\n") == 0)
    {
      break;
    }

    Parse(input);

    command = GetParserCommand();
    args = GetParserArgs(&arg_count);

    ExecuteCommand(command, args, arg_count);

    free(command);
    for (int i = 0; i < arg_count; i++)
    {
      free(args[i]);
    }
    free(args);
  }

  free(input);
}
