#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL egcd(LL a,LL b,LL &x,LL &y)
{
    if(a==0)
    {
        x=0;y=1;
        return b;
    }
    LL x1,y1;
    LL d=egcd(b%a,a,x1,y1);
    x=y1-(b/a)*x1;
    y=x1;
    return d;
}

// no. of solution of ax+by+c=0 in range x1<=x<=x2, y1<=y<=y2

LL cnt(LL a,LL b,LL c,LL x1,LL x2,LL y1,LL y2)
{
    LL x,y;
    if(a<0)
    {
        a=-a;
        x1=-x1;
        x2=-x2;
        swap(x1,x2);
    }
    if(b<0)
    {
        b=-b;
        y1=-y1;
        y2=-y2;
        swap(y1,y2);
    }

    if(a==0 && b==0)
    {
        if(c!=0)return 0;
        return (x2-x1+1)*(y2-y1+1);
    }
    if(a==0)
    {
        if(c%b)return 0;
        y=-c/b;
        if(y<y1 || y>y2)return 0;
        return x2-x1+1;
    }
    if(b==0)
    {
        if(c%a)return 0;
        x=-c/a;
        if(x<x1 || x>x2) return 0;
        return y2-y1+1;
    }
    LL g=egcd(a,b,x,y);
    if(c%g!=0)return 0;
    x*=(-c/g);
    y*=(-c/g);
    LL tmp,xm=b/g,ym=a/g,lo,hi;

    tmp=(x1-x)/xm;
    x+=tmp*xm;
    y-=tmp*ym;
    while(x>=x1)
    {
        x-=xm;
        y+=ym;
    }
    while(x<x1)
    {
        x+=xm;
        y-=ym;
    }
    lo=x;

    tmp=(x2-x)/xm;
    x+=tmp*xm;
    y-=tmp*ym;
    while(x<=x2)
    {
        x+=xm;
        y-=ym;
    }
    while(x>x2)
    {
        x-=xm;
        y+=ym;
    }
    hi=x;

    tmp=(y1-y)/ym;
    y+=tmp*ym;
    x-=tmp*xm;
    while(y>=y1)
    {
        y-=ym;
        x+=xm;
    }
    while(y<y1)
    {
        y+=ym;
        x-=xm;
    }
    hi=min(hi,x);


    tmp=(y2-y)/ym;
    y+=tmp*ym;
    x-=tmp*xm;
    while(y<=y2)
    {
        y+=ym;
        x-=xm;
    }
    while(y>y2)
    {
        y-=ym;
        x+=xm;
    }
    lo=max(lo,x);

    if(lo>hi)return 0;
    return ((hi-lo)/xm)+1;
}

int main()
{
    LL a,b,c,x1,x2,y1,y2;
    int tno=0,T;
    scanf("%d",&T);
    while(++tno<=T)
    {
        scanf("%lld %lld %lld %lld %lld %lld %lld",&a,&b,&c,&x1,&x2,&y1,&y2);
        LL ans=cnt(a,b,c,x1,x2,y1,y2);
        printf("Case %d: %lld\n",tno,ans);
    }
    return 0;
}

