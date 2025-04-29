// Initialiseer FAT en laad indien nodig van EEPROM
void fs_init();

// Voegt een bestand toe aan het EEPROM
// Argumenten: bestandsnaam, data, grootte
// Return: true als succesvol, false bij fout
bool fs_addFile(const char *name, const uint8_t *data, uint16_t size);

// Leest bestand in buffer
// Argumenten: bestandsnaam, pointer naar buffer
// Return: grootte van het bestand of -1 bij fout
int fs_readFile(const char *name, uint8_t *buffer);

// Verwijdert een bestand uit EEPROM
bool fs_deleteFile(const char *name);

// Print vrije ruimte
uint16_t fs_getFreeSpace();
