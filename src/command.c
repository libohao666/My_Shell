#include "../include/head.h"

int split_command(char argv[512], char cmd_str[][512]) {
    int ret = 0;
    int i, j;
    for (i = 0, j= 0; i < strlen(argv); i++) {
        if (argv[i] != ' ') {
            cmd_str[ret][j++] = argv[i];
        }
        else {
            if (j != 0) {
                cmd_str[ret][j] = '\0';
                ret++;
                j = 0;
            }
        }
    }
    if (j != 0) {
        cmd_str[ret][j] = '\0';
        ret++;
    }
    return ret;
}

int cmd_red(char cmd_str[][512], int l, int r) {
    //if (!cmd_exit(cmd_str[l])) return -1;
    int in_cnt = 0, out_cnt = 0;
    char *file_in = NULL, *file_out = NULL;
    int ind = r;
    for (int i = l; i < r; i++) {
        if (!strcmp(cmd_str[i], CMD_IN)) {
            in_cnt++;
            if (i + 1 < r) file_in = cmd_str[i + 1];
            else return -1;
            if (ind == r) ind = i;
        }
        else if (!strcmp(cmd_str[i], CMD_OUT)) {
            out_cnt++;
            if (i + 1 < r) file_out = cmd_str[i + 1];
            else return -1;
            if (ind == r) ind = i;
        }
    }

    if (in_cnt > 1) return -1;
    if (out_cnt > 1) return -1;
    if (in_cnt == 1) {
        FILE *fp = fopen(file_in, "r");
        if (fp == NULL) {
            perror("fopen");
            return -1;
        }
        fclose(fp);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        if (in_cnt == 1) freopen(file_in, "r", stdin);
        if (out_cnt == 1) freopen(file_out, "w", stdout);
        char *tmp_cmd[512];
        for (int i = l; i < ind; i++) {
            tmp_cmd[i] = cmd_str[i];
        }
        tmp_cmd[ind] = NULL;
        execvp(tmp_cmd[l], tmp_cmd + l);
        exit(1);
    }
    else {
        wait(NULL);
    }
    return 0;
}

int cmd_pipe(char cmd_str[][512], int l, int r) {
    if (l >= r) return -1;
    int ind = -1;
    for (int i = l; i < r; i++) {
        if (!strcmp(cmd_str[i], CMD_PIPE)) {
            ind = i;
            break;
        }
    }
    if (ind == -1) return cmd_red(cmd_str, l, r);
    if (ind + 1 == r) return -1;

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exit(cmd_red(cmd_str, l, ind));
    }
    else {
        wait(NULL);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        return cmd_pipe(cmd_str, ind + 1, r);
    }
}

int do_cmd(int cmd_cnt, char cmd_str[][512]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        int fd_in = dup(STDIN_FILENO);
        int fd_out = dup(STDOUT_FILENO);
        cmd_pipe(cmd_str, 0, cmd_cnt);
        dup2(fd_in, STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        exit(1);
    }
    else {
        wait(NULL);
        return 0;
    }
}
