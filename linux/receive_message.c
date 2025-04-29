#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MESS_LEN 100

int main()
{
    // structure for message queue
    struct mesg_buffer
    {
        long mesg_type;
        char mesg_text[MESS_LEN];
    } message;

    // generate a unique key using user-selectable name and id
    key_t key = ftok("ipc", 1);

    // create a message queue if one with this key does not yet exist
    // 0666: give read/write permissions to all users
    int msgid = msgget(key, 0666 | IPC_CREAT);

    while (1)
    {
        int result = msgrcv(msgid, &message, MESS_LEN, 0, IPC_NOWAIT);

        if (result == -1)
        {
            printf("No message in queue.\n");
            sleep(1); // Wait 1 second
        }
        else if (result >= 0)
        {
            printf("Data received is: %s\n", message.mesg_text);
        }
    }
    // to destroy the message queue
    // msgctl(msgid, IPC_RMID, NULL);
    return 0;
}