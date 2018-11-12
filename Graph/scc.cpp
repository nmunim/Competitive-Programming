//scc

int n,m;
vector<int> graph[20001],rgraph[20001],order,component;
bool vis[20001];

void dfs1(int u)
{
    vis[u]=1;
    for(int i=0;i<graph[u].size();i++)
    {
        if(!vis[graph[u][i]])dfs1(graph[u][i]);
    }
    order.push_back(u);
}

void dfs2(int u)
{
    vis[u]=1;
    component.push_back(u);
    for(int i=0;i<rgraph[u].size();i++)
    {
        if(!vis[rgraph[u][i]])dfs2(rgraph[u][i]);
    }
}

void produce_scc()
{
    memset(vis,0,sizeof vis);
    order.clear();
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])dfs1(i);
    }
    memset(vis,0,sizeof vis);
    for(int i=2;i<=n+1;i++)
    {
        if(!vis[order[n-i+1]])
        {
            dfs2(order[n-i+1]);
            // take scc from component
            component.clear();
        }
    }
}
