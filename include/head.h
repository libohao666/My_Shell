#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>

#define CMD_EXIT "exit"
#define CMD_CD "cd"
#define CMD_IN "<"
#define CMD_OUT ">"
#define CMD_PIPE "|"

#define BUFSIZE 512
