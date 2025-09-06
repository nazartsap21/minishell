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

    args = GetParserArgs(&arg_count);
    ExpandVariables(&args, &arg_count);

    if (arg_count > 0)
    {
      ExecuteCommand(args[0], args, arg_count);
    }

    for (int i = 0; i < arg_count; i++)
    {
      free(args[i]);
    }
    free(args);
  }

  free(input);
}
