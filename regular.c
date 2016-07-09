#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
void colcod(int p, int b, const char *code)
{
  int i,j,k,delta;
  char *rl, *rlo;
  printf("Parts: %u\tBights: %u\tCode: %s\n",p,b, code);
  //make complementary bight scheme
  int *cbs = xmalloc((p<b?b:p)*sizeof(int));
  //calculate (-p)modb
  delta=b-p%b;
  printf("complementary bight scheme:\n");
  for (i=0;i<b;i++) cbs[(i*delta) % b]=i;
  if (p>b) for (i=b;i<p;i++) cbs[i]=cbs[i%b];
  for (i=0;i<p;i++) printf("%3d",cbs[i]);
  char *knotcode=xmalloc(p);
  for(j=0;j<strlen(code);j++)
    for (i=j;i<p-1;i+=strlen(code)) knotcode[i]=code[j];
  knotcode[p-1]='\0';
  //printf("%s\n",knotcode);
  printf("\n   ");
  for (i=0;i<p-1;i++) printf("%3c",knotcode[i]);
  printf("\n   ");
  for (i=0;i<p;i++) printf("%3d",cbs[p-1-i]);
  printf("\nrun list");
  rl = xmalloc(p);
  rlo = xmalloc(2*p);
  for (i=0;i<b;i++) {
    //even cycles
    printf("\n%2d. ",2*i+2);
    k=0;
    for (j=1;j<p;j++)
      if (i>=cbs[j]) 
	rl[k++]=knotcode[p-j-1]=='/'?'u':'o';
    rl[k]='\0';
    printhc(rl,rlo);
    printf("%s",rlo);
    if (i==b-1) break;
    //odd cycles
    printf("\n%2d. ",2*i+3);
    k=0;
    for (j=1;j<p;j++)
      if (i>=cbs[j])
	rl[k++]=knotcode[j-1]=='/'?'o':'u';
    rl[k]='\0';
    printhc(rl,rlo);
    printf("%s",rlo);
  }
  printf("\n");
}

void rowcod(int p, int b, const char *code) {
  int i,j,k,delta,I[b];
  char *rl, *rlo;
  printf("Parts: %u\tBights: %u\tCode: %s\n",p,b, code);
  //make complementary bight scheme
  int *cbs = xmalloc((p<b?b:p)*sizeof(int));
  //calculate (-p)modb
  delta=b-p%b;
  printf("complementary bight scheme:\n");
  for (i=0;i<b;i++) cbs[(i*delta) % b]=i;
  if (p>b) for (i=b;i<p;i++) cbs[i]=cbs[i%b];
  for (i=0;i<p;i++) printf("%3d",cbs[i]);
  char *rowcode=xmalloc(2*b+1);
  for(j=0;j<strlen(code);j++)
    for (i=j;i<2*b;i+=strlen(code)) rowcode[i]=code[j];
  rowcode[2*b]='\0';
  printf("\nrowcode: %s\n",rowcode);
  for (i=0;i<b;i++) I[i]=p*i%b;
  printf("\nrun list");
  rl = xmalloc(p);
  rlo = xmalloc(2*p);
  for (i=0;i<b;i++) {
    //even cycles
    printf("\n%2d. ",2*i+2);
    k=0;
    for (j=1;j<p;j++)
      if (i>=cbs[j]) //printf("R = %d ",(2*I[i]+j+p)%(2*b));
	rl[k++]=rowcode[(2*I[i]+j+p)%(2*b)]=='o'?'u':'o';
    rl[k]='\0';
    printhc(rl,rlo);
    printf("%s",rlo);
    if (i==b-1) break;
    //odd cycles
    printf("\n%2d. ",2*i+3);
    k=0;
    for (j=1;j<p;j++)
      if (i>=cbs[j]) //columns same as even cycles bight index = +1
	rl[k++]=rowcode[(2*I[(i+1)%b]+j)%(2*b)]=='o'?'o':'u';
    rl[k]='\0';
    printhc(rl,rlo);
    printf("%s",rlo);
  }
  printf("\n");
}
