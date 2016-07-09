#include <stdlib.h>
#include <stdio.h>
#include "phpk.h"

int main(int argc, char *argv[])
{
  int A,B,x;
  if (argc < 4) {
    fprintf(stderr,"Usage: testphpk A x B (nests width bights)\n");
    exit(EXIT_FAILURE);
  }
  sscanf(argv[1],"%d",&A);
  sscanf(argv[2],"%d",&x);
  sscanf(argv[3],"%d",&B);
  phpk(A, x, B);
}

