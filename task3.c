#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {
        // Child process
        execl("/bin/pwd", "pwd", NULL); // Print working directory
        perror("Exec failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
        printf("Goodbye\n");
    }

    return 0;
}


