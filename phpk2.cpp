#include <bits/stdc++.h>

#define sp << " " <<
#define all(x)      x.begin(),x.end() 
#define PB          push_back 
#define sz(x)       (int)x.size() 
#define MP          make_pair 
#define X           first 
#define Y           second 
#define vi          vector<int> 
  
#define _xx(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _xx(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)
#define LOCAL
using namespace std;

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

void print() {
  cout << '\n';
}

template<typename T, typename... Types>
void print(T firstArg, Types... args) {
  cout << firstArg << " ";
  print(args...);
}

template <typename T>
void printcoll (T const& coll) {
    typename T::const_iterator pos;  // iterator to iterate over coll
    typename T::const_iterator end(coll.end());  // end position

    for (pos=coll.begin(); pos!=end; ++pos) {
        cout << *pos << ' ';
    }
    cout << '\n';
}

void printhc(string rl) {
  stringstream ss;
  int indx{1};
  rep(k, rl.length()-1) {
    if (rl[k+1]==rl[k]) indx++;
    else {
      if (indx>1) {ss << indx << rl[k] << '-'; indx=1;}
      else ss << rl[k] << '-';
    }
    
  }
  if (indx>1) ss << indx << rl.back();
  else ss << rl.back();
  string rlo = ss.str();
  print(rlo);
}

int mod1(int n, int m) {
  int a = n%m;
  if (a==0) a=m;
  return a;
}

void solve() {
  int A,BS,x;
  printf("Calculating a perfect herringbone pineapple knot\n");
  printf("Nests? ");
  scanf("%d",&A);
  printf("Width? ");
  scanf("%d",&x);
  printf("Bights? ");
  scanf("%d",&BS);
  int P, B, k, l[A], r[A];
  int i,ii, j, IL[BS*A],IR[BS*A],CROSSL[A], CROSSR[A], nestincr;
  int HCPL[BS][A], HCPR[BS][A];
  int cycle, lhc, rhc, row, col, startrow, pin;
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
  int y = A+1;
  k=mod1((x-y-2)/2,A);
  //Determine first string run, nest-index numbers and crossings
  l[0]=1;r[0]=k;
  IL[0]=0;IR[0]=0;
  int delta = y%A;
  for (i=1;i<A;i++) {
    l[i]=mod1(l[i-1]+delta,A);//+delta
    r[i]=mod1(r[i-1]+A-delta,A);//-delta
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
  string rl{""};
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
    rl = "";
    //Traverse HCPL to compose rl
    for (i=0, row=startrow, col=0;i<CROSSL[lhc];i++,row=(startrow+i/A)%BS, col=(col+1)%A)
      if (1 <  HCPL[row][col] && (2*cycle-1) >= HCPL[row][col]) {// condition for intersection
	if (i < lhc+1) rl.append(1,'u');//lhc u's
	if (i >= lhc+1 && i < CROSSL[lhc]-rhc-1) rl.append(1,((i-lhc-1)/A)%2 == 0?'o':'u');
	if (i >= CROSSL[lhc]-rhc-1) rl.append(1,'u');//rhc u's
      }
    printf("%2d.\t%d\t%d --> %d:\t",2*cycle-1,pin,l[(cycle-1)%A],r[(cycle-1)%A]);
    printhc(rl);

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
    rl = "";//pointer to rl
    //Traverse HCPR to compose rl
    for (i=0, row=startrow, col=0;i<CROSSR[rhc];i++,row=(startrow+i/A)%BS, col=(col+1)%A)
      if (1 < HCPR[row][col] && 2*cycle >= HCPR[row][col]) {// condition for intersection
	if (i < rhc) rl.append(1,'u');//rhc-1 u's
	if (i >= rhc && i < CROSSR[rhc]-lhc) rl.append(1,((i-rhc)/A)%2 == 0?'o':'u');
	if (i >= CROSSR[rhc]-lhc) rl.append(1,'u');//lhc-1 u's
      }
    printf("%2d.\t%d\t%d <-- %d:\t",2*cycle,pin,l[(cycle)%A],r[(cycle-1)%A]);
    printhc(rl);
  }
}

int main() {
  // #undef LOCAL
  #ifdef LOCAL
  freopen("phpk.in", "r", stdin);
  #endif
  clock_t beg = clock();
  solve();
  clock_t end = clock();
  fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
  return 0;
}
  
