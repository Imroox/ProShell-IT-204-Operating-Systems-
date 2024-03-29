#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGUMENTS 10

// ANSI color codes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Function to implement 'mv' command
void mv_command(char **arguments) {
    if (arguments[1] == NULL || arguments[2] == NULL) {
        printf(ANSI_COLOR_RED "Usage: mv <source> <destination>\n" ANSI_COLOR_RESET);
        return;
    }
    if (rename(arguments[1], arguments[2]) == -1) {
        perror(ANSI_COLOR_RED "mv" ANSI_COLOR_RESET);
    }
}
// Function to manually reverse a string
void reverse_string(char *str) {
    int length = strlen(str);
    for (int i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void rev_command(char **arguments) {
    if (arguments[1] != NULL && strcmp(arguments[1], "-u") == 0) {
        // If the option -u is provided, perform uppercase reverse
        char input[MAX_COMMAND_LENGTH];
        printf(ANSI_COLOR_CYAN "Enter a sentence or word you want to reverse: " ANSI_COLOR_RESET);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        for (int i = 0; input[i] != '\0'; i++) {
            if (isalpha(input[i])) {
                input[i] = toupper(input[i]);
            }
        }

        reverse_string(input);
        printf(ANSI_COLOR_CYAN "Uppercase Reversed: %s\n" ANSI_COLOR_RESET, input);
    } else {
        // Perform normal reverse
        char input[MAX_COMMAND_LENGTH];
        printf(ANSI_COLOR_CYAN "Enter a sentence or word you want to reverse: " ANSI_COLOR_RESET);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        reverse_string(input);
        printf(ANSI_COLOR_CYAN "Reversed: %s\n" ANSI_COLOR_RESET, input);
    }
}

// Function to implement 'du' command
void du_command(char **arguments) {
    int p  = fork();
    if (p  == 0) {  // Child process
        // Execute du command
        execvp("du", arguments);
        // If execvp fails
        perror("du");
        exit(1);
    } else if (p > 0) {  // Parent process
        // Wait for the child process to complete
        waitpid(p, NULL, 0);
    } else {  // Error forking
        perror("fork");
    }
}
// Function to implement 'date' command
void date_command(char **arguments) {
    if (arguments[1] && strcmp(arguments[1], "-f") == 0 && arguments[2]) {
        char cmd[MAX_COMMAND_LENGTH];
        snprintf(cmd, sizeof(cmd), "date +'%s'", arguments[2]);
        system(cmd);
    } else {
        system("date");
    }
}
// Function to get machine name
void get_machine_name(char *machine_name) {
    if (gethostname(machine_name, MAX_COMMAND_LENGTH) == -1) {
        perror(ANSI_COLOR_RED "gethostname" ANSI_COLOR_RESET);
        exit(1);
    }
}

// Function to get username
void get_username(char *username) {
    if (getlogin_r(username, MAX_COMMAND_LENGTH) == -1) {
        perror(ANSI_COLOR_RED "getlogin" ANSI_COLOR_RESET);
        exit(1);
    }
}

int main() {
    char *arguments[MAX_NUM_ARGUMENTS];
    char input[MAX_COMMAND_LENGTH];
    char machine_name[MAX_COMMAND_LENGTH];
    char username[MAX_COMMAND_LENGTH];
    int status;
    while (1) {
        get_machine_name(machine_name);
        get_username(username);
        printf(ANSI_COLOR_CYAN "ProShell: " ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "%s@%s:~$ " ANSI_COLOR_RESET, machine_name, username);
        fgets(input, MAX_COMMAND_LENGTH, stdin);
        input[strlen(input) - 1] = '\0';  // Remove newline character

        // Tokenize the command string by spaces
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL && i < MAX_NUM_ARGUMENTS) {
            arguments[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        arguments[i] = NULL;  // Set the last argument to NULL for execvp

        if (strcmp(arguments[0], "exit") == 0) {
            break;
        } else if (strcmp(arguments[0], "mv") == 0) {
            mv_command(arguments);
        } else if (strcmp(arguments[0], "du")==0){
            du_command(arguments);
        } else if (strcmp(arguments[0], "date") == 0) {
            date_command(arguments);
        } else if (strcmp(arguments[0], "rev") == 0) {
            rev_command(arguments);
        } else {
            int p = fork();
            if (p == 0) {  // Child process
                 int fd_out;
                // Check if '>' is present in arguments
                for (int j = 0; arguments[j] != NULL; j++) {
                    if (strcmp(arguments[j], ">") == 0) {
                        // Redirect output to a file
                        fd_out = open(arguments[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (fd_out == -1) {
                            perror("open");
                            exit(1);
                        }
                        // Replace '>' and the filename with NULLs
                        arguments[j] = NULL;
                        arguments[j+1] = NULL;
                        // Redirect stdout to the file
                        dup2(fd_out, STDOUT_FILENO);
                        close(fd_out);
                        break;
                    }
                }
                // Execute the command
                execvp(arguments[0], arguments);
                // If execvp fails
                perror("execvp");
                exit(1);
            } else if (p > 0) {  // Parent process
                waitpid(p, &status, 0);
            } else {  // Error forking
                perror("fork");
                exit(1);
            }
        }
    }
    return 0;
}
