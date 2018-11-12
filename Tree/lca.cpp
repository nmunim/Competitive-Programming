//LCA

int n,T[100009], P[100009][23],L[100009];

void process()
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 0; 1 << j < n; j++)
            P[i][j] = -1;
    for (i = 1; i <= n; i++)
        P[i][0] = T[i];
    for (j = 1; 1 << j < n; j++)
        for (i = 1; i <= n; i++)
            if (P[i][j - 1] != -1)
                P[i][j] = P[P[i][j - 1]][j - 1];
}

int lca(int p, int q)
{
    int tmp, log, i;
    if (L[p] < L[q])
        tmp = p, p = q, q = tmp;
    for (log = 1; 1 << log <= L[p]; log++);
    log--;
    //we find the ancestor of node p situated on the same level
    for (i = log; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q])
            p = P[p][i];

    if (p == q)
        return p;
    for (i = log; i >= 0; i--)
        if (P[p][i] != -1 && P[p][i] != P[q][i])
            p = P[p][i], q = P[q][i];

    return T[p];
}

// parent of u at level k

int klevpar(int u,int k)
{
    int tmp, log, i;
    for (log = 1; 1 << log <= L[u]; log++);
    log--;
    for (i = log; i >= 0; i--)
        if (L[u] - (1 << i) >= k)
            u = P[u][i];

    return u;
}
