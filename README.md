# MINISHELL

Minishell is a simple command-line interpreter that allows you to execute programs and perform various operations in a terminal environment. 

## Requirements
- C Compiler
- readline library

## Usage

```bash
# Clone this project
git clone https://github.com/laugarci/minishell

# Access
cd minishell

# Compilation
make

# To run
./minishell

# To remove objects
make clean

# To remove objects and executable
make fclean

```

## Features
Minishell has the following features:

- Displays a prompt while waiting for a new command.
- Has a functional history.
- Searches and executes the correct executable based on the PATH variable or using relative or absolute paths.
- Avoids using more than one global variable to indicate the receipt of a signal.
- Does not interpret unclosed quotes or unspecified special characters (\ and ;).
- Manages single and double quotes to prevent the interpretation of metacharacters.
- Implements redirections (<, >, <<, >>).
- Supports the use of pipes (|) to connect the output of one command to the input of the next.
- Manages environment variables ($ followed by characters) that expand to their values.
- Manages the expansion of $? to get the exit status of the last command in the pipeline.
- Handles ctrl-C, ctrl-D, and ctrl-\ similarly to bash.

### Built-ins
Minishell also implements the following built-in commands:

- echo
- cd with a relative or absolute path.
- pwd
- export
- unset 
- env 
- exit
