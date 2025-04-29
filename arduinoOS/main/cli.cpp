#include <Arduino.h>
#include "cli.h"

typedef void (*CommandFunc)();

// Command definitie
typedef struct
{
    char name[BUFSIZE];
    CommandFunc func;
} commandType;

// Stubfuncties (voor nu alleen printen)
void cmd_store() { Serial.println("Store called"); }
void cmd_retrieve() { Serial.println("Retrieve called"); }
void cmd_run() { Serial.println("Run called"); }
void cmd_help() { Serial.println("Help called"); }

// Command array
static commandType commands[] = {
    {"store", &cmd_store},
    {"retrieve", &cmd_retrieve},
    {"run", &cmd_run},
    {"help", &cmd_help}};

static int n_commands = sizeof(commands) / sizeof(commandType);

// Input buffer
static char buffer[BUFSIZE];
static byte index = 0;
static bool prompt_shown = false;

void cli_init()
{
    Serial.begin(9600);
    while (!Serial)
    {
    } // Wacht op serial connectie
}

void cli_update()
{
    if (!prompt_shown)
    {
        Serial.println("ArduinOS 1.0 ready.");
        Serial.print("> ");
        prompt_shown = true;
    }

    if (Serial.available() > 0)
    {
        char c = Serial.read();

        if (c == ' ' || c == '\n')
        {
            buffer[index] = '\0'; // Token is af
            if (index > 0)
            {
                bool matched = false;
                for (int i = 0; i < n_commands; i++)
                {
                    if (strcmp(buffer, commands[i].name) == 0)
                    {
                        commands[i].func(); // Roep juiste functie aan
                        matched = true;
                        break;
                    }
                }
                if (!matched)
                {
                    Serial.print("Onbekend commando: ");
                    Serial.println(buffer);
                    Serial.println("Beschikbare commando's:");
                    for (int i = 0; i < n_commands; i++)
                    {
                        Serial.println(commands[i].name);
                    }
                }
            }
            index = 0; // Reset buffer
            Serial.print("> ");
        }
        else if (index < BUFSIZE - 1)
        {
            buffer[index++] = c;
        }
    }
}
