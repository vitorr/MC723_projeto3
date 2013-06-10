#include <stdio.h>
#include <math.h>
#define LOCK_ADDR (8*1024*1024)
#define PSIN_ADDR (9*1024*1024)

int main(int argc, char *argv[]){
  int i;
  volatile static int proc_number = 0;
  volatile const int * l = (int *) LOCK_ADDR;
  volatile float * s = (float *) PSIN_ADDR;
  int l_value;

  //Gets the lock.
  while (*l != 0);
  proc_number++;
  printf("Hello universe! From processor %d\n", proc_number);
  *s = 3.14/6;
  printf("Sin: %f\n", *s);
  *l = 0; 

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

