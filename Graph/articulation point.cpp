int n,m,h[10001],par[10001],d[10001],color[10001],root;
vector<int> graph[10001];
set<int>artpoint;

void dfs(int u)
{
    d[u]=h[u];
    color[u]=1;
    int children=0;
    for(int i=0;i<graph[u].size();i++)
    {
        int v=graph[u][i];
        if(color[v]==0)
        {
            par[v]=u;
            h[v]=h[u]+1;
            dfs(v);
            d[u]=min(d[u],d[v]);
            if(d[v]>=h[u]&&u!=root)artpoint.insert(u);
            children++;
        }
        else if(v!=par[u])
            d[u]=min(d[u],h[v]);
    }
    if(children>1 && u==root)artpoint.insert(u);

    color[u]=2;
}

int findarticulationpoint()
{
    artpoint.clear();
    memset(color,0,sizeof color);
    for(int i=1;i<=n;i++)
    {
        if(color[i]==0)
        {
            h[i]=0;
            par[i]=-1;
            root=i;
            dfs(i);
        }
    }
    return artpoint.size();
}
