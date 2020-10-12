struct Graph{//0-base (Perfect Match) 
  int n,edge[MAXN][MAXN];
  int match[MAXN],dis[MAXN],onstk[MAXN];
  vector<int> stk;
  void init(int _n){n=_n;
    for(int i=0;i<n;++i) 
      for(int j=0;j<n;++j)
        edge[i][j]=0;
  }
  void add_edge(int u,int v,int w){
    edge[u][v]=edge[v][u]=w;
  }
  bool SPFA(int u){
    if(onstk[u]) return 1;
    stk.pb(u),onstk[u]=1;
    for(int v=0;v<n;++v)
      if(u!=v&&match[u]!=v&&!onstk[v]){
        int m=match[v];
        if(dis[m]>dis[u]-edge[v][m]+edge[u][v]){
          dis[m]=dis[u]-edge[v][m]+edge[u][v];
          onstk[v]=1,stk.pb(v);
          if(SPFA(m)) return 1;
          stk.pop_back(),onstk[v]=0;
        }
      }
    onstk[u]=0,stk.pop_back();
    return 0;
  }
  int solve(){// find a match 
    for(int i=0;i<n;i+=2)
      match[i]=i+1,match[i+1]=i;
    while(1){
      int found=0;
      for(int i=0;i<n;++i) dis[i]=onstk[i]=0;
      for(int i=0;i<n;++i)
        if(stk.clear(),!onstk[i]&&SPFA(i))
          for(found=1;stk.size()>=2;){
            int u=stk.back();
            stk.pop_back();
            int v=stk.back();
            stk.pop_back();
            match[u]=v,match[v]=u;
          }
      if(!found) break;
    }
    int ret=0;
    for(int i=0;i<n;++i) ret+=edge[i][match[i]];
    return ret>>1;
  }
};
