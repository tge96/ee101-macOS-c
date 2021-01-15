// $ gcc -c test.c
// $ gcc -c serial.c
// $ gcc -c ee101.c
// $ gcc -o mytest test.o serial.o ee101.o -l ncurses
// $ ./mytest

//#include <stdio.h>
//#include <string.h>
#include <ncurses.h>      // # add -l ncurses to linker command
#include "ee101.h"        // EE101 Embedded Firmware Debugger, www.ee101.com # add ee101.c and ee101.h files to your project
#include "serial.h"       // add serial.c and serial.h to your project

int fd;
int main(int argc, char *argv[]) {
  int i, x, ch;

  if((fd = serialOpen("/dev/cu.usbserial-FTVHYZXQ", 9600)) < 0) return 2;     // open handle to /dev/<xyz>> used for EE101 1-wire mode
  initscr(); cbreak(); noecho(); keypad(stdscr, TRUE); nodelay(stdscr, TRUE); // configure terminal using ncurses, mainly for its non-blocking getch(); implementation
  printw("Press any key to exit program...\n");

  x = 115;

  for (;;) {
    x = x + 20;
    if(x > 315 ) x = 115;
    EE101Text(GRAY,"1.14.2021");            // continuously print some debug messages to the EE101 firmware debugger
    EE101Text(BROWN,"Macbook Pro");         // ...until user presses any key, on their keyboard, via terminal window
    EE101Text(RED,"EE101 Firmware Debugger, www.ee101.com");
    EE101Text(ORANGE,"...using ");
    EE101Text(YELLOW,"...using EE101 Firmware Debugger 1-wire mode @ /dev/<xyz>>");
    EE101Text(GREEN,"...using ");
    EE101Text(BLUE,"...using ");
    EE101Text(PURPLE,"...with only standard edits to EE101 Firmware Debugger source files");

    EE101Value(GRAY, 100);
    EE101Value(BROWN, 1000);
    EE101Value(RED, 10000);
    EE101Value(ORANGE, 30000);
    EE101Value(YELLOW, x);
    EE101Value(GREEN, 60000);
    EE101Value(BLUE, x + 1000);
    EE101Value(PURPLE, 1000000);

    if((ch = getch()) != ERR) break;  // see printw("Press any key to exit program...\n"); above
  }
  serialClose(fd);                    // close handle to /dev/<xyz>
  endwin();                           // close ncurses, returning terminal to normal
  return 0;
}
