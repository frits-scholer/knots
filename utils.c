#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *xmalloc (size_t size)
{
register void *value = malloc (size);
 if (value == 0) {
    fprintf(stderr, "virtual memory exhausted");
    exit(EXIT_FAILURE);
 }
return value;
}

void printhc(const char *rl, char *rlo) {
  int k, indx;
  char s[6];
  k=0;
  *rlo='\0';
  while (k<strlen(rl)) {
    indx=1;
    k++;
    while (k<strlen(rl) && rl[k]==rl[k-1]) indx++,k++;
    if (indx>1) sprintf(s,"%d%c-",indx,rl[k-1]);
    else sprintf(s,"%c-",rl[k-1]);
    rlo = strcat(rlo,s);
  }
  if (rlo[strlen(rlo)-1]='-') rlo[strlen(rlo)-1]='\0';
}

int gcd(int m, int n) {
  if (m<=0 || n<=0) return -1;
  int r;
  do {
    r=m%n;
    if (r==0) break;
    m=n,n=r;
  } while (1);
  return n;
}

int mod1(int n, int m) {
  int a = n%m;
  if (a==0) a=m;
  return a;
}
