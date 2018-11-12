#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL MOD = 998244353LL;

LL bigmod(LL a,LL p,LL m=MOD)
{
    LL ret=1;
    while(p>0)
    {
        if(p&1)ret=(ret*a)%MOD;
        p>>=1;
        a=(a*a)%MOD;
    }
    return ret;
}

const int N=400009; //keep N double of n+m

namespace ntt{
    const int N=::N;
    const long long mod=::MOD,rt=3;
    // (mod-1, rt, mod) && mod < 1e9:
        // (5 << 25, 3, 167772161)
        // (7 << 26, 3, 469762049)
        // (119 << 23, 3, 998244353)
    // (mod-1, rt, mod) && 2^30 > mod > 1e9:
        // (479 << 21, 3, 1004535809)
        // (483 << 21, 5, 1012924417)

    // typedef long long T;  // only support long long, or you should replace all a*b with 1ll*a*b

    LL G[55],iG[55],itwo[55];

    void add(int &a,int b){a+=b;if(a>=mod)a-=mod;}

    void init(){
        int now=(mod-1)/2,len=1,irt=bigmod(rt,mod-2,mod);
        while(now%2==0){
            G[len]=bigmod(rt,now,mod);
            iG[len]=bigmod(irt,now,mod);
            itwo[len]=bigmod(1<<len,mod-2,mod);
            now>>=1;len++;
        }
    }
    void dft(LL *x,int n,int fg=1){  // fg=1 for dft, fg=-1 for inverse dft
        for(int i=(n>>1),j=1,k;j<n;++j){
            if(i<j)swap(x[i],x[j]);
            for(k=(n>>1);k&i;i^=k,k>>=1);i^=k;
        }
        for(int m=2,now=1;m<=n;m<<=1,now++){
            LL r = fg>0 ? G[now] : iG[now];
            for(int i=0,j;i<n;i+=m){
                LL tr=1,u,v;
                for(j=i;j<i+(m>>1);++j){
                    u=x[j];v=x[j+(m>>1)]*tr%mod;
                    x[j]=(u+v)%mod;
                    x[j+(m>>1)]=(u+mod-v)%mod;
                    tr=tr*r%mod;
                }
            }
        }
    }
    void brute(LL *a,LL *b,int n,int m){
        static LL c[N];
        for(int k=0,t;k<n+m-1;++k){
            t=0;
            for(int i=max(k-m+1,0);i<n && i<=k;++i){add(t,a[i]*b[k-i]%mod);
                // if(k==2&&i==1)OUT(a[i]),OUT(b[k-i]);
            }
            c[k]=t;
        }
        for(int k=0;k<n+m-1;++k)a[k]=c[k];
    }
    void mul(LL *a,LL *b,int n,int m){   // a: 0,1,2,...,n-1; b: 0,1,2,...,m-1
        // if(n+m<=200){
            // brute(a,b,n,m);
            // return;
        // }
        int nn=n+m-1;
        if(n==0||m==0){
            memset(a,0,nn*sizeof(a[0]));
            return;
        }
        int L,len;for(L=1,len=0;L<nn;++len,L<<=1);
        // OUT(nn);
        // OUT(L);OUT(len);
        if(n<L)memset(a+n,0,(L-n)*sizeof(a[0]));
        if(m<L)memset(b+m,0,(L-m)*sizeof(b[0]));
        // rep(i,0,L)TST(a[i]);puts("");
        // rep(i,0,L)TST(b[i]);puts("");
        dft(a,L,1);dft(b,L,1);
        for(int i=0;i<L;++i)a[i]=a[i]*b[i]%mod;
        dft(a,L,-1);
        for(int i=0;i<L;++i)a[i]=a[i]*itwo[len]%mod;
    }
}

LL a[N],b[N],n,m;

int main()
{
    ntt:: init();
    while(true)
    {
        ntt:: mul(a,b,n,m);
    }
    return 0;
}
