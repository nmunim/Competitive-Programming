// 2 sat

vector<int> graph[16001],rgraph[16001],order,ans;
int n,m,a,b,vis[16001],comp[16001];

void dfs1(int u)
{
    vis[u]=1;
    for(int i=0;i<graph[u].size();i++)
    {
        if(!vis[graph[u][i]])
            dfs1(graph[u][i]);
    }
    order.push_back(u);
}

void dfs2(int u,int cl)
{
    comp[u]=cl;
    for(int i=0;i<rgraph[u].size();i++)
    {
        if(comp[rgraph[u][i]]==-1)dfs2(rgraph[u][i],cl);
    }
}

int main()
{
    int t=0,T;
    scanf("%d",&T);
    while(++t<=T)
    {
        scanf("%d %d",&n,&m);
        for(int i=1;i<=16000;i++)
        {
            graph[i].clear();
            rgraph[i].clear();
        }
        order.clear();
        while(n--)
        {
            scanf("%d %d",&a,&b);
            if(a>0 && b<0)swap(a,b);
            if(a>0 && b>0)
            {
                graph[a+m].push_back(b);
                rgraph[b].push_back(a+m);
                graph[b+m].push_back(a);
                rgraph[a].push_back(b+m);
            }
            else if(a<0 && b<0)
            {
                a=fabs(a);b=fabs(b);
                graph[a].push_back(b+m);
                rgraph[b+m].push_back(a);
                graph[b].push_back(a+m);
                rgraph[a+m].push_back(b);
            }
            else if(a<0 && b>0)
            {
                a=fabs(a);
                graph[a].push_back(b);
                rgraph[b].push_back(a);
                graph[b+m].push_back(a+m);
                rgraph[a+m].push_back(b+m);
            }
        }
        memset(vis,0,sizeof vis);
        for(int i=1;i<=2*m;i++)
        {
            if(!vis[i])dfs1(i);
        }
        memset(comp,-1,sizeof comp);

        int k=0;
        for(int i=2*m-1;i>=0;i--)
        {
            if(comp[order[i]]==-1)dfs2(order[i],k++);
        }

        int flag=1;
        for(int i=1;i<=m;i++)
        {
            if(comp[i]==comp[m+i]){flag=0;break;}
        }
        if(flag==0)
        {
            printf("Case %d: No\n",t);
            continue;
        }
        printf("Case %d: Yes\n",t);
        ans.clear();
        for(int i=1;i<=m;i++)
        {
            if(comp[i]>comp[m+i])ans.push_back(i);
        }
        printf("%d",ans.size());
        if(!ans.empty())
        {
            for(int i=0;i<ans.size();i++)
                printf(" %d",ans[i]);
        }
        putchar('\n');
    }
    return 0;
}
