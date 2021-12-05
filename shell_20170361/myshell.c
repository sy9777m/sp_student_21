#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<readline/readline.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int status;

    char* cmdline;
    char* opt;


    while(1) {
        cmdline = readline("$ ");
        printf("%s\n", cmdline);

        opt = strtok(cmdline, " \n"); 
        if(!strcmp(opt, "quit"))
            break;
	else {
		int i = 0;
		char* command;
		char* argument_list[256];

		for (i = 0; i < 256; ++i) argument_list[i] = NULL;

		i = 0;
		while (opt != NULL) {
			if (i == 0) {
				command = opt;
				argument_list[i] = opt;
			}
			else argument_list[i] = opt;
			opt = strtok(NULL, " \n");
			++i;
		}

		pid = fork();

		if (pid == 0) {
			status = execvp(command, argument_list);
			if (status < 0) {
				printf("execve error: No such file or directory\n");
				exit(0);
			}
		}
		else {
			wait(&status);
		}
	}

    }

    return 0;
}


