#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


void ExecuteCommand(Command_t* cmd)
{
  int in_fd = 0;
  int pipe_fd[2];
  pid_t pid;
  Command_t* current = cmd;

  while (current)
  {
    if (current->pipe_to)
    {
      if (pipe(pipe_fd) == -1)
      {
        perror("pipe failed");
        return;
      }
    } 
    else
    {
      pipe_fd[0] = pipe_fd[1] = -1;
    }

    pid = fork();
    if (pid < 0)
    {
      perror("fork failed");
      return;
    }

    if (pid == 0)
    {
      if (in_fd != 0)
      {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
      }

      if (current->pipe_to)
      {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
      }

      if (current->input_file)
      {
        int fd = open(current->input_file, O_RDONLY);
        if (fd < 0) { perror("open input"); exit(1); }
        dup2(fd, STDIN_FILENO);
        close(fd);
      }

      if (current->output_file)
      {
        int flags = O_WRONLY | O_CREAT | (current->append ? O_APPEND : O_TRUNC);
        int fd    = open(current->output_file, flags, 0644);
        if (fd < 0) { perror("open output"); exit(1); }
        dup2(fd, STDOUT_FILENO);
        close(fd);
      }

      execvp(current->argv[0], current->argv);
      perror("execvp failed");
      exit(1);
    }
    else 
    {
      if (in_fd != 0) close(in_fd);
      if (current->pipe_to) 
      {
        close(pipe_fd[1]);
        in_fd = pipe_fd[0];
      }

      if (!current->background) 
      {
        waitpid(pid, NULL, 0);
      }
    }

    current = current->pipe_to;
  }
}
