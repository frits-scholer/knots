#include <stdio.h>
#include "shpk.h"

int main()
{
  int A,B,x;
  printf("Calculating a standard herringbone pineapple knot\n");
  printf("Nests? ");
  scanf("%d",&A);
  printf("Width? ");
  scanf("%d",&x);
  printf("Bights? ");
  scanf("%d",&B);
  shpk(A, B, x);
}
