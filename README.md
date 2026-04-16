🐚 OkehMastah Shell

A minimal Unix-like shell implemented in C. This project demonstrates core concepts of operating systems such as process creation, command parsing, and execution.

📌 Overview

OkehMastah Shell is a lightweight command-line interpreter that supports both built-in and external commands. It is designed as a learning project to understand how traditional shells (like bash) work internally.

⚙️ Features
🔹 Command Execution
Executes standard system commands using process control system calls.
Supports commands available in the system’s PATH.
🔹 Built-in Commands
cd <directory> – Change the current working directory.
exit – Exit the shell.
gondorCallsForAid – Displays a help message describing available commands.
🔹 Input Parsing
Reads user input dynamically.
Tokenizes commands based on whitespace delimiters.
🛠️ Architecture

The shell is structured into several core components:

1. Input Handling
A custom readLine() function reads user input character-by-character.
The input buffer dynamically resizes when needed.
2. Command Parsing
Input is split into tokens using strtok.
Tokens are stored in an array of strings for further processing.
3. Command Execution
Built-in Commands
Checked first before attempting external execution.
Implemented as separate functions (e.g., cd, exit).
External Commands
Executed using:
fork() to create a child process
execvp() to run the command
waitpid() to wait for process completion
🔄 Program Flow
Display prompt
Read user input
Parse input into tokens
Determine if command is built-in
If yes → execute directly
If no → create a child process and execute
Repeat until exit is called
