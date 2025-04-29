// Initialiseer stack van een proces
void stack_init(int pid);

// Push byte op stack
void stack_pushByte(int pid, uint8_t val);

// Pop byte van stack
uint8_t stack_popByte(int pid);

// Push INT, CHAR, FLOAT, BOOL
void stack_pushInt(int pid, int val);
void stack_pushChar(int pid, char val);
void stack_pushFloat(int pid, float val);
void stack_pushBool(int pid, bool val);

// Pop als specifiek type
int stack_popInt(int pid);
char stack_popChar(int pid);
float stack_popFloat(int pid);
bool stack_popBool(int pid);

// Pop willekeurig numeriek type en return als float
float stack_popAsFloat(int pid);
