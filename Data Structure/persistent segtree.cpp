
int NEXT_FREE_INDEX, L[3200009],R[3200009],s[3200009],n,ir,a[100009],root[100009];  // ir is initial root, if ir=0, set NEXT_FREE_INDEX=1

void build(int id = ir,int l = 0,int r = n){  // array index from 0 to n-1
	if(r - l < 2){
		s[id] = a[l];
		return ;
	}
	int mid = (l+r)/2;
	L[id] = NEXT_FREE_INDEX ++;
	R[id] = NEXT_FREE_INDEX ++;
	build(L[id], l, mid);
	build(R[id], mid, r);
	s[id] = s[L[id]] + s[R[id]];
}

int upd(int p, int v,int id,int l = 0,int r = n){ //For the first query (with index 0) we should run root[0] = upd(p,  v,  ir)
    //and for the rest of them, for j - th query se should run root[j] = upd(p,  v,  root[j - 1])
	int ID =  NEXT_FREE_INDEX ++; // index of the node in new version of segment tree
	if(r - l < 2){
		s[ID] = s[id]+v;
		return ID;
	}
	int mid = (l+r)/2;
	L[ID] = L[id], R[ID] = R[id]; // in case of not updating the interval of left child or right child
	if(p < mid)
		L[ID] = upd(p, v, L[ID], l, mid);
	else
		R[ID] = upd(p, v, R[ID], mid, r);
    s[ID] = s[L[ID]] + s[R[ID]];
	return ID;
}


int sum(int x,int y,int id,int l = 0,int r = n){  // to query from x to y, call sum(x,y+1,root[z])
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= y)	return s[id];
	int mid = (l+r)/2;
	return sum(x, y, L[id], l, mid) +
	       sum(x, y, R[id], mid, r);
}
