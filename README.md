# Minishell

### As Beautiful as a Shell

#### Summary
**Minishell** is a simple shell program developed in C, similar to Bash. The goal of this project is to create a functional shell that supports command execution, process management, and redirections, providing an in-depth understanding of processes, file descriptors, and system calls.

#### Introduction
**Minishell** provides a minimalist version of a Unix shell, allowing users to execute commands, handle environment variables, use redirections, and pipelines. This project aims to explore process creation and control, while implementing key shell features.

#### Installation
1. Clone the repository:
   ```
   git clone <repository_url>
   ```
2. Navigate to the project directory:
   ```
   cd minishell
   ```
3. Compile the project:
   ```
   make
   ```

#### Usage
Run the shell with:
```
./minishell
```
You will see a prompt waiting for commands, similar to Bash.

#### Features
- **Prompt Display**: Displays a prompt while waiting for a command.
- **History Support**: Uses the readline library to provide command history.
- **Command Execution**: Executes commands using relative or absolute paths, or searches the PATH environment variable.
- **Redirections**:
  - `<` Redirect input.
  - `>` Redirect output.
  - `<<` Here document (reads input until a given delimiter).
  - `>>` Append output redirection.
- **Pipes**: Supports the pipe (`|`) character to link commands.
- **Environment Variables**: Expands environment variables with `$` and handles `$?` for the last exit status.
- **Signal Handling**: Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` similar to Bash.
- **Built-in Commands**:
  - `echo` (with `-n` option)
  - `cd` (with relative or absolute paths)
  - `pwd` (prints working directory)
  - `export` (manages environment variables)
  - `unset` (removes environment variables)
  - `env` (prints environment variables)
  - `exit` (exits the shell)