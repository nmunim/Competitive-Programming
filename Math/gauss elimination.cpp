
#include <bits/stdc++.h>
using namespace std;

/*
   n rows/equations, m+1 columns, m variables
   calculates determinant, rank and ans[] -> value for variables
   returns {0, 1, INF} -> number of solutions
*/

const double EPS = 1e-9;
#define MAX 105
#define INF 100000000
int where[MAX], Rank;

double Det;
int gauss(double a[MAX][MAX], double ans[MAX], int n, int m)
{
   Det = 1.0, Rank = 0;
   memset(where, -1, sizeof(where));
   for(int col = 0, row = 0; col < m && row < n; ++col) {
      int sel = row;
      for(int i = row+1; i < n; ++i)
         if(fabs(a[i][col]) > fabs(a[sel][col])) sel = i;
      if(fabs(a[sel][col]) < EPS) { Det = 0.0; continue; }
      for(int j = 0; j <= m; ++j) swap(a[sel][j], a[row][j]);
      if(row != sel) Det = -Det;
      Det *= a[row][col];
      where[col] = row;

      double s = (1.0 / a[row][col]);
      for(int j = 0; j <= m; ++j) a[row][j] *= s;
      for(int i = 0; i < n; ++i) if (i != row && fabs(a[i][col]) > EPS) {
         double t = a[i][col];
         for(int j = 0; j <= m; ++j) a[i][j] -= a[row][j] * t;
      }
      ++row, ++Rank;
   }

   for(int i = 0; i < m; ++i) ans[i] = (where[i] == -1) ? 0.0 : a[where[i]][m];
   for(int i = Rank; i < n; ++i) if(fabs(a[i][m]) > EPS) return 0;
   for(int i = 0; i < m; ++i) if(where[i] == -1) return INF;
   return 1;
}

// calculates gauss modulo a prime
long long Det;
long long bigmod(long long x, long long pow, long long mod)
{
   long long ret = 1;
   while(pow > 0) {
      if(pow & 1) ret = (ret * x) % mod;
      x = (x * x) % mod;
      pow >>= 1;
   }
   return ret;
}
#define INVERSE(a, m) bigmod(a, m-2, m)
int gauss(long long a[MAX][MAX], long long ans[MAX], int n, int m, long long mod)
{
   Det = 1, Rank = 0;
   memset(where, -1, sizeof(where));
   for(int col = 0, row = 0; col < m && row < n; ++col) {
      int sel = row;
      for(int i = row+1; i < n; ++i)
         if(abs(a[i][col]) > abs(a[sel][col])) sel = i;
      if(!a[sel][col]) { Det = 0; continue; }
      for(int j = 0; j <= m; ++j) swap(a[sel][j], a[row][j]);
      if(row != sel) Det = -Det;
      Det = (Det * a[row][col]) % mod;
      where[col] = row;

      long long s = INVERSE(a[row][col], mod); // inverse of a[row][col]
      for(int j = 0; j <= m; ++j) a[row][j] = (a[row][j] * s) % mod;
      for(int i = 0; i < n; ++i) if (i != row && a[i][col] > 0) {
         long long t = a[i][col];
         for(int j = 0; j <= m; ++j) a[i][j] = (a[i][j] - (a[row][j] * t) % mod + mod) % mod;
      }
      ++row, ++Rank;
   }

   for(int i = 0; i < m; ++i) ans[i] = (where[i] == -1) ? 0 : a[where[i]][m];
   for(int i = Rank; i < n; ++i) if(a[i][m]) return 0;
   for(int i = 0; i < m; ++i) if(where[i] == -1) return INF;
   return 1;
}

// calculates 32 times faster for modulo 2
int Det; // number of variables (must be defined)
int gauss(vector < bitset<MAX> > &a, bitset<MAX> &ans, int n, int m)
{
   Det = 1, Rank = 0;
   memset(where, -1, sizeof(where));
   for(int col = 0, row = 0; col < m && row < n; ++col) {
      int sel = row;
      for(int i = row; i < n; ++i) if(a[i][col]) { sel = i; break; }
      if(!a[sel][col]) { Det = 0; continue; }
      swap(a[sel], a[row]);
      if(row != sel) Det = -Det;
      Det &= a[row][col];
      where[col] = row;

      for(int i = 0; i < n; ++i) if (i != row && a[i][col] > 0) a[i] ^= a[row];
      ++row, ++Rank;
   }

   for(int i = 0; i < m; ++i) ans[i] = (where[i] == -1) ? 0 : a[where[i]][m];
   for(int i = Rank; i < n; ++i) if(a[i][m]) return 0;
   for(int i = 0; i < m; ++i) if(where[i] == -1) return INF;
   return 1;
}
