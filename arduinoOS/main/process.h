enum ProcessStatus
{
    READY,
    RUNNING,
    PAUSED,
    TERMINATED
};

// Struct voor 1 proces (in .cpp gedefinieerd)
typedef struct
{
    int pid;
    char name[16];
    ProcessStatus status;
    uint16_t sp;
    uint16_t pc;
    uint16_t fp;
    uint16_t loopAddr;
} Process;

// Initialiseer process table
void proc_init();

// Start nieuw proces
int proc_start(const char *name, const uint8_t *bytecode, uint16_t size);

// Pauzeer proces
bool proc_pause(int pid);

// Hervat proces
bool proc_resume(int pid);

// Beëindig proces
bool proc_terminate(int pid);

// Voer 1 instructie uit van elk actief proces
void proc_executeAll();
