int n,color[10001],h[10001],d[10001],par[10001];
vector<int> graph[10001];
vector<PII> bridge;

void dfs(int u)
{
    d[u]=h[u];
    color[u]=1;
    for(int i=0;i<graph[u].size();i++)
    {
        int v=graph[u][i];
        if(color[v]==0)
        {
            par[v]=u;
            h[v]=h[u]+1;
            dfs(v);
            d[u]=min(d[u],d[v]);
            if(d[v]>h[u])
                bridge.push_back(make_pair(min(v,u),max(v,u)));
        }
        else if(v!=par[u])
            d[u]=min(d[u],h[v]);
    }
    color[u]=2;
}

void findbridge()
{
    bridge.clear();
    memset(color,0,sizeof color);
    for(int i=1;i<=n;i++)
    {
        if(color[i]==0)
        {
            h[i]=0;
            par[i]=-1;
            dfs(i);
        }
    }
}
