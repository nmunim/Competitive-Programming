#include <bits/stdc++.h>
using namespace std;

/***************************************************************************************
 *     Suffix Array Implementation O(nlog n)
 *     Definition : suffix(i) => substring [i,n-1]
 *     Input : STRING (inpStr) , sigma => Character Set Size
 Output:
 sa => ith smallest suffix of the string
 rak => rak[i] indicates the position of suffix(i) in the suffix array
 height => height[i] indicates the LCP of i-1 and i th suffix
 *     LCP of suffix(i) & suffix(j) = { L = rak[i], R = rak[j] ,  min(height[L+1, R]);}
 ***************************************************************************************/


const int maxn = 5e5+5;
int wa[maxn],wb[maxn],wv[maxn],wc[maxn];
int r[maxn],sa[maxn],rak[maxn], height[maxn],dp[maxn][22],jump[maxn], SIGMA = 0 ;

int cmp(int *r,int a,int b,int l){return r[a] == r[b] && r[a+l] == r[b+l];}
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for( i=0;i<m;i++) wc[i]=0;
    for( i=0;i<n;i++) wc[x[i]=r[i]] ++;
    for( i=1;i<m;i++) wc[i] += wc[i-1];
    for( i= n-1;i>=0;i--)sa[--wc[x[i]]] = i;
    for( j= 1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++)y[p++] = i;
        for(i=0;i<n;i++)if(sa[i] >= j) y[p++] = sa[i] - j;
        for(i=0;i<n;i++)wv[i] = x[y[i]];
        for(i=0;i<m;i++) wc[i] = 0;
        for(i=0;i<n;i++) wc[wv[i]] ++;
        for(i=1;i<m;i++) wc[i] += wc[i-1];
        for(i=n-1;i>=0;i--) sa[--wc[wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]] = 0,i=1;i<n;i++) x[sa[i]]= cmp(y,sa[i-1],sa[i],j) ? p-1:p++;
    }
}
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) rak[sa[i]] = i;
    for(i=0;i<n;height[rak[i++]] = k ) {
        for(k?k--:0, j=sa[rak[i]-1] ; r[i+k] == r[j+k] ; k ++) ;
    }
}

void initRMQ(int n)
{
    for(int i= 0;i<=n;i++) dp[i][0] = height[i];
    for(int j= 1; (1<<j) <= n; j ++ ){
        for(int i = 0; i + (1<<j) - 1 <= n ; i ++ ) {
            dp[i][j] = min(dp[i][j-1] , dp[i + (1<<(j-1))][j-1]);
        }
    }
    for(int i = 1;i <= n;i ++ ) {
        int k = 0;
        while((1 << (k+1)) <= i) k++;
        jump[i] = k;
    }

}
int askRMQ(int L,int R)
{
    int k = jump[R-L+1];
    return min(dp[L][k], dp[R - (1<<k) + 1][k]);
}

void init(string s)
{
    int n=s.size();
    SIGMA=0;
    for(int i = 0; i < n; i ++) {
        r[i] = s[i]-'a' + 1;
        SIGMA = max(SIGMA, r[i]);
    }
    r[n] = 0;
    da(r,sa,n+1,SIGMA + 1); // don't forget SIGMA + 1. It will ruin you.
    calheight(r,sa,n);
    initRMQ(n);
}

int lcp(int x, int y)  // longest common prefix between suffix x and suffix y
{
    return askRMQ(min(rak[x],rak[y])+1,max(rak[x],rak[y]));
}

string s;

int main()
{
    cin>>s;
    init(s);
    while(true)
    {
        int x,y;
        cin>>x>>y;
        cout<<lcp(x,y)<<endl;
    }
}

