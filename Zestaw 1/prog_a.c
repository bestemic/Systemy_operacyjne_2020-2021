#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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

    printf("\nIdentyfikatory procesu:\n");
    printf("UID: %d\n", getuid());
    printf("GID: %d\n", getgid());
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("PGID: %d\n", getpgid_check());
    
    
    return 0;
}