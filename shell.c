#include "shell.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void start_shell(void)
{
  char *input = NULL;
  size_t len = 0;

  while (1) 
  {
    printf("shell> ");

    getline(&input, &len, stdin);
    
    if (strcmp(input, "exit\n") == 0)
    {
      break;
    }

    Parse(input);
  }

  free(input);
}
