const int MAXN=40005;
vector<int> G[MAXN];//1-base
int n,B,arr[MAXN],ans[100005],cur_ans;
int in[MAXN],out[MAXN],dfn[MAXN*2],dft;
int deep[MAXN],sp[__lg(MAXN*2)+1][MAXN*2],bln[MAXN],spt;
bitset<MAXN> inset;
struct QUERY{
  int L,R,Lid,id,lca;
  QUERY(int l,int r,int _id):L(l),R(r),lca(0),id(_id){}
  bool operator<(const QUERY &b){
    if(Lid!=b.Lid) return Lid<b.Lid;
    return R<b.R;
  }
};
vector<QUERY> query;
void dfs(int u,int f,int d){
  deep[u]=d,sp[0][spt]=u,bln[u]=spt++;
  dfn[dft]=u,in[u]=dft++;
  for(int v:G[u])
    if(v!=f)
      dfs(v,u,d+1),sp[0][spt]=u,bln[u]=spt++;
  dfn[dft]=u,out[u]=dft++;
}
int lca(int u,int v){
  if(bln[u]>bln[v]) swap(u,v);
  int t=__lg(bln[v]-bln[u]+1);
  int a=sp[t][bln[u]],b=sp[t][bln[v]-(1<<t)+1];
  if(deep[a]<deep[b]) return a;
  return b;
}
void flip(int x){
  if(inset[x]) sub(arr[x]); // TODO
  else add(arr[x]); // TODO
  inset[x]=~inset[x];
}
void solve(){
  B=sqrt(2*n),dft=spt=cur_ans=0,dfs(1,1,0);
  for(int i=1,x=2;x<2*n;++i,x<<=1)
    for(int j=0;j+x<=2*n;++j)
      if(deep[sp[i-1][j]]<deep[sp[i-1][j+x/2]])
        sp[i][j]=sp[i-1][j];
      else sp[i][j]=sp[i-1][j+x/2];
  for(auto &q:query){
    int c=lca(q.L,q.R);
    if(c==q.L||c==q.R)
      q.L=out[c==q.L?q.R:q.L],q.R=out[c];
    else if(out[q.L]<in[q.R])
      q.lca=c,q.L=out[q.L],q.R=in[q.R];
    else q.lca=c,c=in[q.L],q.L=out[q.R],q.R=c;
    q.Lid=q.L/B;
  }
  sort(ALL(query));
  int L=0,R=-1;
  for(auto q:query){
    while(R<q.R) flip(dfn[++R]);
    while(L>q.L) flip(dfn[--L]);
    while(R>q.R) flip(dfn[R--]);
    while(L<q.L) flip(dfn[L++]);
    if(q.lca) add(arr[q.lca]);
    ans[q.id]=cur_ans;
    if(q.lca) sub(arr[q.lca]);
  }
}
