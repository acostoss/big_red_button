#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LID_CLOSED 21
#define BUTTON_PRESSED 22
#define LID_OPEN 23

int main(int argc, char **argv)
{
  int fd;
  int i, res, desc_size = 0;
  char buf[256];

  /* Use a udev rule to make this device */
  fd = open("/dev/hidraw0", O_RDWR|O_NONBLOCK);

  if (fd < 0) {
    perror("welp, unable to open device");
    return 1;
  }

  int prior = LID_CLOSED;
  
  int status;

  while (1) {
    memset(buf, 0x0, sizeof(buf));
    buf[0] = 0x08;
    buf[7] = 0x02;

    res = write(fd, buf, 8);
    if (res < 0) {
      perror("write");
      exit(1);
    }

    memset(buf, 0x0, sizeof(buf));
    res = read(fd, buf, 8);

    if (res >= 0) {
      if (prior == LID_CLOSED && buf[0] == LID_OPEN) {
         printf("Opened\n");
         fflush(stdout);
      } else if (prior != BUTTON_PRESSED && buf[0] == BUTTON_PRESSED) {
        printf("Pressed\n");
       	system("omxplayer -p -o hdmi -g -r /home/pi/cyberBlastControl/video/briefing5.mp4");
	system("clear");
	fflush(stdout);
      } else if (prior != LID_CLOSED && buf[0] == LID_CLOSED) {
        printf("Closed\n");
        fflush(stdout);
      }
      prior = buf[0];
    }
    usleep(20000); /* Sleep for 20ms*/
  }
}
