#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void koniec(void){
    printf("\nKoniec procesu główego!\n\n");
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

    // Zbudowanie tablicy argumentów dla execv
    char* arg_list[] = {argv[1], NULL};

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
            execv(argv[1], arg_list);
            perror("execv error");
            _exit(1);
        default:
            wait(NULL);
            break;
        }
    }

    return 0;
}