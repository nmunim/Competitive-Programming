LL mulMod(LL x, LL y, LL p) {
    if (y == 0) return 0;
    if (x < 1000111000111000111LL / y) return x * y % p;
    LL mid = mulMod((x+x)%p, y>>1LL, p);
    if (y & 1) return (mid + x) % p;
    else return mid;
}
LL powMod(LL x, LL k, LL m) {
    if (k == 0) return 1;
    if ((k & 1)) return mulMod(x,powMod(x, k-1, m), m);
    else return powMod(mulMod(x,x,m), k/2, m);
}
bool suspect(LL a, LL s, LL d, LL n) {
    LL x = powMod(a, d, n);
    if (x == 1) return true;
    for (int r = 0; r < s; ++r) {
        if (x == n - 1) return true;
        x = mulMod(x, x, n);
    }
    return false;
}
// {2,7,61,-1}                      is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,-1} is for n < 10^15 (at least)
bool isPrime(LL n) {
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    LL test[] = {2,3,5,7,11,13,17,19,23,-1};
    LL d = n - 1, s = 0;
    while (d % 2 == 0) ++s, d /= 2;
    for (int i = 0; test[i] < n && test[i] != -1; ++i)
        if (!suspect(test[i], s, d, n)) return false;
    return true;
}
// Killer prime: 5555555557LL (fail when not used mulMod)



LL pollard_rho(LL n, LL seed) { // always call factorize
  LL x, y;
  x = y = rand() % (n - 1) + 1;
  int head = 1, tail = 2;
  while (true) {
    x = mulMod(x, x, n);
    x = (x + seed) % n;
    if (x == y) return n;
    LL d = gcd(max(x - y, y - x), n);
    if (1 < d && d < n) return d;
    if (++head == tail) y = x, tail <<= 1;
  }
}

void factorize(LL n, vector<LL> &divisor) { // pollard-rho factorization
  if (n == 1) return;
  if (isPrime(n)) divisor.push_back(n);
  else {
    LL d = n;
    while (d >= n) d = pollard_rho(n, rand() % (n - 1) + 1);
    factorize(n / d, divisor);
    factorize(d, divisor);
  }
}

vector<LL> divisors(vector<LL> d) {
  vector<LL> ret = {1};
  sort(d.begin(), d.end());
  for (int i = 0, count = 1; i < d.size(); ++i) {
    if (i + 1 == d.size() || d[i] != d[i + 1]) {
      int c = ret.size();
      ret.resize(ret.size() * (count+1));
      LL n = 1;
      for (int j = 1; j <= count + 1; ++j) {
        for (int k = 0; k < c; ++k) {
          ret[(j-1)*c+k] = ret[k]*n;
        }
        n *= d[i];
      }
      count = 1;
    } else count += 1;
  }
  sort(ret.begin(), ret.end());
  return ret;
}


int main()
{
    LL n;
    cin>>n;
    VL v;
    factorize(n,v);
    VL v1;
    v1=divisors(v);
    REP(i,0,v1.size()-1)cout<<v1[i]<<' ';
    return 0;
}
