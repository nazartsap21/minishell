# MiniShell

MiniShell is a simple shell implementation written in C. It supports basic shell functionalities such as command execution, input/output redirection, piping, background execution, and variable expansion.

---

## Features

- **Command Execution**: Execute basic commands like `ls`, `rm`, `echo`, etc.
- **Input Redirection**: Use `<` to redirect input from a file.
- **Output Redirection**: Use `>` to redirect output to a file or `>>` to append output to a file.
- **Piping**: Use `|` to pipe the output of one command to another.
- **Background Execution**: Use `&` to execute commands in the background.
- **Variable Expansion**: Expand environment variables (e.g., `$HOME`) and command substitution (e.g., `$(command)`).
- **Wildcard Expansion**: Expand wildcard patterns like `*.txt` to match files in the current directory.

---

## Project Structure

```
MiniShell/
├── .github/
│   └── workflows/
│       └── c-cpp.yml       # GitHub Actions CI configuration
├── .vscode/
│   └── settings.json       # VSCode settings
├── executor.c              # Command execution logic
├── executor.h              # Header for executor.c
├── expander.c              # Variable and wildcard expansion logic
├── expander.h              # Header for expander.c
├── main.c                  # Entry point of the program
├── main.h                  # Header for main.c
├── parser.c                # Command parsing logic
├── parser.h                # Header for parser.c
├── shell.c                 # Shell loop implementation
├── shell.h                 # Header for shell.c
├── Makefile                # Build configuration
├── .gitignore              # Git ignore rules
├── MiniShell.code-workspace # VSCode workspace file
└── minishell.exe           # Compiled executable (generated after build)
```

---

## Getting Started

### Prerequisites

- **Operating System**: Linux or macOS
- **Compiler**: GCC
- **Build Tools**: `make`

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/nazartsap21/MiniShell.git
   cd MiniShell
   ```

2. Build the project using `make`:
   ```bash
   make
   ```

3. The executable `minishell.exe` will be generated in the project directory.

### Running the Shell

Run the shell using the following command:
```bash
./minishell.exe
```

---

## Usage

### Basic Commands

You can execute basic commands like:
```bash
shell> ls
shell> echo "Hello, World!"
shell> rm file.txt
```

### Input/Output Redirection

- Redirect input from a file:
  ```bash
  shell> sort < input.txt
  ```

- Redirect output to a file:
  ```bash
  shell> ls > output.txt
  ```

- Append output to a file:
  ```bash
  shell> echo "New Line" >> output.txt
  ```

### Piping

Use `|` to pipe the output of one command to another:
```bash
shell> ls | grep ".c"
```

### Background Execution

Use `&` to execute commands in the background:
```bash
shell> sleep 10 &
```

### Variable Expansion

Expand environment variables:
```bash
shell> echo $HOME
```

Expand command substitution:
```bash
shell> echo $(date)
```

### Wildcard Expansion

Expand wildcard patterns to match files:
```bash
shell> rm *.txt
```

---

## Development

### Code Style

- Follow consistent indentation and naming conventions.
- Use comments to explain complex logic.

### Build and Test

- Clean the project:
  ```bash
  make clean
  ```

- Rebuild the project:
  ```bash
  make
  ```

---

## Contributing

Contributions are welcome! If you find a bug or have a feature request, please open an issue or submit a pull request.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- This project was inspired by the need to understand shell internals and system programming in C.
- Thanks to the open-source community for providing resources and tools to make this project possible.