#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void koniec(void){
    printf("\nKoniec procesu!\n\n");
}

// Obsługa błędu funkcji getpgid()
pid_t getpgid_check(){
    pid_t processg_id = getpgid(0);
    if(processg_id == -1){
        perror("getpgid error");
        exit(EXIT_FAILURE);
    }
    else return processg_id;
}

int main(int argc,char *argv[]) {

    // Rejestracja funkcji wywołanych przez exit()
    if(atexit(koniec) != 0){
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
    
    // Zmienne do przechowania identyfikatorów
    pid_t parent_id;

    // Pobranie id rodzica
    parent_id = getpid();

    printf("Proces macierzysty:\n");
    printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n\n", getuid(), getgid(), getpid(), getppid(), getpgid_check());
    printf("Procesy potomne:\n");
    for(int i=0; i<3; i++){
        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            if(setpgid(0, 0) == -1){
                perror("setpgid error");
                exit(1);
            }
            printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgid_check());
            break;
        default:
            wait(NULL);
            break;
        }
    }

    // Zamykanie procesu macierzystego
    if(parent_id == getpid()){
        return 0;
    }

    // Zamykanie procesów potomnych
    _exit(0);
    
}