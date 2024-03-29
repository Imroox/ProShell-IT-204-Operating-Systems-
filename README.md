# Operating Systems Shell Project - ProShell

## 💬 About The Project

ProShell is a project submission for the IT 204 Operating Systems Course at International Burch University. ProShell is a project that was developed by Ali Imran Alić and Adnan Ferhatović, both current students at International Burch University. ProShell consists of a few parts:
- myshell.c - Solution for 1.1, 1.2, and 1.4 tasks.
- task3.c, Task3Intermediate.c, Task3Additionally.c - Solutions for 1.3 Task
- Operating Systems Shell Project.pdf- Answers for Task 1.5 (You can also find the answers for Task 1.5 at the end of this README file 😃)

myshell.c has implementations for the following commands:
- rev 
- rev -u (Additional option for rev function which will return reversed string in uppercase letters)
- mv
- du
- date
- date -f (Additional option for date function that will return date in special format. Format is specified by user)


task3.c has implementations for the following system calls:
- fork()
- wait()
- exec()

Task3Intermediate.c has implementations for the following system calls:
- waitpid()
- execvpe()

Task3Additionally.c has an implementation for the process called forkbomb.

## 📄 Sources/Tutorials
Sources we used during our project implementation:
- https://www.geeksforgeeks.org/introduction-linux-shell-shell-scripting/ 
- https://www.linux.org/
- https://www.digitalocean.com/community/tutorials/linux-commands
- https://www.programiz.com/c-programming

## 💻 Compiling Our Program

This is an explanation of how to download and run your project locally. To run this project you need to be using Linux Operating System as it follows and uses Unix System Calls. To get a local copy and run them follow these simple example steps

### 🚀 Installation
1. Clone this repository
- git clone https://github.com/Imroox/ProShell-IT-204-Operating-Systems-.git
2. Compile myshell.c using gcc compiler
- gcc -Wall -o myshell myshell.c
3. Compile task3.c, Task3Intermediate and Task3Additionally using gcc compiler
- gcc -Wall -o task3 task3.c
- gcc -Wall -o Task3Intermediate Task3Intermediate.c
- gcc -Wall -o Task3Additionally Task3Additionally.c

4. Run using these commands:
- ./myshell for myshell.c
- ./task3 for task3.c
- ./Task3Intermediate for Task3Intermediate.c
- ./Task3Additionally for Task3Additionally.c

### © C Code Implementation
If you additionally want to see the code and implementation of the myshell.c, task3.c, Task3Intermediate. and Task3Additionally, You can use the command nano:
- nano myshell.c
- nano task3.c
- nano Task3Additionally.c
- nano Task3Intermediate.c

## 📁 List Of Project Files
- myshell.c
- task3.c
- Task3Additionally.c
- Task3Intermediate
- README.md
- Operating Systems Shell Project.pdf

## ✔️ Task 1.5 Answers
#### Question 1.5.1: What is the purpose of the fork() system call? 

- The purpose of fork() is to allow a process to create a new process, which is known as the child process, which is an identical copy of the calling process, which is known as the parent process.
The fork() system call is fundamental for multitasking and multiprocessing in Unix-like systems. It enables the creation of new processes that can execute concurrently with the parent process.

#### Question 1.5.2: When a process makes a system call and runs kernel code:  

#### A. How does the process obtain the address of the kernel instruction to jump to? 

- A. When a process makes a system call and transitions from user mode to kernel mode, it needs to obtain the address of the kernel instruction to jump to execute the appropriate kernel code. This address is typically stored in a special system register called the "system call table" or "system call vector." The system call number provided by the process is used as an index in this table to fetch the address of the corresponding kernel function.

#### B. Where is the userspace context of the process (program counter and other registers)
- B. During the transition from user mode to kernel mode, the userspace context of the process, including the program counter (PC) and other registers, is typically stored in a data structure known as the "kernel stack" or "process control block" (PCB). This data structure is maintained by the operating system for each process and contains information about the process's execution state. When the process makes a system call, the processor switches from user mode to kernel mode, and the current state of the process (including the program counter and registers) is saved onto its kernel stack. After the system call is executed, the process's state is restored from the kernel stack, and it resumes execution in user mode.

#### Question 1.5.3: Explain the following code snippet and write down the list of process state transitions that occur during the following program. You may assume that this is the only process that the CPU is executing.
 int i = 1;

while (i < 100) { i++; }

printf("%d ", i);

while (i > 0) { i--; }

printf("%d ", i);

- The program initializes the variable i to 1, then enters a loop where i is incremented until it reaches 100. After the first loop, it prints the value of i. Then, it enters another loop where i is decremented until it reaches 0, and finally, it prints the value of i again.

- List of process state transitions:

##### Start: The process starts in the "Running" state when it is scheduled by the CPU.

##### Loop 1 (Incrementing i):
While executing the first loop, the process remains in the "Running" state.

##### Print Statement (After Loop 1):
The process transitions to the "Blocked" state when it performs I/O (printing to the console).

##### Loop 2 (Decrementing i):
After printing the first value of i, the process resumes the second loop and transitions back to the "Running" state.

##### Print Statement (After Loop 2):
The process transitions to the "Blocked" state again when performing I/O for the second print statement.

##### End:
After printing the second value of i, the process completes its execution and transitions to the "Terminated" state.



##  👥 Team Members
 Ali Imran Alić - ali.imran.alic@stu.ibu.edu.ba

Adnan Ferhatović - adnan.ferhatovic@stu.ibu.edu.ba
