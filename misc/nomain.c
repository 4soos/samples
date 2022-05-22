#include <stdlib.h>

void _start() {
  int ret = my_main();
  exit(ret); 
}

int my_main() {
  puts("This is a program without a main() function!");
  return 0; 
}


