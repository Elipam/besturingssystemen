# ArduinOS Command Line Interface

## Overview

This project implements a non-blocking command line interface (CLI) for Arduino that allows you to interact with the system while other tasks continue to run in the background.

## File Structure

- `arduinoOS.ino`: Main Arduino sketch
- `CLI.h` and `CLI.cpp`: Command Line Interface implementation

## How to Use the CLI

### Setup

1. Upload the code to your Arduino board
2. Open the Serial Monitor (or any terminal program like PuTTY)
3. Set the baud rate to 9600
4. You should see the message "ArduinOS 1.0 ready." followed by a prompt ">"

### Entering Commands

1. Type a command at the prompt
2. Press Enter to execute the command
3. For commands that require arguments, enter the argument after the command prompt appears

### Available Commands

The current implementation includes the following commands:

| Command  | Description                            | Arguments      |
| -------- | -------------------------------------- | -------------- |
| help     | Displays a list of available commands  | None           |
| version  | Displays the current OS version        | None           |
| store    | Example command that takes an argument | Value to store |
| retrieve | Example command that takes an argument | ID to retrieve |

### Adding New Commands

To add a new command:

1. Declare a new static command function in `CLI.h`:

   ```cpp
   static void cmdYourCommand();
   ```

2. Add the command to the commands array in `CLI.cpp`:

   ```cpp
   static commandType commands[] = {
       // ...existing commands...
       {"yourcommand", &CLI::cmdYourCommand},
   };
   ```

3. Implement the command function in `CLI.cpp`:
   ```cpp
   void CLI::cmdYourCommand() {
       // Your command implementation here

       // If your command needs arguments:
       if (readArgument(argBuffer)) {
           // Process argument
       }
   }
   ```

## Technical Details

### Non-Blocking Input

The CLI uses a non-blocking input routine that processes one character at a time, allowing other code to execute while waiting for user input. This is crucial for maintaining system responsiveness.

### Command Structure

Commands are organized in a struct array that maps command names to function pointers:

```cpp
typedef struct {
    char name[BUFSIZE];
    CommandFunction func;
} commandType;
```

### Function Pointers

The system uses function pointers to call the appropriate function for each command:

```cpp
typedef void (*CommandFunction)();
```

### Token Processing

1. Input is read one character at a time
2. Characters are accumulated until a space or newline is encountered
3. The resulting token is compared against the command list
4. The corresponding function is called if a match is found

### Reading Arguments

For commands that require arguments, the `readArgument` method is used to read the next token after the command.

## Example Usage

```
> help
Available commands:
  help
  version
  store
  retrieve

> version
ArduinOS version 1.0

> store 123
Storing with argument: 123

> unknown
Unknown command: unknown
Available commands:
  help
  version
  store
  retrieve
```
