#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Command_t* Parse(char* input) {
  if (!input) return NULL;

  Command_t* cmd = (Command_t*)calloc(1, sizeof(Command_t));
  if (!cmd) exit(1);

  cmd->argv = (char**)malloc(MAX_ARGS * sizeof(char*));
  if (!cmd->argv) exit(1);
  cmd->argc = 0;

  char* p = input;

  while (*p != '\0')
  {
    while (*p == ' ' || *p == '\t' || *p == '\n') p++;
    if (*p == '\0') break;

    if (*p == '<')
    {
      p++;
      while (*p == ' ' || *p == '\t') p++;
      char* start = p;
      while (*p && *p != ' ' && *p != '\t' && *p != '\n') p++;
      size_t len = p - start;
      if (len > 0) cmd->input_file = strndup(start, len);
    }
    else if (*p == '>')
    {
      p++;
      int append = 0;
      if (*p == '>') { append = 1; p++; }
      while (*p == ' ' || *p == '\t') p++;
      char* start = p;
      while (*p && *p != ' ' && *p != '\t' && *p != '\n') p++;
      size_t len = p - start;
      if (len > 0) 
      {
        cmd->output_file = strndup(start, len);
        cmd->append = append;
      }
    }
    else if (*p == '|')
    {
      p++;
      cmd->pipe_to = Parse(p);
      break;
    }
    else if (*p == '&')
    {
      p++;
      cmd->background = 1;
    }
    else
    {
      char* start = p;
      if (*p == '"')
      {
        p++;
        start = p;
        while (*p && *p != '"') p++;
        size_t len = p - start;
        if (len > 0)
        {
          cmd->argv[cmd->argc++] = strndup(start, len);
        }
        if (*p == '"') p++;
      }
      else
      {
        while (*p && *p != ' ' && *p != '\t' && *p != '\n' &&
               *p != '<' && *p != '>' && *p != '|' && *p != '&')
          p++;
        size_t len = p - start;
        if (len > 0)
        {
          cmd->argv[cmd->argc++] = strndup(start, len);
        }
      }
    }
  }

  cmd->argv[cmd->argc] = NULL;
  return cmd;
}

void FreeCommand(Command_t* cmd)
{
  if (!cmd) return;
  for (int i = 0; i < cmd->argc; i++) free(cmd->argv[i]);
  free(cmd->argv);
  free(cmd->input_file);
  free(cmd->output_file);
  if (cmd->pipe_to) FreeCommand(cmd->pipe_to);
  free(cmd);
}
