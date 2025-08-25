#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void ExecuteCommand(char* command, char** args, int arg_count)
{
  if (command == NULL)
  {
    return;
  }

  pid_t pid = fork();
  if (pid < 0) 
  {
    perror("fork failed");
    return;
  }

  if (pid == 0)
  {
    execvp(command, args);
    perror("execvp failed"); // if execvp returns, it failed
    exit(1);
  }
  else 
  {
    waitpid(pid, NULL, 0);   // wait for child process to finish
  }
}
