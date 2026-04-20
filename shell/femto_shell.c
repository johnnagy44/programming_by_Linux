#include <stdio.h>
#include<string.h>
#define MAX_INPUT 20000
int femtoshell_main(int argc, char *argv[])
{
    // Write your code here
    // Do not write a main() function. Instead, deal with femtoshell_main() as the main function of your program.
    char buf[MAX_INPUT];
    int status = 0;
    while (1) {

	printf("Femto shell prompt > ");
	if (!fgets(buf, 20000, stdin)) {
	    break;
	}
	if (buf[0] == '\n')
	    continue;
	buf[strlen(buf) - 1] = '\0';

	if (!strncmp(buf, "echo ", 5)) {
	    status = 0;
	    printf("%s\n", buf + 5);
	}

	else if (!strncmp(buf, "exit", 4)) {
	    printf("Good Bye\n");
	    break;
	} else {
	    status = -9;
	    printf("Invalid command\n");
	}

    }
    return status;
}
