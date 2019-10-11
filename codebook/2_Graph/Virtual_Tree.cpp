void insert(int x){
	if(top==-1) 
		return st[++top]=x,void();
	int p=LCA(st[top],x);
	if(p==st[top])
		return st[++top]=x,void();
	while(dep[st[top-1]]>dep[p])
		vG[st[top-1]].pb(st[top]),--top;
	vG[p].pb(st[top]),--top;
	if(st[top]!=p) st[++top]=p;
	st[++top]=x;
}
void ending(){
	while(top>0)
		vG[st[top-1]].pb(st[top]),--top;
}
void reset(int x){
	for(int i:vG[x])
		reset(i);
	vG[x].clear();
}
