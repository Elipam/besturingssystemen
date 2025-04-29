#ifndef CLI_H
#define CLI_H

#include <Arduino.h>

#define BUFSIZE 12

// Command function type definition
typedef void (*CommandFunction)();

// Command structure as specified in the assignment
typedef struct
{
  char name[BUFSIZE];
  CommandFunction func;
} commandType;

class CLI
{
private:
  char currentToken[BUFSIZE];
  char buffer[BUFSIZE];    // Buffer for storing characters
  uint8_t index = 0;       // Current position in buffer
  bool tokenReady = false; // Flag to indicate if a token is ready

  // Input routine method
  bool readToken(char *tokenBuffer);

public:
  CLI();
  void begin();
  void printPrompt();
  void processInput();

  // Command functions moved to public section
  static void cmdHelp();
  static void cmdVersion();
  static void cmdStore();
  static void cmdRetrieve();
  // Add more command functions as needed

  // Method to read additional arguments for commands
  static bool readArgument(char *argBuffer);
};

#endif
