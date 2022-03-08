#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void koniec(void){
    printf("    Koniec procesu potomnego!\n");
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

    printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgid_check());

    return 0;
}