#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p = fork();

    if (p< 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {
        // Child process
        char *args[] = {"ls", NULL}; // Command to execute
        execvpe("ls", args, NULL);   // Execute ls command
        perror("Exec failed");
        exit(1);
    } else {
        // Parent process
        waitpid(p, NULL, 0);  // Wait for child process to complete
        printf("Goodbye by parent.");
    }

    return 0;
}
