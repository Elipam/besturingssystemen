#include "CLI.h"

// Create a CLI instance
CLI cli;

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  // Configure built-in LED
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the CLI
  cli.begin();
}

void loop()
{
  // Process CLI input (non-blocking)
  cli.processInput();

  // Other Arduino OS tasks run here
  // Since our CLI is non-blocking, these tasks will continue to run
  // while waiting for user input

  // Example: Blink LED without using delay()
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 1000)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    lastBlink = millis();
  }

  // Add other OS tasks here
}
