#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


// knuth optimization- problem spoj breaking strings

// a string has to be broken in m different positions.
// cost of a break is length of the string

LL dp[1002][1002];
int pos[1002][1002],n,m,arr[1002];
LL INF =1e18;

int main()
{
    while(scanf("%d %d",&n,&m)!=EOF)
    {
    for(int i=1;i<=m;i++)scanf("%d",&arr[i]);
    arr[0]=0;arr[m+1]=n;
    for(int i=0;i<=m;i++){dp[i][i+1]=0;pos[i][i+1]=i;}
    for(int j=2;j<=m+1;j++)
    {
        for(int i=0;i<=m+1-j;i++)
        {
            dp[i][i+j]=INF;
            for(int k=pos[i][i+j-1];k<=pos[i+1][i+j];k++)
            {
                if(dp[i][k]+dp[k][i+j]-arr[i]+arr[i+j]<=dp[i][i+j])
                {
                    dp[i][i+j]=dp[i][k]+dp[k][i+j]-arr[i]+arr[i+j];
                    pos[i][i+j]=k;
                }
            }
        }
    }
    printf("%lld\n",dp[0][m+1]);
    }
    return 0;
}
