#include "../include/head.h"

int do_cd(int cmd_cnt, char cmd_str[][512]) {
    int ret = 0;
    if (cmd_cnt != 2) {
        ret = -1;
    }
    else {
        printf("cd %s\n", cmd_str[1]);
        ret = chdir(cmd_str[1]);
    }
    return ret;
}
