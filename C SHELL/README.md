# Custom Shell - OS Mini Project

A modular, feature-rich interactive shell implementation in C that supports built-in commands, process management, I/O redirection, and signal handling.

## Author
**Name:** Eswar Kumar Anantha 
**Roll No:** 2023102011

## Features

### 1. Display Requirement
- Dynamic prompt format: `<username@system_name:curr_dir>`
- Shows relative path from home directory using `~`
- Automatically retrieves username and hostname (no hard-coding)

### 2. Built-in Commands

#### echo [text...]
- Displays the provided text
- Handles multiple spaces/tabs between words (collapsed to single space)
- Example: `echo hello    world` → `hello world`

#### pwd
- Prints the absolute path of the current working directory

#### cd [path]
- `cd` or `cd ~` - Navigate to home directory
- `cd ..` - Move up one directory level
- `cd -` - Go to previous directory (prints the path)
- `cd <path>` - Navigate to specified directory
- Error handling for multiple arguments

#### history
- Displays last 10 commands
- Stores up to 20 commands persistently
- Saved in `.mysh_history` file in home directory
- Doesn't store duplicate consecutive commands
- Persists across shell sessions

### 3. Process Management

#### Foreground Processes
- Execute any external command (e.g., `ls -l`, `gcc file.c`)
- Shell waits for process completion before showing prompt
- Only one foreground process runs at a time

#### Background Processes
- Run commands in background using `&` suffix
- Example: `sleep 10 &`
- Shell immediately returns to prompt
- Displays background process PID

### 4. I/O Redirection

#### Input Redirection (`<`)
- Redirect input from file
- Example: `sort < input.txt`

#### Output Redirection (`>`)
- Redirect output to file
- Example: `ls -l > output.txt`

#### Combined Redirection
- Example: `grep "pattern" < input.txt > output.txt`

### 5. Signal Handling

#### Ctrl+C (SIGINT)
- Terminates only foreground process
- Shell continues running
- Background processes unaffected

#### Ctrl+D (EOF)
- Cleanly exits the shell
- Saves history before exiting

#### Background Process Cleanup
- Automatically reaps completed background processes
- Prevents zombie processes using SIGCHLD handler

## Project Structure

```
2023102011_OSMiniProject/
├── main.c              # Main shell loop and initialization
├── shell.h             # Common definitions and global variables
│
├── display.c           # Shell prompt display
├── display.h
│
├── utils.c             # Utility functions (parsing, tokenization)
├── utils.h
│
├── builtin.c           # Built-in command dispatcher
├── builtin.h
├── echo.c              # Echo command implementation
├── pwd.c               # PWD command implementation
├── cd.c                # CD command implementation
│
├── history.c           # Command history management
├── history.h
│
├── execute.c           # Process execution (foreground/background)
├── execute.h
│
├── redirection.c       # I/O redirection handling
├── redirection.h
│
├── signals.c           # Signal handlers
├── signals.h
│
├── makefile            # Build configuration
└── README.md           # This file
```

## Modularity Design

The project is designed with **high modularity** in mind:

1. **Header Files**: Each module has its own header file with clear interface definitions
2. **Separation of Concerns**: Each .c file handles a specific functionality:
   - Display module: Prompt generation
   - Utils module: Helper functions
   - Built-in commands: Separate files for echo, pwd, cd
   - History module: Persistent command tracking
   - Execute module: Process creation and management
   - Redirection module: File descriptor manipulation
   - Signals module: Signal handling

3. **Clean Interfaces**: Functions are well-defined with clear purposes
4. **Minimal Dependencies**: Each module only includes what it needs
5. **Easy Extension**: New commands can be added by creating new files and updating builtin.c

## Compilation

### Build the shell:
```bash
make
```

### Clean build files:
```bash
make clean
```

## Usage

### Start the shell:
```bash
./mysh
```

### Example Commands:
```bash
<username@hostname:~> pwd
/home/username

<username@hostname:~> cd Documents
<username@hostname:~/Documents> pwd
/home/username/Documents

<username@hostname:~/Documents> cd -
/home/username

<username@hostname:~> echo Hello    World
Hello World

<username@hostname:~> ls -l > files.txt
<username@hostname:~> cat < files.txt
[contents of files.txt]

<username@hostname:~> sleep 5 &
[12345]

<username@hostname:~> history
pwd
cd Documents
pwd
cd -
echo Hello    World
ls -l > files.txt
cat < files.txt
sleep 5 &
history

<username@hostname:~> exit
```

## Implementation Details

### Memory Management
- Dynamic memory allocation for history entries
- Proper cleanup on exit
- No memory leaks

### Error Handling
- Uses `perror()` for system call errors
- Graceful handling of invalid commands
- Informative error messages

### Standards Compliance
- POSIX-compliant system calls
- Uses only C standard library functions
- No third-party libraries

## Testing Recommendations

1. Test all built-in commands with various arguments
2. Test foreground and background processes
3. Test I/O redirection (input, output, combined)
4. Test signal handling (Ctrl+C, Ctrl+D)
5. Test history persistence across sessions
6. Test edge cases (empty commands, invalid paths)
7. Check for memory leaks using valgrind
8. Test with long-running background processes

## Known Limitations

- Maximum input size: 4096 characters
- Maximum tokens per command: 64
- History size: 20 commands (displays last 10)


## Notes

- History file: `.mysh_history` (hidden file in home directory)
- The shell sets its initial directory as home (`~`)
- All paths are resolved relative to the shell's home directory
- Background processes run independently of the shell

## Compilation Flags

- `-Wall`: Enable all warnings
- `-Wextra`: Enable extra warnings
- `-g`: Include debugging information

## Exit

Type `exit` or press `Ctrl+D` to quit the shell gracefully.
