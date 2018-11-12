// nodes are 0-indexed
// nE=number of edges
// nSpe=number of nodes
// specify eg[]

const LL N=62;
struct Edge
{
    LL u,v,c;
} eg[N*N];

LL nSpe, nE, bln[N], vst[N], dis[N], ismrg[N], prv[N];

LL dmst(LL root)
{
    memset(ismrg,0,sizeof ismrg);
    LL curW, ww;
    curW=ww=0;
    while (1)
    {
        memset(prv,-1,sizeof prv);
        for (LL i=0; i<nSpe; i++)
            dis[i] = INF;
        for (LL i=0; i<nE; i++)
        {
            if (eg[i].v!=eg[i].u && eg[i].v!=root && dis[eg[i].v] > eg[i].c)
            {
                dis[eg[i].v] = eg[i].c;
                prv[eg[i].v] = eg[i].u;
            }
        }
// find cycle
        LL sign=1;
        curW=0;
        memset(bln,-1,sizeof bln);
        memset(vst,-1, sizeof vst);
        for (LL i=0; i<nSpe; i++)
        {
            if (ismrg[i]) continue;
            if (prv[i]==-1 && i!=root) return INF;
            if (i!=root) curW += dis[i];
            LL s;
            for (s=i; s!=-1 && vst[s]==-1; s=prv[s])
                vst[s]=i;
            if (s!=-1 && vst[s]==i)
            {
                sign=0;
                LL j=s;
                while (1)
                {
                    ismrg[j]=1;
                    bln[j]=s;
                    ww += dis[j];
                    j=prv[j];
                    if (j==s) break;
                }
                ismrg[s]=0;
            }
        }
        if (sign) break;
// merge
        for (LL i=0; i<nE; i++)
        {
            if (bln[eg[i].v]!=-1) eg[i].c -= dis[eg[i].v];
            if (bln[eg[i].u]!=-1) eg[i].u = bln[eg[i].u];
            if (bln[eg[i].v]!=-1) eg[i].v = bln[eg[i].v];
            if (eg[i].u==eg[i].v) eg[i--] = eg[--nE];
        }
// system("pause");
    }
    return curW+ww;
}
