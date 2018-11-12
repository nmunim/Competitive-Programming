struct Matrix
{
    LL mat[17][17];

    Matrix(){}

    void init(int sz)
    {
        memset(mat,0,sizeof mat);
        for(int i=0; i<sz; i++) mat[i][i]=1;
    }
} aux;

inline void matMult(Matrix &m, Matrix &m1, Matrix &m2, int sz)
{
    for(int i=0;i<sz;i++)
    {
        for(int j=0;j<sz;j++)
        {
            m.mat[i][j]=0;
            for(int k=0;k<sz;k++)
            {
                m.mat[i][j]=(m.mat[i][j]+m1.mat[i][k]*m2.mat[k][j])%MOD;
            }
        }
    }
}

inline Matrix expo(Matrix &M, LL n, int sz)
{
    Matrix ret;
    ret.init(sz);

    if(n==0) return ret;
    if(n==1) return M;

    Matrix P=M;

    while(n!=0)
    {
        if(n&1)
        {
            aux=ret;
            matMult(ret,aux,P,sz);
        }

        n>>=1;

        aux=P; matMult(P,aux,aux,sz);
    }

    return ret;
}
