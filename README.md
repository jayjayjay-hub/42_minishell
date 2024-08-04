<h1 align="center">
	MINISHELL(Projects at 42tokyo)
</h1>

<p align="center">
	<b><i>Final Score 99/100</i></b><br>
</p>

# ☔️ Remaining issues
1. **Currently under revision**: Cannot `cd` back to root directory (Had this been cured, it would have been 100 points.)
   

# 💡 About the project

> This project is about creating a simple shell.
> Yes, your own little bash.
> You will learn a lot about processes and file descriptors.
> (Reference: 42Tokyo minishell project PDF)

## Overview
Minishell is a project from the 42 curriculum that involves reimplementing the core functionalities of the Unix shell, specifically Bash.
The objective is to gain a deeper understanding of how command interpreters work and to develop skills in system programming and process management.
This project provides an opportunity to delve into various aspects of shell operations, including command parsing, execution, and environment management.

## Key Features
- **Command Execution**: The shell supports the execution of built-in and external commands, allowing users to interact with the operating system.
- **Redirection and Pipes**: Implementing input/output redirection and pipelines to facilitate complex command sequences.
- **Environment Variables**: Handling environment variables and enabling users to manipulate them through built-in commands.
- **Signal Handling**: Managing signals for a smooth user experience, particularly for interrupting and terminating processes.
- **Interactive Mode**: Providing a user-friendly prompt that can execute commands in real-time.

## Objectives
- **Understanding Shell Internals**: Gain insights into how shells interpret and execute user commands.
- **System Programming**: Enhance skills in system-level programming using C, focusing on process creation and management.
- **Error Handling**: Implement robust error handling to ensure the shell operates smoothly under various conditions.
- **Modular Design**: Develop a modular codebase that can be extended with additional features and functionalities.

## Challenges
- **Command Parsing**: Accurately parsing complex command structures and handling edge cases.
- **Process Management**: Efficiently managing processes, including foreground and background execution.
- **Concurrency**: Ensuring the shell handles multiple commands and signals concurrently without issues.
- **Memory Management**: Properly managing memory allocation and deallocation to prevent leaks and ensure stability.


# 🛠️ Usage

### Requirements

- The library is written in C language and needs the **`cc` compiler**.
- use **`The GNU Readline Library`**

### Instructions

**1. Compiling the code**

To compile the [libft library](https://github.com/jayjayjay-hub/libft) and this project code, go to its path and run:

```shell
$ make
```

**2. Run**
After creating the executable file `minishell`, you must do it file.

```shell
./minishell
```

**+α. Cleaning all binary (.o) and executable files**

To clean all files generated while doing a make, go to the path and run:

```shell
$ make fclean
```
