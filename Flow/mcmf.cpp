#include <bits/stdc++.h>
using namespace std;

// use djkstra / belmanford accordingly

#define MAX 3009
bool done[MAX];
int used[MAX];
typedef long long Tc;
typedef long long Tf;

struct Edge {
   int from, to, next;
   Tf cap, flow;
   Tc cost;
   Edge(int from, int to, int next, Tf cap, Tc cost) {
      this->from = from;
      this->to = to;
      this->next = next;
      this->cap = cap;
      this->cost = cost;
      this->flow = 0;
   }
};

struct MinCostFlow {
   typedef pair <Tc, int> Pti;
   Tf infF=(numeric_limits<Tf>::max() / 4);
   Tc infC=(numeric_limits<Tc>::max() / 4);
   int n;
   int S, T, ne[MAX];
   Tc d[MAX], pi[MAX];
   vector < Edge > E;

   void init(int _n) {
      n=_n;
      memset(ne, -1, n * sizeof(int));
      fill(pi, pi+n, 0);
      E.clear();
   }
   void addEdge(int u, int v, Tf cap = 1, Tc cost = 0) {
      E.push_back(Edge(u, v, ne[u], cap, cost));
      ne[u] = (int)E.size()-1;
      E.push_back(Edge(v, u, ne[v], 0, -cost));
      ne[v] = (int)E.size()-1;
   }

   // djkstra
   bool djkstra() {
      memset(used, -1, n*sizeof(int));
      memset(done, 0, n*sizeof(bool));
      fill(d, d+n, infC);
      priority_queue < Pti, vector <Pti>, greater <Pti> > q;
      q.push(make_pair(0, S));
      d[S] = 0;

      while(!q.empty()) {
         int u = q.top().second, v;
         q.pop();
         if(done[u]) continue;
         done[u] = true;

         for(int i = ne[u]; i != -1; i = E[i].next) {
            v = E[i].to;
            Tc pot = d[u] + pi[u] - pi[v];
            if(E[i].cap > E[i].flow && pot + E[i].cost < d[v]) {
               d[v] = pot + E[i].cost;
               used[v] = i;
               q.push(make_pair(d[v], v));
            }
         }
      }
      for(int i = 0; i < n; i++) pi[i] = min(pi[i] + d[i], infC);

      return d[T] != infC;
   }

    // belmanford
    bool belmanford() {
      memset(used, -1, n*sizeof(int));
      memset(done, 0, n*sizeof(bool));
      fill(d, d+n, infC);
      queue<int> q;
      q.push(S);
      d[S] = 0;

      while(!q.empty()) {
         int u = q.front(), v;
         q.pop();
         done[u] = 0;

         for(int i = ne[u]; i != -1; i = E[i].next) {
            v = E[i].to;
            Tc pot = d[u] + pi[u] - pi[v];
            if(E[i].cap > E[i].flow && pot + E[i].cost < d[v]) {
               d[v] = pot + E[i].cost;
               used[v] = i;
               if(done[v]==0)
               {
                   q.push(v);
                   done[v]=1;
               }
            }
         }
      }
      for(int i = 0; i < n; i++) pi[i] = min(pi[i] + d[i], infC);

      return d[T] != infC;
   }


   pair <Tf, Tc> maxFlow(int src, int snk) {
      S = src, T = snk;
      Tf flow = 0;
      Tc cost = 0;

      while(djkstra()) {
         // get blocking flow
         snk = T;
         Tf bflow = infF;
         while(snk != S) {
            bflow = min(bflow, E[ used[snk] ].cap - E[ used[snk] ].flow);
            snk = E[ used[snk] ].from;
         }
         // augment path
         snk = T;
         while(snk != S) {
            E[ used[snk] ].flow += bflow;
            E[ used[snk] ^ 1 ].flow -= bflow;
            cost += E[ used[snk] ].cost * bflow;
            snk = E[ used[snk] ].from;
         }
         flow += bflow;
      }
      return make_pair(flow, cost);
   }
} maxf;
