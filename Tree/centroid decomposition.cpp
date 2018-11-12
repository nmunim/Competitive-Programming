int nn,sub[100008],par[100008];
set<int> gset[100008];

void dfs1(int u,int p)
{
	sub[u]=1;
	nn++;
	if(gset[u].empty())return;
	itrALL(gset[u],it)
    if(*it!=p)
    {
        dfs1(*it,u);
        sub[u]+=sub[*it];
    }
}
int dfs2(int u,int p)
{

	if(gset[u].empty())return u;
	itrALL(gset[u],it)
		if(*it!=p && sub[*it]>nn/2)
			return dfs2(*it,u);
	return u;
}
void decompose(int root,int p)  // call decompose(1,-1)
{
	nn=0;
	dfs1(root,root);
	int centroid = dfs2(root,root);
	if(p==-1)p=centroid;
	par[centroid]=p;
	if(gset[centroid].empty())return;
	itrALL(gset[centroid],it)
	{
		gset[*it].erase(centroid);
		decompose(*it,centroid);
	}
	gset[centroid].clear();
}
