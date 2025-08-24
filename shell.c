#include "shell.h"
#include "parser.h"
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

    printf("Command from parser: %s\n", command ? command : "None");

    for (int i = 0; i < arg_count; i++)
    {
      printf("Argument %d from parser: %s\n", i + 1, args[i] ? args[i] : "None");
    }

    free(command);
    for (int i = 0; i < arg_count; i++)
    {
      free(args[i]);
    }
    free(args);
  }

  free(input);
}
