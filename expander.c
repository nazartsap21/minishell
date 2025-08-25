#include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

void ExpandVariables(char** args, int arg_count)
{
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
