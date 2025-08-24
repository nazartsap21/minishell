#include "parser.h"
#include <stdio.h>
#include <string.h>


Parser_t parser = 
{
  .args = {NULL},
  .arg_count = 0
};


void Parse(char* input)
{
  CleanParser();

  char* token = strtok(input, " \n");

  while (token != NULL)
  {
    if (*token != '\0' && parser.arg_count < MAX_ARGS)
    {
      parser.args[parser.arg_count++] = token;
    }

    token = strtok(NULL, " \n");
  }

  for (int i = 0; i < parser.arg_count; i++)
  {
    printf("Argument %d: %s\n", i + 1, parser.args[i]);
  }
}


void CleanParser(void)
{
  for (int i = 0; i < parser.arg_count; i++)
  {
    parser.args[i] = NULL;
  }
  parser.arg_count = 0;
}
