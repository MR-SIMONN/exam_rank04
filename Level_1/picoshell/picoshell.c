#include "../../header.h"

int picoshell(char **cmds[])
{
    int res = 0;
    int prev_read_fd = -1;
    int pipe_fd[2];
    pid_t pid;
    int i = 0;
    pid_t child_pids[128];
    int child_count = 0;

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(pipe_fd) == -1)
            return 1;

        pid = fork();
        if (pid == -1)
            return 1;

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

        child_pids[child_count++] = pid;

        if (prev_read_fd != -1)
            close(prev_read_fd);
        if (cmds[i + 1])
        {
            close(pipe_fd[1]);
            prev_read_fd = pipe_fd[0];
        }
        i++;
    }

    int status;
    for (int j = 0; j < child_count; j++)
    {
        if (waitpid(child_pids[j], &status, 0) == -1)
            return 1;
        else if (WIFEXITED(status) && WEXITSTATUS(status))
            res = 1;
    }

    return res;
}

int main (int ac, char **av)
{

}
