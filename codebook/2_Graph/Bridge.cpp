struct Bridge{//1-base
	int n,low[MAXN],dfn[MAXN],t;
	vector<pii> G[MAXN],edge;
	vector<bool> bri;
	void init(int _n){n=_n;
		for(int i=1;i<=n;++i) G[i].clear();
	}
	void add_edge(int a,int b){
		int x=edge.size();
		G[a].pb(pii(b,x)),G[b].pb(pii(a,x)),edge.pb(pii(a,b));
	}
	void dfs(int x,int f){
		dfn[x]=low[x]=++t;
		for(auto i:G[x])
			if(!dfn[i.X])
				dfs(i.X,i.Y),low[x]=min(low[x],low[i.X]);
			else if(i.Y!=f) low[x]=min(low[x],low[i.X]);
		if(low[x]==dfn[x] && f!=-1) bri[f]=1;
	}
	void get_edge(){
		bri.clear(),bri.resize(edge.size(),0);
		FILL(low,0),FILL(dfn,0),t=0;
		for(int i=1;i<=n;++i)
			if(!dfn[i]) dfs(i,-1);
	}
};
