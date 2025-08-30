#include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

void ExpandVariables(char** args, int arg_count)
{
  for (int i = 0; i < arg_count; ++i)
  {
    char* p = args[i];
    size_t len = strlen(p);

    for (int j = 0; j < len; ++j)
    {
      if (p[j] == '$' && p[j+1] == '(')
      {
        char* end = strchr(p + j + 2, ')');
        if (end)
        {
          size_t var_len = end - (p + j + 2);
          char var[var_len + 1];
          strncpy(var, p + j + 2, var_len);
          var[var_len] = '\0';
          char* var_value = getenv(var);
          if (var_value)
          {
            size_t new_len = strlen(p) - (var_len + 3) + strlen(var_value);
            char* new_arg = malloc(new_len + 1);
            if (new_arg)
            {
              strncpy(new_arg, p, j);
              new_arg[j] = '\0';
              strcat(new_arg, var_value);
              strcat(new_arg, end + 1);
              free(args[i]);
              args[i] = new_arg;
              len = strlen(new_arg);
              p = new_arg;
              j += strlen(var_value) - 1;
            }
          }
          else
          {
            // Variable not found, remove the $(VAR) part
            size_t new_len = strlen(p) - (var_len + 3);
            char* new_arg = malloc(new_len + 1);
            if (new_arg)
            {
              strncpy(new_arg, p, j);
              new_arg[j] = '\0';
              strcat(new_arg, end + 1);
              free(args[i]);
              args[i] = new_arg;
              len = strlen(new_arg);
              p = new_arg;
              j--;
            }
          }
        }
        else
        {

        }
      }
      else if (p[j] == '$')
      {
        
      }
    }

    
    
  }



  if (args == NULL || arg_count <= 0)
    return;

  for (int i = 0; i < arg_count; i++)
  {
    if (args[i] == NULL)
      continue;

    if (args[i][0] == '$')
    {
      char* var_name = args[i] + 1;
      char* var_value = getenv(var_name);
      if (var_value)
      {
        free(args[i]);
        args[i] = strdup(var_value);
      }
    }
    else if (args[i][0] == '~')
    {
      char* home = getenv("HOME");
      if (home)
      {
        char* new_arg = malloc(strlen(home) + strlen(args[i]) + 1);
        if (new_arg)
        {
          sprintf(new_arg, "%s%s", home, args[i] + 1);
          free(args[i]);
          args[i] = new_arg;
        }
      }
    }
    else if (args[i][0] == '*')
    {
      // @todo: fix globbing
      glob_t glob_result;
      char result[1024] = "";

      if (glob(args[i], 0, NULL, &glob_result) == 0)
      {
        free(args[i]);
        for (size_t j = 0; j < glob_result.gl_pathc; j++)
        {
          sprintf(result, "%s %s", result, glob_result.gl_pathv[j]);
        }
        printf("Glob result: %s\n", result);
        args[i] = strdup(result);
      }
      globfree(&glob_result);
    }
  }
}
