/* this example shows how to implement the simplest solution of homework 1. */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iso646.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys-types.h>
#define N 1000

int main() {
        char del[] = " ,\n";
        char *rest1 = "exit";
        char *rest2 = "close";
        printf("command: 'close' or 'exit' to leave program\n");
        while (1!=0){
                char *p;
                char *s = (char *)malloc(N*sizeof(char));// = (char *)malloc(N*sizeof(char));
                int i = 0;
                int j = 0;

                scanf("%[^\n]%*c", s);
                if ((strcmp(s, rest1) == 0) or (strcmp(s, rest2) == 0)){
                        free(s);
                        break;
                }
                const pid_t pid = fork();
                if (pid < 0)
                        printf("fatal error\n");
                if (pid){
                        int status;
                        waitpid(pid, &status, 0);
                        printf("Return code: %d\n", WEXITSTATUS(status));
                        printf("Return pid: %d\n", getpid());
                }
                else{
                        char **help1 = (char **)malloc(N*sizeof(char*));
                        int k=0;
                        for (;k<N;k++)
                                help1[k] = NULL;

//              for (i = 0; i < 10; i++)
//                      help1[i] = 0;
                        printf("String: %s", s);
                        for( p = strtok(s, del); p != NULL; p = strtok(NULL, del)) {
                                help1[j] = p;
                                j += 1;
                        }

//              char **help2 = realloc(help1, j);
                        int q;
                        q = execvp(help1[0], help1);
                        if (q == -1) {
                                printf("fatal error");
                                exit(42);
                        }
                        free(s);
                        free(help1);
                }

        }
        return 0;
}

