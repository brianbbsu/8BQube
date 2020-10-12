struct Strongly_CC{//1-base
	int low[N], dfn[N], bln[N], sz[N], n, Time, nScc;
	bitset<N> instack;
	stack<int> st;
	vector<int> G[N], SCC[N];
	void init(int _n) {
        n = _n;
		for(int i = 1; i <= n; ++i)
			G[i].clear();
	}
	void add_edge(int a, int b) {
		G[a].pb(b);
	}
	void dfs(int u) {
		dfn[u] = low[u] = ++Time;
		instack[u] = 1, st.push(u);
		for(int i : G[u])
			if(!dfn[i]) dfs(i), low[u] = min(low[i], low[u]);
			else if(instack[i] && dfn[i] < dfn[u]) 
				low[u] = min(low[u], dfn[i]);
		if(low[u] == dfn[u]) {
			int tmp;
			do {
				tmp = st.top(), st.pop();
				instack[tmp]=0, bln[tmp] = nScc;
			}while(tmp != u);
            ++nScc;
		}
	}
	void solve() {
        Time = nScc = 0;
		for(int i = 1; i <= n; ++i) 
            SCC[i].clear(), low[i] = dfn[i] = bln[i] = sz[i] = 0;
		for(int i = 1; i <= n; ++i)
			if(!dfn[i]) 
                dfs(i);
		for(int i = 1; i <= n; ++i)
			++sz[bln[i]], SCC[bln[i]].pb(i); 
	}
};
