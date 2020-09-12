struct Strongly_CC{//1-base
	int low[MAXN],vis[MAXN],bln[MAXN],sz[MAXN],n,t,nScc;
	bitset<MAXN> instack;
	stack<int> st;
	vector<int> G[MAXN],SCC[MAXN];
	void init(int _n){n=_n;
		for(int i=1;i<=n;++i)
			G[i].clear();
	}
	void add_edge(int a,int b){
		G[a].pb(b);
	}
	void dfs(int u){
		vis[u]=low[u]=++t;
		instack[u]=1,st.push(u);
		for(int i:G[u])
			if(!vis[i]) dfs(i),low[u]=min(low[i],low[u]);
			else if(instack[i]&&vis[i]<vis[u]) 
				low[u]=min(low[u],vis[i]);
		if(low[u]==vis[u]){
			int tmp;
			do{
				tmp=st.top(),st.pop();
				instack[tmp]=0,bln[tmp]=nScc;
			}while(tmp!=u);
			++nScc;
		}
	}
	void solve(){
		FILL(low,0),FILL(vis,0),FILL(bln,0),FILL(sz,0),t=nScc=0;
		for(int i=1;i<=n;++i) SCC[i].clear();
		for(int i=1;i<=n;++i)
			if(!vis[i]) dfs(i);
		for(int i=1;i<=n;++i){
			++sz[bln[i]],SCC[bln[i]].pb(i); 
	}
};
