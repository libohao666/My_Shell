#include "./include/head.h"
#include "./include/color.h"
#include "./include/get_info.h"
#include "./include/command.h"
#include "./include/cd.h"

char user_name[BUFSIZE];
char host_name[BUFSIZE];
char cur_dir[BUFSIZE];
char tmp_str[BUFSIZE];
char cmd_str[BUFSIZE][BUFSIZE];

int main() {
    //获取用户名
    get_username(user_name);
    //获取主机名
    get_hostname(host_name);
    //获取工作目录
    get_curdir(cur_dir);
    while (1) {
        printf(L_GREEN"%s"NONE"@"L_GREEN"%s"NONE":"BLUE"%s"NONE"%c", user_name, host_name, cur_dir, (strcmp(user_name, "root") ? '$' : '#'));
        fgets(tmp_str, BUFSIZE, stdin);
        int len = strlen(tmp_str);
        if (len < BUFSIZE) tmp_str[len - 1] = '\0';
        int cmd_cnt = split_command(tmp_str, cmd_str);
        if (cmd_cnt) {
            if (!strcmp(cmd_str[0], CMD_EXIT)) {
                return 0;
            }
            else if (!strcmp(cmd_str[0], CMD_CD)) {
                if (do_cd(cmd_cnt, cmd_str) < 0) {
                    printf("cd error!\n"); 
                }
                get_curdir(cur_dir);
            }
            else {
                do_cmd(cmd_cnt, cmd_str);
            }
        }
    }
    
    return 0;
}
