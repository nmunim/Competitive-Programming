int n;
vector<PII> graph[1001];
int dist[1001];

bool belmanford(int s)
{
    memset(dist,127,sizeof dist);
    dist[s]=0;
    for(int i=1;i<=n-1;i++)   //relaxing the edges n-1 times
    {
        for(int u=1;u<=n;u++)
        {
            for(int j=0;j<graph[u].size();j++)
            {
                PII v=graph[u][j];
                dist[v.first]=min(dist[v.first],dist[u]+v.second);
            }
        }
    }
    for(int u=1;u<=n;u++)
    {
        for(int j=0;j<graph[u].size();j++)
        {
            PII v=graph[u][j];
            if(dist[v.first]>dist[u]+v.second)return 1;  //neg cycle detected
        }
    }
    return 0;
}
