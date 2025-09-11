#include "../../header.h"

int picoshell(char **cmds[])
{
    if (!cmds)
        return 1;
    int prev_read_fd = -1;
    int pipe_fd[2];
    int pid;
    int i = 0;
    int children = 0;

    pipe_fd[0] = -1;
    pipe_fd[1] = -1;
    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(pipe_fd) == -1)
        {
            if (prev_read_fd != -1)
                close (prev_read_fd);
            return 1;
        }

        pid = fork();
        if (pid == -1)
        {
            if (prev_read_fd != -1)
                close (prev_read_fd);
            if (cmds[i + 1])
            {
                close (pipe_fd[0]);
                close (pipe_fd[1]);
            }
            return 1;
        }

        if (pid == 0)
        {
            if (prev_read_fd != -1)
            {
                dup2(prev_read_fd, STDIN_FILENO);
                close(prev_read_fd);
            }

            if (cmds[i + 1])
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
                close(pipe_fd[0]);
            }

            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }

        children++;

        if (prev_read_fd != -1)
            close(prev_read_fd);
        if (cmds[i + 1])
        {
            close(pipe_fd[1]);
            prev_read_fd = pipe_fd[0];
        }
        i++;
    }

    for (int j = 0; j < children; j++)
    {
        if (wait(NULL) == -1)
            return 1;
    }

    return 0;
}

