#include <stdio.h>
#include <string.h>
#include "regular.h"

int main()
{
  int p,b;
  char *code=NULL;
  size_t len=0;
  printf("Calculating a regular column coded knot\n");
  printf("Parts? ");
  scanf("%d",&p);
  printf("Bights? ");
  scanf("%d",&b);
  printf("Code (use \\ or /)? ");
  getchar();
  getline(&code,&len,stdin);
  code[strlen(code)-1]='\0';//get rid of newline
  colcod(p,b,code);
}
