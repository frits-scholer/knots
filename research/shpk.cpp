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
  int k, indx;
  k=0;
  while (k<(int)rl.length()) {
    indx=1;
    k++;
    while (k<(int)rl.length() && rl[k]==rl[k-1]) indx++,k++;
    if (indx>1) ss << indx << rl[k-1] << '-';
    else ss << rl[k-1] << '-';
    
  }
  string rlo = ss.str();
  if (rlo != "") rlo.erase(rlo.length()-1);
  cout << rlo;
}

void shpkcomp(int p,int b,int A,int L,int R) {
  printf("\nA = %d L = %d R = %d\n",A,L,R);
  printf("P = %d B* = %d\n",p,b);
  //make complementary bight scheme
  vi cbs(b);
  int delta = b - (p%b);
  rep(i,b) cbs[(i*delta)%b]=i;
  cbs.resize(p); 
  if (p>b) rep(i,b,p) cbs[i]=cbs[i%b];
  //Reference cycles
  vi lset(p), rset(p);
  lset[0]=L-1;
  rset[0]=R-1;
  rep(i,1,p-1) {
   lset[i]=A-1;
   rset[i]=A-1;
  }
  lset[p-1]=R-1;
  rset[p-1]=L-1;
  //first cycle
  printf("\n%2d. ",1);
  string rl{""};
  rep(j,p)
    rep(l,lset[j])
      rl.append (1,j%2==0?'u':'o');
  printhc(rl);
  rep(i,b) {
    rl = "";
    //even half cycles
    printf("\n%2d. ",2*i+2);
    rep(j,p-1) {
      rep(l,rset[j])
	rl.append(1,j%2==0?'u':'o');
      if (i>=cbs[j+1]) rl.append(1,j%2==0?'u':'o');
    }
    rl.append(rset[p-1],'u');
    printhc(rl);
    if (i== b-1) break;
    rl = "";
    //odd half cycles
    printf("\n%2d. ",2*i+3);
    rep(j,p-1) {
      rep(l,lset[j])
	rl.append(1,j%2==0?'u':'o');
      if (i>=cbs[j+1]) rl.append(1,j%2==0?'u':'o');
    }
    rl.append(lset[p-1],'u');
    printhc(rl);
  }

  printf("\n");
}

void solve() {
  int A,B,x;
  printf("Calculating a standard herringbone pineapple knot\n");
  printf("Nests? ");
  scanf("%d",&A);
  printf("Width? ");
  scanf("%d",&x);
  printf("Bights? ");
  scanf("%d",&B);
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

int main() {
  // #undef LOCAL
  #ifdef LOCAL
  freopen("shpk.in", "r", stdin);
  #endif
  clock_t beg = clock();
  solve();
  clock_t end = clock();
  fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
  return 0;
}
  
