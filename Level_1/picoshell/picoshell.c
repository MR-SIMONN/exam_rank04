#include "../../header.h"

int picoshell(char **cmds[])
{
    int i = 0;
    int fd[2];
    int in_fd = 0;
    pid_t pid;

    if (!cmds)
        return 1;
    while (cmds[i])
    {
        if (cmds[i + 1])
            pipe(fd);
        else
        {
            fd[0] = -1;
            fd[1] = -1;
        }

        pid = fork();
        if (pid == 0)
        {
            if (in_fd != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (fd[1] != -1)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(0);
        }
        else
        {
            if (in_fd != 0)
                close(in_fd);
            if (fd[1] != -1)
                close(fd[1]);
            in_fd = fd[0];
            i++;
        }
    }

    while (wait(NULL) > 0)
         ;
    return 0;
}