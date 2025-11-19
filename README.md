# Minishell

## Overview
Minishell is a small Bash-like shell implemented in C as part of the 42 curriculum.  
It supports execution of system programs, built-in commands, pipes, environment variable expansion, redirections, and basic signal handling.

## Features
- Execution of external programs via `fork` and `execve`
- Built-in commands (`cd`, `pwd`, `exit`)
- Our own Versions of specific Built-in commands (`echo`, `env`, `export`)
- Environment variable expansion (`$VAR`)
- Pipes and command chaining
- Input/output redirections (`<`, `>`, `>>`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+Z`)
- Quoting (`' '` and `" "`)

## Approach
The shell:
1. Reads user input  
2. Tokenizes and parses commands  
3. Expands environment variables  
4. Builds an execution tree  
5. Creates processes using `fork`  
6. Redirects file descriptors for pipes and I/O operations  
7. Executes `execve`  
8. Cleans up and waits for child processes  

Errors are handled gracefully and printed in a Bash-compatible format.

## Usage
Compile:
```make```

Run:
```./minishell```