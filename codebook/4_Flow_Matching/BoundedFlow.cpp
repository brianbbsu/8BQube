struct BoundedFlow{//0-base
	struct Edge{
		int to,cap,flow,rev;
	};
	vector<Edge> G[MAXN];
	int n,s,t,dis[MAXN],cur[MAXN],cnt[MAXN];
	void init(int _n){n=_n;
		for(int i=0;i<n+2;++i) G[i].clear(),cnt[i]=0;
	}
	void add_edge(int u,int v,int lcap,int rcap){
		cnt[u]-=lcap,cnt[v]+=lcap;
		G[u].pb(Edge{v,rcap,lcap,(int)G[v].size()});
		G[v].pb(Edge{u,0,0,(int)G[u].size()-1});
	}
	void add_edge(int u,int v,int cap){
		G[u].pb(Edge{v,cap,0,(int)G[v].size()});
		G[v].pb(Edge{u,0,0,(int)G[u].size()-1});
	}
	int dfs(int u,int cap){
		if(u==t || !cap) return cap;
		for(int &i=cur[u];i<(int)G[u].size();++i){
			Edge &e=G[u][i];
			if(dis[e.to]==dis[u]+1 && e.flow!=e.cap){
				int df=dfs(e.to,min(e.cap-e.flow,cap));
				if(df){
					e.flow+=df;
					G[e.to][e.rev].flow-=df;
					return df;
				}
			} 
		}
		dis[u]=-1;
		return 0;
	}
	bool bfs(){
		FILL(dis,-1);
		queue<int> q;
		q.push(s),dis[s]=0;
		while(!q.empty()){
			int tmp=q.front();
			q.pop();
			for(auto &u:G[tmp])
				if(!~dis[u.to] && u.flow!=u.cap){
					q.push(u.to);
					dis[u.to]=dis[tmp]+1; 
				}
		} 
		return dis[t]!=-1;
	}
	int maxflow(int _s,int _t){
		s=_s,t=_t;
		int flow=0,df;
		while(bfs()){
			FILL(cur,0);
			while(df=dfs(s,INF)) flow+=df;
		}
		return flow;
	}
	bool solve(){
		int sum=0; 
		for(int i=0;i<n;++i)
			if(cnt[i]>0) add_edge(n+1,i,cnt[i]),sum+=cnt[i];
			else if(cnt[i]<0) add_edge(i,n+2,-cnt[i]);
		if(sum!=maxflow(n+1,n+2)) sum=-1;
		for(int i=0;i<n;++i)
			if(cnt[i]>0) G[n+1].pop_back(),G[i].pop_back();
			else if(cnt[i]<0) G[i].pop_back(),G[n+2].pop_back();
		return sum!=-1;
	}
	int solve(int _s,int _t){
		add_edge(_t,_s,INF);
		if(!solve()) return -1; //invalid flow
		int x=G[_t].back().flow;
		return G[_t].pop_back(),G[_s].pop_back(),x;
	}
};
