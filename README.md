# Minishell

The goal of this project was to recreate a simple shell in C with some basic features by taking bash as a reference.

## Description

### Features :

- Commands History
- Launch an executable from an absolute or relative path or by looking into the PATH environment variable.
- Handles **single quotes** and **double quotes**.
- Implements redirections :
  - `<` redirect input
  - `>` redirect output
  - `>>` redirect output in append mode
- Implements **pipes** `|` to chain multiple commands together and redirect the output of a command to the input of the following one.
- Handles **environment variables** and expand them to their values.
- Handles **$?** which expands to the exit status of the last executed command.
- Handles ctrl-C, ctrl-D and ctrl-\ which behave like in bash.
- Implements the following built-ins :
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options

### What I’ve learned : 

- I got a deeper understanding of bash and Unix systems, and learned how to create child processes using the fork system call and how to communicate between multiple processes through the use of pipes and signals.

## Installation

Build the project, by executing the Makefile in the root folder with :

```
make
```

Run the executable :

```
./minishell
```
