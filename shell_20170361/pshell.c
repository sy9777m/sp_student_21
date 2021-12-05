#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
//	for(int i = 0; i < argc; i++)
//		printf("%d: %s\n", i, argv[i]);

	/* do program here */
	/* execute command with execvp */

	char* command = argv[1];
	char* argument_list[argc];
	for (int i = 0; i < argc - 1; ++i) {
		argument_list[i] = argv[i + 1];
	}
	argument_list[argc - 1] = NULL;

	printf("processing ...\n");

	pid_t pid = fork();
	int status;

	if (pid == 0) {
		status = execvp(command, argument_list);
		if (status < 0) {
			printf("execve error: No such file or directory\n");
			exit(0);
		}
	}
	else {
		wait(&status);
		printf("completed.\n");
	}

	return 0;
}

