// Initialiseer geheugentabel
void mem_init();

// Sla variabele op in geheugen
// Return: true als succesvol
bool mem_storeVariable(const char *name, const char *type, int processId, const void *data, uint16_t size);

// Haal variabele op
// Return: pointer naar data, of nullptr
void *mem_getVariable(const char *name, int processId);

// Verwijder variabele uit geheugen
bool mem_deleteVariable(const char *name, int processId);
