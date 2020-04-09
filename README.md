# Sammmy - Norman Simple Shell

## project details
Welcome to the `Sammmy - Norman Simple Shell project!` This program is a simple shell that can be compiled and launched from the command line within any number of Linux versions. It contains the most basic features and functions found in the various shell programs.

## Quick Start

Git clone all this respository to your local directory.
`$ git clone https://github.com/samisosa20/simple_shell.git`

or

`$ git clone https://github.com/isaza00/simple_shell.git`

Compile the program.

`$ make all`

Execute the shell.

`$ ./hsh`

Note: You can also run this shell in non-interactive mode, by simply piping your desired commands into the shell executable.

## Syntax
When using this shell, the syntax for running any command follows the familiar syntax when running a command in any other shell:

`$ <command> <flags or options> <argument 1> <argument 2> ...`
In non-interactive mode:

`$ <command> | ./hsh`
### Example
Interactive mode:

`$ /bin/ls`
or

`$ ls -l`
or

`$ cat textfile`
Non-interactive mode:

`$ echo "ls -l" | ./hsh`

## FILES

Brief description of every file in this repository. Subject to change.

| **File Name**| **Description**|
| ----- | ---- |
| AUTHORS | Text file containing the contributing authors |
| README.md | This file that you are reading |
| Man_Page | Manual page for our simple shell program |
| dir_function.c | file where are execve functions with or without PATH |
| functions.c | where are multipe functions to help run code |
| malfree.c | Create and free mallocs |
| more_function.c | where are multipe functions to help run code too |
| shell.c | Primary shell source code |
| shell.h | Shell header file |

## Authors

Sammy Guttman.
Norman Isaza.