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

string printhc(string s) {
  stringstream ss;
  int pos = 0;
  while (s[pos] == ' ') pos++;
  char cur = s[pos];
  int cnt = 1;
  rep(i, pos+1, s.length()) {
    if (s[i] == ' ') continue;
    if (s[i] == cur) cnt++;
    else {
      if (cnt>1) ss << cnt;
      ss << cur;
      cur = s[i];
      cnt = 1;
      ss << '-';
    }
  }
  if (cnt>1) ss << cnt;
  ss << cur;
  return ss.str();
}

void solve() {
  print("Calculating a row-coded knot");
  int p, b, r;
  print("parts, bights:");
  cin >> p >> b;
  if (gcd(p,b) != 1 ) {print("nr of parts and bights must be relatively prime."); return;}
  string code;
  print("row pattern using u and o:");
  cin >> code;
  print("Parts:", p, "Bights:", b, "Row coding:", code);
  r = code.length()/2;
  int cl = code.length();
  print("repeating code:", code, "length:", cl, "repeat:", r);
  vi cbs(b);
  int delta = b - (p%b);
  rep(i,b) cbs[(i*delta)%b]=i;
  cbs.resize(p); 
  if (p>b) rep(i,b,p) cbs[i]=cbs[i%b];
  print("complementary bight scheme:");
  cbs = vi(begin(cbs)+1, end(cbs));
  printcoll(cbs);
  //set up coding
  string lr,rl;
  rep(i, p+2*r-3) {
    lr.push_back(code[i%cl]);
  }
  print("LR:\t", lr);
  string altcode = lr.substr(p);
  // print("alt code:\t", altcode);
  int rpos = lr.find(altcode);
  print("alt code found at:\t", rpos);
  altcode = lr.substr(rpos, cl);
  rep(i, altcode.length()) altcode[i] = altcode[i]=='u'?'o':'u';
  print("alt code:\t", altcode);
  rl = altcode.substr(2);
  int kmax = (p-1)/cl;
  rep(k,kmax) rl += altcode;
  rl += altcode.substr(0, p-1-kmax*cl);
  print("RL:\t", rl);
  delta = p%r;
  //set up line segments
  int w = 2*p;
  cout << setw(2) << "i" << setw(w) << "R->L" << setw(w) << "L->R" << "\n";
  rep(i, b) {
    //get position for even half-cycle in RL
    int ps = (cl-2+delta*(2*i))%cl;
    string hc = rl.substr(ps, p-1);
    rep(j, p-1) if (cbs[j]>i) hc[j] = ' ';
    cout << setw(2) << i << setw(w) << printhc(hc);
    if (i == b-1) {cout << "\n";break;}
    //get position for odd half-cycle in LR
    ps = (delta*(2*i+2))%cl;
    hc = lr.substr(ps, p-1);
    rep(j, p-1) if (cbs[j]>i) hc[j] = ' ';
    cout << setw(w) << printhc(hc);cout << "\n";
  }
}

int main() {
  // #undef LOCAL
  #ifdef LOCAL
  freopen("rrc.in", "r", stdin);
  #endif
  clock_t beg = clock();
  solve();
  clock_t end = clock();
  fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
  return 0;
}
  
