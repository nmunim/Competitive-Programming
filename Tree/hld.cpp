// call pre after inputing graph in all test cases
// nodes are numbered from 1 to n
// change segment tree and mx array update accordingly

int n;
VI graph[100005];
int nxt[100005], sz[100005], p[100005], chain[100005], num[100005], csz[100005], top[100005], all, cnt, depth[100005];
LL t[400005], mx[400005];

LL query(int node,int b,int e,int i,int j)
{
    if(b>j || e<i)return 0;
    if(b>=i && e<=j)return t[node];
    int mid=(b+e)/2;
    LL ret1,ret2;
    ret1=query(2*node,b,mid,i,j);
    ret2=query(2*node+1,mid+1,e,i,j);
    return max(ret1,ret2);
}


void update(int node,int b,int e,int i,LL val)
{
    if(b>i||e<i)return;
    if(b==i && e==i){t[node]=val;return;}
    int mid=(b+e)/2;
    update(2*node,b,mid,i,val);
    update(2*node+1,mid+1,e,i,val);
    t[node]=max(t[node*2],t[node*2+1]);
}

void dfs(int v, int pr = 0){
  p[v] = pr;
  sz[v] = 1;
  for(int i=0;i<graph[v].size();i++)
  {
    int to = graph[v][i];
    if(to == pr){
      continue;
    }
    depth[to] = depth[v] + 1;
    dfs(to, v);
    sz[v] += sz[to];
    if(nxt[v] == -1 || sz[to] > sz[nxt[v]]){
      nxt[v] = to;
    }
  }
}

void hld(int v, int pr = -1){
  chain[v] = cnt - 1;
  num[v] = all++;
  if(!csz[cnt - 1]){
    top[cnt - 1] = v;
  }
  ++csz[cnt - 1];
  if(nxt[v] != -1){
    hld(nxt[v], v);
  }
  for(int i=0;i<graph[v].size();i++)
  {
    int to = graph[v][i];
    if(to == pr || to == nxt[v]){
      continue;
    }
    ++cnt;
    hld(to, v);
  }
}

LL ask(int a, int b){
  LL res = 0;
  while(chain[a] != chain[b]){
    if(depth[top[chain[a]]] < depth[top[chain[b]]]) swap(a, b);
    int start = top[chain[a]];
    if(num[a] == num[start] + csz[chain[a]] - 1)
      res = max(res, mx[chain[a]]);
    else
      res = max(res, query(1, 0, n - 1, num[start], num[a]));
    a = p[start];
  }
  if(depth[a] > depth[b]) swap(a, b);
  res = max(res, query(1, 0, n - 1, num[a], num[b]));
  return res;
}

void modify(int a, int b){
  update(1, 0, n - 1, num[a], b);
  int strt = num[top[chain[a]]];
  int en = strt + csz[chain[a]] - 1;
  mx[chain[a]] = query(1, 0, n - 1, strt, en);
}


void pre()
{
    memset(nxt,-1,sizeof nxt);
    depth[1]=0;
    dfs(1);
    cnt=1;
    all=0;
    memset(csz,0,sizeof csz);
    hld(1);
    memset(t,0,sizeof t);
    memset(mx,0,sizeof mx);
}
