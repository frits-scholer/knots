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

string hc(string rl) {
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
  return ss.str();
}

void solve() {
  print("Calculating a column-coded knot");
  u32 p, b;
  print("parts, bights:");
  cin >> p >> b;
  if (gcd(p,b) != 1 ) {print("nr of parts and bights must be relatively prime."); return;}
  string code{""}, pattern, altcode;
  print("column pattern using u and o:");
  cin >> pattern;
  //calculate code from pattern
  while (code.length() < p-1) code += pattern;
  if (code.length() > p-1) code.erase(p-1);
  print("Parts:", p, "Bights:", b, "\nPattern", pattern, "Column coding:", code);
  vi cbs(b);
  int delta = b - (p%b);
  rep(i,b) cbs[(i*delta)%b]=i;
  cbs.resize(p); 
  if (p>b) {rep(i,b,p) cbs[i]=cbs[i%b];}
  cout << endl;
  cbs = vi(begin(cbs)+1, end(cbs));
  altcode = code;
  reverse(all(altcode));
  rep(i, altcode.length()) altcode[i] = altcode[i]=='u'?'o':'u';
  ostream_iterator<char> os(cout, " ");
  copy (all(code), os);
  print("\tL -> R");
  printcoll(cbs);
  copy (all(altcode), os);
  print("\tR -> L\n");

  string rl_even, rl_odd;
  u32 rl_width{2*p};
  rep(i, b) {
    rl_even = "";
    rep(j, p-1) if (cbs[j] <= i) rl_even.append(1, altcode[j]);
    cout << setw(2) << i*2+2 << ". " << setw(rl_width) << hc(rl_even);
    if (i==(int)b-1) {cout << endl; break;}
    rl_odd = "";
    rep(j, p-1) if (cbs[j] <= i) rl_odd.append(1, code[j]);
    cout << "\t" << setw(2) << i*2+3 << ". " << setw(rl_width) << hc(rl_odd) << endl;
  }
}

int main() {
  // #undef LOCAL
  #ifdef LOCAL
  freopen("rcc.in", "r", stdin);
  #endif
  clock_t beg = clock();
  solve();
  clock_t end = clock();
  fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
  return 0;
}
  
