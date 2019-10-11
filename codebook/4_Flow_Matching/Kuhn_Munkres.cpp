struct KM{//0-base
	int n,match[MAXN],vx[MAXN],vy[MAXN];
	int edge[MAXN][MAXN],lx[MAXN],ly[MAXN],slack[MAXN];
	void init(int _n){n=_n;
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				edge[i][j]=0;
	}
	void addEdge(int x, int y, int w){ 
		edge[x][y]=w;
	}
	bool DFS(int x){
		vx[x]=1;
		for(int y=0;y<n;++y){
			if(vy[y]) continue;
			if(lx[x]+ly[y]>edge[x][y])
				slack[y]=min(slack[y], lx[x]+ly[y]-edge[x][y]);
			else{
				vy[y]=1;
				if(!~match[y]||DFS(match[y]))
        			return match[y] = x,1;
			}
		}
		return 0;
	}
	int solve(){
		fill(match,match+n,-1);
		fill(lx,lx+n,-INF),fill(ly,ly+n,0);
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				lx[i]=max(lx[i],edge[i][j]);
		for(int i=0;i<n;++i){
			fill(slack,slack+n,INF);
			while(1){
				fill(vx,vx+n,0),fill(vy,vy+n,0);
				if(DFS(i)) break;
				int d=INF;
				for(int j=0;j<n;++j)
					if(!vy[j]) d=min(d,slack[j]);
				for(int j=0;j<n;++j){
					if(vx[j]) lx[j]-=d;
					if(vy[j]) ly[j]+=d;
					else slack[j]-=d;
				}
			}
		}
		int res=0;
		for(int i=0;i<n;++i) res+=edge[match[i]][i];
		return res;
	}
};
