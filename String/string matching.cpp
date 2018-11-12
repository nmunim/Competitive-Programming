#include <bits/stdc++.h>
using namespace std;

// kmp
// pi[i]=x means match length x+1
int pi[100009];

int prefixfunction(string p)
{
    int now;
    pi[0]=now=-1;
    int len=p.size();
    for(int i=1;i<len;i++)
    {
        while(now!=-1 && p[now+1]!=p[i])now=pi[now];
        if(p[now+1]==p[i])pi[i]=++now;
        else pi[i]=now=-1;
    }
}

int kmp(string t,string p)
{
    int now;
    now=-1;
    int n=t.size();
    int m=p.size();
    for(int i=0;i<n;i++)
    {
        while(now!=-1 && p[now+1]!=t[i])now=pi[now];
        if(p[now+1]==t[i])++now;
        else now=-1;
        if(now==m)return 1;
    }
    return 0;
}

// z algo
// z[i]=x means match length x
int z[100010];

void zfunction(string s)
{
    int n = s.size();
    int L, R, k;
    L = R = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i > R)
        {
            L = R = i;
            while (R<n && s[R-L] == s[R])
                R++;
            z[i] = R-L;
            R--;
        }
        else
        {
            k = i-L;
            if (z[k] < R-i+1)
                 z[i] = z[k];
            else
            {
                L = i;
                while (R<n && s[R-L] == s[R])
                    R++;
                z[i] = R-L;
                R--;
            }
        }
    }
}


// Lexicographically minimum rotation of a sequence
//
// Given a sequence s of length N, min_rotation(s, N) returns the start index
// of the lexicographically minimum rotation.
//
// Note: array s must be of length of at least 2 * N.
//
// Time complexity: O(N)



int min_rotation(int *s, int N) {
  for(int i=0;i<N;i++) s[N+i] = s[i];

  int a = 0;
  for(int b=0;b<N;b++) for(int i=0;i<N;i++) {
    if (a+i == b || s[a+i] < s[b+i]) { b += max(0, i-1); break; }
    if (s[a+i] > s[b+i]) { a = b; break; }
  }
  return a;
}


int main()
{
    string s;
    cin>>s;
    prefixfunction(s);
    for(int i=0;i<s.size();i++)cout<<pi[i]<<" ";
    cout<<endl;
    zfunction(s);
    for(int i=0;i<s.size();i++)cout<<z[i]<<" ";
}
