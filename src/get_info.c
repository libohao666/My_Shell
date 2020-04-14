#include "../include/head.h"

void get_username(char *user_name) {
    struct passwd *pwd = getpwuid(getuid());
    strcpy(user_name, pwd->pw_name);
}

void get_hostname(char *host_name) {
    gethostname(host_name, BUFSIZE);
}

void get_curdir(char *result) {
	uid_t userid = getuid();
    struct passwd *pwd = getpwuid(userid);
	char *home = pwd->pw_dir;
	
	int max_directory_path = 1024;
    char *current = malloc(max_directory_path);
    getcwd(current, 1024);
    
	char *c = strstr(current, home);
    int length_home = strlen(home);
    int length_current_directory = strlen(current);

    result[0] = '~';
    result[1] = '\0';
    strcat(result, current + length_home);

	//char *ret = getcwd(cur_dir, BUFSIZE);
    //if (ret == NULL) cur_dir = NULL;
}

