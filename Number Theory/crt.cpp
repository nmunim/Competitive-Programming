//crt

int egcd(int a,int b,int &x,int &y)
{
    if(a==0)
    {
        x=0;y=1;
        return b;
    }
    int x1,y1;
    int d=egcd(b%a,a,x1,y1);
    x=y1-(b/a)*x1;
    y=x1;
    return d;
}

// Solve linear congruences equation:
// - a[i] * x = b[i] MOD m[i] (mi don't need to be co-prime)
// Tested:
// - https://open.kattis.com/problems/generalchineseremainder
bool linearCongruences(const vector<int> &a, const vector<int> &b,
        const vector<int> &m, int &x, int &M) {
    int n = a.size();
    x = 0; M = 1;
    for(int i=0;i<n;i++) {
        int a_ = a[i] * M, b_ = b[i] - a[i] * x, m_ = m[i];
        int y, t, g = egcd(a_, m_, y, t);
        if (b_ % g) return false;
        b_ /= g; m_ /= g;
        x += M * (y * b_ % m_);
        M *= m_;
    }
    x = (x + M) % M;
    return true;
}

int main()
{
    VI a={1,1},b={2,3},m={5,6};
    int x,M;
    if(linearCongruences(a,b,m,x,M))cout<<x<<' '<<M<<'\n';
    return 0;
}
