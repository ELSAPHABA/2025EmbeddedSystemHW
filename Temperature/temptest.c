#include "temp.h"

int main(int argc, char **argv)
{
    while(1)
    {
        printf("LOAD Temperature\n");
        temp_read();
        
        sleep(10);
    }

    return 0;
}