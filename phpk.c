#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
void phpk(int A, int x, int BS) {
  int P, B, k, l[A], r[A];
  int i,ii, j, IL[BS*A],IR[BS*A],CROSSL[A], CROSSR[A], nestincr;
  int HCPL[BS][A], HCPR[BS][A];
  int cycle, lhc, rhc, row, col, p, startrow, pin;
  char *rl, *rlo;
  printf("A=%d x=%d B*=%d\n",A,x,BS);
  //Check and set up parameters
  if ((x+A)%2 == 0) {
    printf("A and x must be of different parity\n");
    return;
  }
  P=2*A+x-2;
  if (gcd(P,BS)>1) {
    printf(" P = %d and B* = %d must be coprime\n",P,BS);
    return;
  }
  B=A*BS;
  k=mod1((x-A-1)/2,A);
  //Determine first string run, nest-index numbers and crossings
  l[0]=1;r[0]=k;
  IL[0]=0;IR[0]=0;
  for (i=1;i<A;i++) {
    l[i]=mod1(l[i-1]+A-1,A);//+delta
    r[i]=mod1(r[i-1]+1,A);//-delta
    IL[i]=(IL[i-1]+4*A+x-l[i-1]-l[i]-2*r[i-1])%B;
    IR[i]=(IR[i-1]+4*A+x-r[i-1]-r[i]-2*l[i])%B;
  }
  for (i=0;i<A;i++) {
    CROSSL[l[i]-1]=2*A+x-1-l[i]-r[i];
    CROSSR[r[i]-1]=2*A+x-1-l[(i+1)%A]-r[i];
  }
  nestincr = 2*A*A+A*(x-2);
  for (i=0;i<A;i++)
    for (j=1,ii=i;j<BS;j++, ii+=A) {
      IL[ii+A]=(IL[ii]+nestincr)%B;
      IR[ii+A]=(IR[ii]+nestincr)%B;
    }
  //Set up half-cycle tables
  for (i=0;i<B;i++) {
    HCPL[IL[i]/A][l[i%A]-1]=2*i+1;
    HCPR[IR[i]/A][r[i%A]-1]=2*i+2;
  }
  //  printf("\n");
  //Calculate and print braiding algorithm
  rl=xmalloc(2*A+x);
  rlo=xmalloc(4*A+2*x);
  printf("hc\tpin\tbight bound.\trun list\n");
  for (cycle=1;cycle<=B;cycle++) {
    //determine position of beginning of half cycle from l to r
    for (i=0;i<BS;i++)
      for (j=0;j<A;j++)
	if (HCPL[i][j]==(2*cycle-1)) goto pl1;
  pl1:
    lhc=j;startrow=(i+1)%BS;//printf("%2d %2d\t",lhc, startrow);
    pin=i+1;
    //determine position of end of half cycle
    for (i=0;i<BS;i++)
      for (j=0;j<A;j++)
	if (HCPR[i][j]==2*cycle) goto pr1;
  pr1:
    rhc=j;
    //determine rl
    p=0;//pointer to rl
    //Traverse HCPL to compose rl
    for (i=0, row=startrow, col=0;i<CROSSL[lhc];i++,row=(startrow+i/A)%BS, col=(col+1)%A)
      if (1 <  HCPL[row][col] && (2*cycle-1) >= HCPL[row][col]) {// condition for intersection
	if (i < lhc) rl[p++]='u';//lhc u's
	if (i >= lhc && i < CROSSL[lhc]-rhc) rl[p++]=((i-lhc)/A)%2 == 0?'o':'u';
	if (i >= CROSSL[lhc]-rhc) rl[p++]='u';//rhc u's
      }
    rl[p]='\0';
    printhc(rl, rlo);
    printf("%2d.\t%d\t%d --> %d:\t%s\n",2*cycle-1,pin,l[(cycle-1)%A],r[(cycle-1)%A],rlo);

    //determine position of beginning of half cycle from r to l
    for (i=0;i<BS;i++)
      for (j=0;j<A;j++)
	if (HCPR[i][j]==(2*cycle)) goto pr2;
  pr2:
    rhc=j;startrow=(i+1)%BS;//printf("%2d %2d\t",rhc, startrow);
    pin=i+1;
    //determine position of end of half cycle
    for (i=0;i<BS;i++)
      for (j=0;j<A;j++)
	if (HCPL[i][j]==(2*cycle+1)%(2*B)) goto pl2;
  pl2:
    lhc=j;
    //determine rl
    p=0;//pointer to rl
    //Traverse HCPR to compose rl
    for (i=0, row=startrow, col=0;i<CROSSR[rhc];i++,row=(startrow+i/A)%BS, col=(col+1)%A)
      if (1 < HCPR[row][col] && 2*cycle >= HCPR[row][col]) {// condition for intersection
	if (i < rhc+1) rl[p++]='u';//rhc+1 u's
	if (i >= rhc+1 && i < CROSSR[rhc]-lhc-1) rl[p++]=((i-rhc-1)/A)%2 == 0?'o':'u';
	if (i >= CROSSR[rhc]-lhc-1) rl[p++]='u';//lhc+1 u's
      }
    rl[p]='\0';
    printhc(rl, rlo);
    printf("%2d.\t%d\t%d <-- %d:\t%s\n",2*cycle,pin,l[(cycle)%A],r[(cycle-1)%A],rlo);
  }
}
