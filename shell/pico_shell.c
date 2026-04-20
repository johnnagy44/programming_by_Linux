#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>

#define MAX_INPUT_PICO 20000

char **parse(char *buf) {
    int size = 10, i = 0;
    char **args = malloc(size * sizeof(char*));

    char *token = strtok(buf, " ");
    while (token != NULL) {
        args[i++] = token;

        if (i >= size) {
            size *= 2;
            args = realloc(args, size * sizeof(char*));
        }

        token = strtok(NULL, " ");
    }

    args[i] = NULL;
    return args;
}

int main(int argc, char *argv[])
{
    char buf[MAX_INPUT_PICO];
    int status = 0;

    while (1) {
        printf("Pico shell prompt > ");

        if (!fgets(buf, MAX_INPUT_PICO, stdin))
            break;

        if (buf[0] == '\n')
            continue;

        buf[strcspn(buf, "\n")] = 0;

        char **args = parse(buf);

        if (args[0] == NULL) {
            free(args);
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            printf("Good Bye\n");
            free(args);
            break;
        }

        else if (strcmp(args[0], "echo") == 0) {
            for (int i = 1; args[i]; i++) {
                printf("%s ", args[i]);
            }
            printf("\n");
        }

        else if (strcmp(args[0], "pwd") == 0) {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)))
                printf("%s\n", cwd);
            else
                perror("pwd");
        }

        else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }

        else if (strcmp(args[0], "ls") == 0) {
            const char *dir = args[1] ? args[1] : ".";

            DIR *d = opendir(dir);
            if (!d) {
                perror("ls");
            } else {
                struct dirent *entry;
                while ((entry = readdir(d)) != NULL) {
                    if (strcmp(entry->d_name, ".") != 0 &&
                        strcmp(entry->d_name, "..") != 0) {
                        printf("%s  ", entry->d_name);
                    }
                }
                printf("\n");
                closedir(d);
            }
        }

        // ===== external commands =====
        else {
            pid_t pid = fork();

            if (pid == 0) {
                execvp(args[0], args);
                perror("exec");
                exit(1);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork");
            }
        }

        free(args);
    }

    return status;
}