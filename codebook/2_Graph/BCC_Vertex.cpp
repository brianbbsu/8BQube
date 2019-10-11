vector<int> G[N];// 1-base
vector<int> bcc[N];
int low[N],vis[N],Time;
int bcc_id[N],bcc_cnt;// 1-base
bool is_cut[N];//whether is av
int st[N],top;
void dfs(int u,int pa=-1){
	int child=0;
	low[u]=vis[u]=++Time;
	st[top++]=u;
	for(int v:G[u])
		if(!vis[v]){
			dfs(v,u),++child;
			low[u]=min(low[u],low[v]);
			if(vis[u]<=low[v]){
				is_cut[u]=1;
				bcc[++bcc_cnt].clear();
				int t;
				do{
					bcc_id[t=st[--top]]=bcc_cnt;
					bcc[bcc_cnt].push_back(t);
				}while(t!=v);
				bcc_id[u]=bcc_cnt;
				bcc[bcc_cnt].push_back(u);
			}
		}
		else if(vis[v]<vis[u]&&v!=pa)
			low[u]=min(low[u],vis[v]);
	if(pa==-1&&child<2)is_cut[u]=0;
}
inline void bcc_init(int n){
	Time=bcc_cnt=top=0;
	for(int i=1;i<=n;++i)
		G[i].clear(),vis[i]=0,is_cut[i]=0,bcc_id[i]=0;
}
