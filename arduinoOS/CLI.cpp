#include "CLI.h"
#include <string.h>

// Define the command array with function pointers
static commandType commands[] = {
    {"help", &CLI::cmdHelp},
    {"version", &CLI::cmdVersion},
    {"store", &CLI::cmdStore},
    {"retrieve", &CLI::cmdRetrieve},
    // Add more commands here according to Table 1 in your assignment
};

// Calculate the number of commands
static int numCommands = sizeof(commands) / sizeof(commandType);

// Static variable for arguments
static char argBuffer[BUFSIZE];
static bool argReady = false;
static uint8_t argIndex = 0;

// Command function implementations
void CLI::cmdHelp()
{
  Serial.println("Available commands:");
  for (int i = 0; i < numCommands; i++)
  {
    Serial.print("  ");
    Serial.println(commands[i].name);
  }
}

void CLI::cmdVersion()
{
  Serial.println("ArduinOS version 1.0");
}

void CLI::cmdStore()
{
  // Read additional argument
  if (readArgument(argBuffer))
  {
    Serial.print("Storing with argument: ");
    Serial.println(argBuffer);
  }
  else
  {
    Serial.println("Error: store command requires an argument");
  }
}

void CLI::cmdRetrieve()
{
  // Read additional argument
  if (readArgument(argBuffer))
  {
    Serial.print("Retrieving with argument: ");
    Serial.println(argBuffer);
  }
  else
  {
    Serial.println("Error: retrieve command requires an argument");
  }
}

// Constructor
CLI::CLI()
{
  // Initialize variables
  index = 0;
  tokenReady = false;
  buffer[0] = '\0';
}

void CLI::begin()
{
  Serial.println("ArduinOS 1.0 ready.");
  printPrompt();
}

void CLI::printPrompt()
{
  Serial.print("> ");
}

// Token reading function
bool CLI::readToken(char *tokenBuffer)
{
  // If a token was processed, reset the buffer for the next token
  if (tokenReady)
  {
    index = 0;
    tokenReady = false;
    buffer[0] = '\0';
  }

  // Check if there's any input available
  if (Serial.available() > 0)
  {
    char c = Serial.read();

    // Echo the character back to the terminal
    Serial.print(c);

    // Check if the character is a space or newline (token delimiter)
    if (c == ' ' || c == '\n')
    {
      // Terminate the current token if it has any characters
      if (index > 0)
      {
        buffer[index] = '\0';
        tokenReady = true;
      }
    }
    // Otherwise, add the character to the buffer if there's space
    else if (index < BUFSIZE - 2)
    { // Leave room for null terminator
      buffer[index] = c;
      index++;
      buffer[index] = '\0'; // Always null-terminate
    }
  }

  // If a token is ready, copy it to the provided buffer
  if (tokenReady)
  {
    strcpy(tokenBuffer, buffer);
    return true;
  }

  return false;
}

// Static method to read additional arguments
bool CLI::readArgument(char *argBuffer)
{
  // Reset static variables
  argReady = false;
  argIndex = 0;

  // Non-blocking wait for the next token
  for (int timeout = 0; timeout < 1000; timeout++)
  {
    if (Serial.available() > 0)
    {
      char c = Serial.read();

      // Echo the character back
      Serial.print(c);

      // Check for token delimiters
      if (c == '\n')
      {
        if (argIndex > 0)
        {
          argBuffer[argIndex] = '\0';
          argReady = true;
        }
        break;
      }
      // Add character to buffer
      else if (argIndex < BUFSIZE - 2 && c != ' ')
      {
        argBuffer[argIndex] = c;
        argIndex++;
        argBuffer[argIndex] = '\0';
      }
    }

    // Non-blocking delay
    delay(1);
  }

  return argReady;
}

void CLI::processInput()
{
  // Call our non-blocking input routine
  if (readToken(currentToken))
  {
    Serial.println(); // New line after command

    // Search for the command in our array
    bool commandFound = false;
    for (int i = 0; i < numCommands; i++)
    {
      if (strcmp(currentToken, commands[i].name) == 0)
      {
        // Call the command function using the function pointer
        (commands[i].func)();
        commandFound = true;
        break;
      }
    }

    // If command not found, show error and list commands
    if (!commandFound)
    {
      Serial.print("Unknown command: ");
      Serial.println(currentToken);
      cmdHelp();
    }

    // Print the prompt for the next command
    printPrompt();
  }
}
