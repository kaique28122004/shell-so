#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

int main() {

    char linha[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {

        printf("meu-shell> ");
        fflush(stdout);

        if (fgets(linha, MAX_LINE, stdin) == NULL)
            break;

        linha[strcspn(linha, "\n")] = '\0';

        if (strcmp(linha, "exit") == 0)
            break;

        int i = 0;

        args[i] = strtok(linha, " ");

        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork");
            continue;
        }

        if (pid == 0) {

            execvp(args[0], args);

            perror("Comando não encontrado");
            exit(EXIT_FAILURE);

        } else {

            wait(NULL);

        }

    }

    printf("Shell encerrado.\n");

    return 0;
}
