
int M[1002][1002][11][11],prelog[1002];
void calcprelog()
{
    REP(i,1,1001)prelog[i]=log2(i);
}

void precompute_max(){
    for (int i = 0 ; (1<<i) <= n; i += 1){
        for(int j = 0 ; (1<<j) <= m ; j += 1){
            for (int x = 1 ; x + (1<<i) -1 <= n; x+= 1){
                for (int y = 1 ;  y + (1<<j) -1 <= m; y+= 1){
                    if (i == 0 and j == 0)
                        M[x][y][i][j] = arr[x][y]; // store x, y
                    else if (i == 0)
                        M[x][y][i][j] = max(M[x][y][i][j-1], M[x][y+(1<<(j-1))][i][j-1]);
                    else if (j == 0)
                        M[x][y][i][j] = max(M[x][y][i-1][j], M[x+ (1<<(i-1))][y][i-1][j]);
                    else
                        M[x][y][i][j] = max(max(M[x][y][i-1][j-1], M[x + (1<<(i-1))][y][i-1][j-1]), max(M[x][y+(1<<(j-1))][i-1][j-1], M[x + (1<<(i-1))][y+(1<<(j-1))][i-1][j-1]));
                    // cout << "from i="<<x<<" j="<<y<<" of length="<<(1<<i)<<" and length="<<(1<<j) <<"max is: " << M[x][y][i][j] << endl;
                }
            }
        }
    }
}

int compute_max(int x, int y, int x1, int y1){
    int k = prelog[x1 - x + 1];
    int l = prelog[y1 - y + 1];
    // cout << "Value of k="<<k<<" l="<<l<<endl;
    int ans = max(max(M[x][y][k][l], M[x1 - (1<<k) + 1][y][k][l]), max(M[x][y1 - (1<<l) + 1][k][l], M[x1 - (1<<k) + 1][y1 - (1<<l) + 1][k][l]));
    return ans;
}
