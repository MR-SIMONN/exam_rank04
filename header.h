# ifndef HEADER_H
# define HEADER_H

#include <string.h>
#include <libc.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

char    *get_next_line(int fd);

#endif