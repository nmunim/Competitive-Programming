/*

 Maxflow Dinic Implementation. Work for both directed and Undirected Graph
 Complexity : V^2E

 * init(number_of_node)
 * addEdge(from, to, cap)
 * dinitz(source,dest)

 $ MAXNODE : 3000
 $ For Undirected Graph : edge and reverse edge capacity = cap

 */
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
const long long INF = 1e9;
typedef long long T;
struct Edge
{
    int u, v;
    T cap, flow;
    Edge(int u, int v, T c, T f):u(u), v(v), cap(c), flow(f) {}
};

struct Dinic
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];

    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++) G[i].clear();
        edge.clear();
    }

    void addEdge(int u, int v, T cap)
    {
        edge.push_back(Edge(u, v, cap, 0)); edge.push_back(Edge(v, u, 0, 0));
        m=edge.size();
        G[u].push_back(m-2); G[v].push_back(m-1);
    }

    bool bfs()
    {
        memset(vis, 0, sizeof vis);
        queue<int> q;
        q.push(s);
        d[s]=0;
        vis[s]=1;
        while(!q.empty()){
            int x=q.front();q.pop();
            for(int i=0; i<G[x].size(); i++){
                Edge& e=edge[G[x][i]];
                if(!vis[e.v] && e.cap>e.flow){
                    vis[e.v]=true;
                    d[e.v]=d[x]+1;
                    q.push(e.v);
                }
            }
        }
        return vis[t];
    }

    T dfs(int x, T a)
    {
        if(x==t || a==0)return a;
        T flow=0, f;
        for(int& i=cur[x]; i<G[x].size(); i++){
            Edge& e=edge[G[x][i]];
            if(d[x]+1==d[e.v] && (f=dfs(e.v, min(a, e.cap-e.flow)))>0){
                e.flow+=f;
                edge[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0)break;
            }
        }
        return flow;
    }

    T dinitz(int s, int t)
    {
        this->s=s;
        this->t=t;
        T flow=0;
        while(bfs()){
            memset(cur, 0, sizeof cur);
            flow+=dfs(s, INF);
        }
        return flow;
    }
} maxf;
