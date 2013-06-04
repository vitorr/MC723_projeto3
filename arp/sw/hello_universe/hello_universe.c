#include <stdio.h>
#define LOCK_ADDR (8*1024*1024)

int main(int argc, char *argv[]){
  int i;
  volatile int * l = (int *) LOCK_ADDR;
  int l_value;

  //Gets the lock.
  do {
    l_value = *l; 
  } while (l_value != 0);
  printf("Hello universe!\n");
  *l = l_value; 

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

