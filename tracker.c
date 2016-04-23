#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

#define MOUSEFILE "/dev/input/trackedmouse"
#define LENGTHFILE "/var/opt/mickey/length.txt"

int main()
{
    int fd;
    FILE * lengthfile;
    struct input_event ie;
 
    char x,y;
    int length;

    length=0;

    if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
        perror("Failed to open Mouse device\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Device open OK\n");
    }

    while(read(fd, &ie, sizeof(struct input_event)))
    {
       if (ie.type == EV_ABS) {
          if (ie.code == ABS_X) {
            x=ie.value;
            length = length + abs((int)x);
          }
          if (ie.code == ABS_Y) {
            y=ie.value;
            length = length + abs((int)y);
          }
       }
       lengthfile = fopen(LENGTHFILE, "w+");
       if (lengthfile == NULL) {
          perror("Failed to write to lengthfile\n");
       }
       fprintf(lengthfile,"%d",length);
       fclose(lengthfile);
    }

return 0;
}
