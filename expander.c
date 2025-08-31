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
          size_t cmd_len = end - (p + j + 2);
          char cmd[256];
          strncpy(cmd, p + j + 2, cmd_len);
          cmd[cmd_len] = '\0';
          FILE* fp = popen(cmd, "r");
          if (fp)
          {
            char cmd_output[512] = "";
            size_t n = fread(cmd_output, 1, sizeof(cmd_output) - 1, fp);
            cmd_output[n] = '\0';
            for (int k = n - 1; k >= 0 && (cmd_output[k] == '\n' || cmd_output[k] == '\r'); k--) {
              cmd_output[k] = '\0';
            }
            pclose(fp);
            size_t new_len = strlen(p) - (cmd_len + 3) + strlen(cmd_output);
            char* new_arg = malloc(new_len + 1);
            if (new_arg)
            {
              strncpy(new_arg, p, j);
              new_arg[j] = '\0';
              strcat(new_arg, cmd_output);
              strcat(new_arg, end + 1);
              free(args[i]);
              args[i] = new_arg;
              len = strlen(new_arg);
              p = new_arg;
              j += strlen(cmd_output) - 1;
            }
          }
        }
        else
        {
          // For now skip this case as it doesn't seem to match anything
        }
      }
      else if (p[j] == '$')
      {
        char* var_name = &p[j + 1];
        size_t var_len = 0;
        for (int k = 0; k < strlen(var_name); k++, var_len++)
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
            p = new_arg;
            j += strlen(env_var) - 1;
          }
        }
      }
    }
  }



  // if (args == NULL || arg_count <= 0)
  //   return;

  // for (int i = 0; i < arg_count; i++)
  // {
  //   if (args[i] == NULL)
  //     continue;

  //   if (args[i][0] == '$')
  //   {
  //     char* var_name = args[i] + 1;
  //     char* var_value = getenv(var_name);
  //     if (var_value)
  //     {
  //       free(args[i]);
  //       args[i] = strdup(var_value);
  //     }
  //   }
  //   else if (args[i][0] == '~')
  //   {
  //     char* home = getenv("HOME");
  //     if (home)
  //     {
  //       char* new_arg = malloc(strlen(home) + strlen(args[i]) + 1);
  //       if (new_arg)
  //       {
  //         sprintf(new_arg, "%s%s", home, args[i] + 1);
  //         free(args[i]);
  //         args[i] = new_arg;
  //       }
  //     }
  //   }
  //   else if (args[i][0] == '*')
  //   {
  //     // @todo: fix globbing
  //     glob_t glob_result;
  //     char result[1024] = "";

  //     if (glob(args[i], 0, NULL, &glob_result) == 0)
  //     {
  //       free(args[i]);
  //       for (size_t j = 0; j < glob_result.gl_pathc; j++)
  //       {
  //         sprintf(result, "%s %s", result, glob_result.gl_pathv[j]);
  //       }
  //       printf("Glob result: %s\n", result);
  //       args[i] = strdup(result);
  //     }
  //     globfree(&glob_result);
  //   }
  // }
}
