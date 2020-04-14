int split_command(char argv[512], char cmd_str[][512]);
int cmd_red(char cmd_str[][512], int l, int r);
int cmd_pipe(char cmd_str[][512], int l, int r);
int do_cmd(int cmd_cnt, char cmd_str[][512]);
