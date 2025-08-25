#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Parser_t parser = 
{
  .bitmap = 0,
  .args = {NULL},
  .arg_count = 0
};


void Parse(char* input)
{
  if (input == NULL)
    return;

  parser.arg_count = 0;
  parser.bitmap = 0;

  char* p = input;
  while (*p != '\0')
  {
    while (*p == ' ' || *p == '\t' || *p == '\n') p++;
      if (*p == '\0') break;

    char* start = p;
    char* arg = NULL;
    size_t len = 0;

    if (*p == '"')
    {
      p++;
      start = p;
      while (*p && *p != '"') p++;
      len = p - start;
      arg = (char*)malloc(len + 1);
      if (arg)
      {
        strncpy(arg, start, len);
        arg[len] = '\0';
      }
      if (*p == '"') p++;
    }
    else
    {
      start = p;
      while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '"') p++;
      len = p - start;
      arg = (char*)malloc(len + 1);
      if (arg)
      {
        strncpy(arg, start, len);
        arg[len] = '\0';
      }
    }

    if (arg && parser.arg_count < MAX_ARGS)
    {
      parser.args[parser.arg_count++] = arg;
    }
    else if (arg)
    {
      free(arg);
    }

    if (*p == '"') p++;
  }
  if (parser.arg_count < MAX_ARGS)
    parser.args[parser.arg_count] = NULL;
}


void CleanParser(void)
{
  for (int i = 0; i < parser.arg_count; i++)
  {
    parser.args[i] = NULL;
  }

  parser.args[0] = NULL;
  parser.arg_count = 0;
  parser.bitmap = 0;
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
