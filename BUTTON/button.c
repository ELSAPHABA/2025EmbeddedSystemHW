
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

static int fd = 0;
static int msgID = 0;
static pthread_t buttonTh_id;
char buttonPath[256] = {0, };

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

int buttonInit(void)
{
    if (probeButtonPath(buttonPath) == 0)
        {
            printf("ERR?\n");
            return 0;
        }
    fd = open(buttonPath, O_RDONLY);
    msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}


int buttonExit(void)
{
    pthread_join(buttonTh_id, (void**)0);
    close(fd);
}


int probeButtonPath(char *newPath)
{
    
    int returnValue = 0;
    int number = 0;
    FILE *fp = fopen(PROBE_FILE, "rt");
    while (!feof(fp))
    {
        
        char tmpStr[2000];
        fgets(tmpStr, 2000, fp);
        if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0)
        {
            printf("YES! I found!: %s\r\n", tmpStr);
            returnValue = 1;
        }
        if (
            (returnValue == 1) &&
            (strncasecmp(tmpStr, HAVE_TO_FIND_2,
                         strlen(HAVE_TO_FIND_2)) == 0)
        )
        {
            printf("-->%s", tmpStr);
            printf("\t%c\r\n", tmpStr[strlen(tmpStr) - 3]);
            number = tmpStr[strlen(tmpStr) - 3] - '0';
            break;
        }
    }
    fclose(fp);
    if (returnValue == 1)
    {
        sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
    }

    return returnValue;
}


static void *buttonThFunc(void)
{
    BUTTON_MSG_T Data;
    Data.messageNum = 1;
    struct input_event stEvent;
    while (1)
    {
        read(fd, &stEvent, sizeof(stEvent));
        if ((stEvent.type == EV_KEY))
        {
            Data.keyInput = stEvent.code;
	        Data.pressed = stEvent.value;
            Data.type = stEvent.type;
            msgsnd(msgID, &Data, sizeof(Data) - 4, 0);
        }
    }
}