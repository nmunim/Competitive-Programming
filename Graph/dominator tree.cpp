int N;
vector<int> graph[100008];
vector<int> domtree[100008],rgraph[100008],bucket[100008];
int sdom[100008],par[100008],dom[100008],dsu[100008],label[100008];
int arr[100008],rev[100008],timer;

int Find(int u,int x=0)
{
    if(u==dsu[u])return x?-1:u;
    int v = Find(dsu[u],x+1);
    if(v<0)return u;
    if(sdom[label[dsu[u]]] < sdom[label[u]])
        label[u] = label[dsu[u]];
    dsu[u] = v;
    return x?v:label[u];
}
void Union(int u,int v)
{
    dsu[v]=u;
}
void dfs0(int u)
{
    timer++;arr[u]=timer;rev[timer]=u;
    label[timer]=timer;sdom[timer]=timer;dsu[timer]=timer;
    for(int i=0;i<graph[u].size();i++)
    {
        int w = graph[u][i];
        if(!arr[w])dfs0(w),par[arr[w]]=arr[u];
        rgraph[arr[w]].push_back(arr[u]);
    }
}

void buildtree(int src)  // the graph is 1 based, clear graph, rgraph, bucket,domtree for each testcase
{                          // no need to build rgraph manually, set arr to 0,
    timer=0;
    dfs0(src);
    N=timer;
    for(int i=N;i>=1;i--)
    {
        for(int j=0;j<rgraph[i].size();j++)
            sdom[i] = min(sdom[i],sdom[Find(rgraph[i][j])]);
        if(i>1)bucket[sdom[i]].push_back(i);
        for(int j=0;j<bucket[i].size();j++)
        {
            int w = bucket[i][j];
            int v = Find(w);
            if(sdom[v]==sdom[w])dom[w]=sdom[w];
            else dom[w] = v;
        }
        if(i>1)Union(par[i],i);
    }
    for(int i=2;i<=N;i++)
    {
        if(dom[i]!=sdom[i])
            dom[i]=dom[dom[i]];
        domtree[rev[i]].PB(rev[dom[i]]);
        domtree[rev[dom[i]]].PB(rev[i]);
    }
}
