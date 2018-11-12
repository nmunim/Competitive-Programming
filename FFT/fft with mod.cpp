
void multiply ( vector<LL> & a, vector<LL> & b, vector<LL> & res) {
    for(int i=0;i<a.size();i++)
    {
        a[i]%=MOD;
        if(a[i]<0)a[i]+=MOD;
    }
     for(int i=0;i<b.size();i++)
    {
        b[i]%=MOD;
        if(b[i]<0)b[i]+=MOD;
    }
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;

    vector<base>a1(n),a2(n),b1(n),b2(n),a3(n),b3(n);

    a.resize(n);
    b.resize(n);
    LL x1=(((1LL<<10)-1)<<20), x2=(((1LL<<10)-1)<<10), x3=((1LL<<10)-1);

    for(int i=0;i<n;i++)
    {
        a1[i]=((a[i]&x1)>>20);
        a2[i]=((a[i]&x2)>>10);
        a3[i]=(a[i]&x3);
        b1[i]=((b[i]&x1)>>20);
        b2[i]=((b[i]&x2)>>10);
        b3[i]=(b[i]&x3);
    }

    fft (a1, false),  fft (a2, false);
    fft (b1, false),  fft (b2, false);
    fft (a3, false),  fft (b3, false);
    vector<base>c0(n),c1(n),c2(n),c3(n),c4(n);

    for(int i=0;i<n;i++)
    {
        c0[i]=a3[i]*b3[i];
        c1[i]=a2[i]*b3[i]+a3[i]*b2[i];
        c2[i]=a2[i]*b2[i]+a1[i]*b3[i]+a3[i]*b1[i];
        c3[i]=a1[i]*b2[i]+a2[i]*b1[i];
        c4[i]=a1[i]*b1[i];
    }
    fft (c0, true);
    fft (c1, true);
    fft (c2, true);
    fft (c3, true);
    fft (c4, true);

    res.resize (n);
    for (size_t i=0; i<n; ++i)
        res[i] =(((((LL)(c0[i].real()+0.5))%MOD)*((1)%MOD))%MOD
        +((((LL)(c1[i].real()+0.5))%MOD)*((1LL<<10)%MOD))%MOD
        +((((LL)(c2[i].real()+0.5))%MOD)*((1LL<<20)%MOD))%MOD
        +((((LL)(c3[i].real()+0.5))%MOD)*((1LL<<30)%MOD))%MOD
        +((((LL)(c4[i].real()+0.5))%MOD)*((1LL<<40)%MOD))%MOD)%MOD;
}
