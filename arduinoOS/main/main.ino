#include "cli.h"

void setup()
{
    cli_init();
}

void loop()
{
    cli_update();

    // Simuleer andere processen hier
    delay(1); // (of millis()-gebaseerde scheduler)
}
