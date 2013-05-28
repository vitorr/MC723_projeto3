#include <stdio.h>

int main(int argc, char *argv[]){
  int i;

  printf("Hello universe!\n");

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

