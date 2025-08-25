#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Parser_t parser = 
{
  .args = {NULL},
  .arg_count = 0
};


void Parse(char* input)
{
  if (input == NULL)
    return;

  if (parser.args[0])
    CleanParser();

  char* token = strtok(input, " \n\t");

  while (token != NULL)
  {
    if (*token != '\0' && parser.arg_count < MAX_ARGS)
    {
      parser.args[parser.arg_count++] = token;
    }

    token = strtok(NULL, " \n\t");  
  }
}


void CleanParser(void)
{
  for (int i = 0; i < parser.arg_count; i++)
  {
    parser.args[i] = NULL;
  }

  parser.args[0] = NULL;
  parser.arg_count = 0;
} 


char** GetParserArgs(int* arg_count)
{
  if (arg_count == NULL)
    return NULL;

  *arg_count = parser.arg_count;
  if (parser.arg_count == 0)
    return NULL;

  char** args_copy = malloc(sizeof(char*) * (parser.arg_count + 1));
  if (!args_copy)
    return NULL;

  for (int i = 0; i < parser.arg_count; i++)
  {
    args_copy[i] = strdup(parser.args[i]);
  }

  args_copy[parser.arg_count] = NULL;

  return args_copy;
}
