#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

void shpkcomp(int, int, int, int, int);

void shpk(int A, int B, int x) {
  int k, n, r, P;
  if ((x+A)%2 != 0) {
    printf("A and x must be both even or both odd\n");
    return;
  }
  k=((x+A)/2-1)%A;
  printf("A = %d  x = %d B* = %d\n",A,x,B);
  if (k==0) {
    n=(x-2)/A;
    P=n+2;
    if (gcd(P,B) != 1) {
	  printf("gcd(%d,%d) is not 1\n",P,B);
	  return;
    }
    printf("k = %d P = %d\n",A,P);
    for (r=1;r<=A;r++) shpkcomp(P,B,r,1,r);
  }
  else {
    n=(x+A-2*k-2)/(2*A);
    P=1+2*n;//for A-k components
    if (gcd(P,B) != 1 || gcd(P+2,B) != 1 ) {
	  printf("gcd(%d,%d) is not 1 or gcd(%d,%d) is not 1\n",P,B,P+2,B);
	  return;
    }

    printf("k = %d P1 = %d P2 = %d\n",k,P,P+2);
    for  (r=1;r<=A-k;r++) shpkcomp(P,B,r,1,r);
    P=P+2;//for k components
    for  (r=1;r<=k;r++) shpkcomp(P,B,A-k+r,1,r);

  }
}

void shpkcomp(p,b,A,L,R) {

  int i, j, c, k, l, delta;
  int *lset, *rset;
  char *rl, *rlo;
  printf("\nA = %d L = %d R = %d",A,L,R);
  printf("\nP = %d B* = %d",p,b);
  //make complementary bight scheme
  int *cbs = xmalloc((p<b?b:p)*sizeof(int));
  //calculate (-p)modb
  delta=b-p%b;
  for (i=0;i<b;i++) cbs[(i*delta) % b]=i;
  if (p>b) for (i=b;i<p;i++) cbs[i]=cbs[i%b];
  //Reference cycles
  lset = xmalloc(p*sizeof(int));
  rset = xmalloc(p*sizeof(int));
  lset[0]=L-1;
  rset[0]=R-1;
  for (i=1;i<p-1;i++) {
   lset[i]=A-1;
   rset[i]=A-1;
  }
  lset[p-1]=R-1;
  rset[p-1]=L-1;
  rl = xmalloc(A*p);
  rlo = xmalloc(2*p);
  //first cycle
  printf("\n%2d. ",1);
  k=0;
  for (j=0;j<p;j++)
    for (l=0;l<lset[j];l++)
      rl[k++] = (j%2==0?'u':'o');
  rl[k]='\0';
  printhc(rl,rlo);
  printf("%s",rlo);
  for (i=0;i<b;i++) {
    //even half cycles
    printf("\n%2d. ",2*i+2);
    k=0;
    for (j=0;j<p-1;j++) {
      for (l=0;l<rset[j];l++)
	rl[k++] = (j%2==0?'u':'o');
      if (i>=cbs[j+1]) rl[k++] = (j%2==0?'u':'o');
    }
    for (l=0;l<rset[p-1];l++) rl[k++]='u';
    rl[k]='\0';
    printhc(rl,rlo);
    printf("%s",rlo);
    if (i== b-1) break;
    //odd half cycles
    printf("\n%2d. ",2*i+3);
    k=0;
    for (j=0;j<p-1;j++) {
      for (l=0;l<lset[j];l++)
	rl[k++] = (j%2==0?'u':'o');
      if (i>=cbs[j+1]) rl[k++] = (j%2==0?'u':'o');
    }
    for (l=0;l<lset[p-1];l++) rl[k++]='u';
    rl[k]='\0';
    printhc(rl,rlo);
    printf("%s",rlo);
  }

  printf("\n");
}

