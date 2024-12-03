#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pid_t pid;
    int Numero1, Numero2, Somma;


    if (pipe(fd) == -1) {
        perror("Errore");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("Errore");
        return 1;
    }

    if (pid == 0) {
        // Figlio
        close(fd[0]);

        printf("Inserisci due numeri: ");
        scanf("%d", &Numero1);
        scanf("%d", &Numero2);

        Somma = Numero1 + Numero2;

        write(fd[1], &Somma, sizeof(Somma));

        close(fd[1]);
    } else {
        // Padre
        close(fd[1]);

        wait(NULL);
        read(fd[0], &Somma, sizeof(Somma));

        printf("Somma: %d\n", Somma);

        close(fd[0]);
    }

    return 0;
}