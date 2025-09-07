#include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <glob.h>

void ExpandVariables(char*** args_ptr, uint8_t* arg_count)
{
  char** args = *args_ptr;

  for (size_t i = 0; i < *arg_count; ++i)
  {
    char*  p   = args[i];
    size_t len = strlen(p);

    for (size_t j = 0; j < len; ++j)
    {
      if (p[j] == '$' && p[j+1] == '(')
      {
        char* end = strchr(p + j + 2, ')');
        if (end)
        {
          size_t cmd_len = end - (p + j + 2);
          char cmd[256];
          strncpy(cmd, p + j + 2, cmd_len);
          cmd[cmd_len] = '\0';

          FILE* fp     = popen(cmd, "r");
          if (fp)
          {
            char cmd_output[512] = "";
            size_t n = fread(cmd_output, 1, sizeof(cmd_output) - 1, fp);
            cmd_output[n] = '\0';
            for (size_t k = n - 1; k >= 0 && (cmd_output[k] == '\n' || cmd_output[k] == '\r'); k--) {
              cmd_output[k] = '\0';
            }
            pclose(fp);
            size_t new_len = strlen(p) - (cmd_len + 3) + strlen(cmd_output);
            char*  new_arg = malloc(new_len + 1);
            if (new_arg)
            {
              strncpy(new_arg, p, j);
              new_arg[j] = '\0';
              strcat(new_arg, cmd_output);
              strcat(new_arg, end + 1);
              free(args[i]);
              args[i] = new_arg;
              len     = strlen(new_arg);
              p       = new_arg;
              j       += strlen(cmd_output) - 1;
            }
          }
        }
      }
      else if (p[j] == '$')
      {
        char*  var_name = &p[j + 1];
        size_t var_len  = 0;
        for (size_t k = 0; k < strlen(var_name); k++, var_len++)
        {
          if (var_name[k] == ' ' || var_name[k] == '\0' || var_name[k] == '\n' || var_name[k] == '\r')
          {
            var_name[k] = '\0';
            break;
          }
        }

        if (var_len == 0) return;

        char* env_var = getenv(var_name);
        if (!env_var) return;
        size_t new_len = strlen(p) - (var_len + 1) + strlen(env_var);
        if (env_var)
        {
          char* new_arg = malloc(new_len + 1);
          if (new_arg)
          {
            strncpy(new_arg, p, j);
            new_arg[j] = '\0';
            strcat(new_arg, env_var);
            strcat(new_arg, p + j + var_len + 1);
            free(args[i]);
            args[i] = new_arg;
            len = strlen(new_arg);
            p   = new_arg;
            j   += strlen(env_var) - 1;
          }
        }
      }
      else if (p[j] == '*')
      {
        glob_t glob_result;
        if (glob(p, 0, NULL, &glob_result) == 0)
        {
          if (glob_result.gl_pathc <= 0)
            break;

          uint8_t new_arg_count = *arg_count + glob_result.gl_pathc - 1;
          char**  new_args      = malloc((new_arg_count + 1) * sizeof(char*));

          if (!new_args)
            return;

          size_t idx = 0;
          for (idx = 0; idx < i; idx++)
          {
            new_args[idx] = strdup(args[idx]);
          }

          for (size_t k = 0; k < glob_result.gl_pathc; k++, idx++)
          {
            new_args[idx] = strdup(glob_result.gl_pathv[k]);
          }

          for (size_t k = i + 1; k < *arg_count; k++, idx++)
          {
            new_args[idx] = strdup(args[k]);
          }

          new_args[new_arg_count] = NULL;

          for (size_t k = 0; k < *arg_count; k++)
          {
            free(args[k]);
          }
          free(args);

          *args_ptr  = new_args;
          args       = new_args;
          *arg_count = new_arg_count;
          i          += glob_result.gl_pathc - 1;
        }
        globfree(&glob_result);
      }
      else if (p[j] == '~' && (j == 0) && (len == 1 || p[1] == '/'))
      {
        char* home = getenv("HOME");
        if (home)
        {
          size_t new_len = strlen(p) - 1 + strlen(home);
          char*  new_arg = malloc(new_len + 1);
          if (new_arg)
          {
            strcpy(new_arg, home);
            strcat(new_arg, p + 1);
            free(args[i]);
            args[i] = new_arg;
            len     = strlen(new_arg);
            p       = new_arg;
            j       += strlen(home) - 1;
          }
        }
      }
    }
  }
}
