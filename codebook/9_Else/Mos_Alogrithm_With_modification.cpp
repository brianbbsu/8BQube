struct QUERY{//BLOCK=N^{2/3}
	int L,R,id,LBid,RBid,T;
	QUERY(int l,int r,int id,int lb,int rb,int t):
		L(l),R(r),id(id),LBid(lb),RBid(rb),T(t){}
	bool operator<(const QUERY &b)const{
		if(LBid!=b.LBid) return LBid<b.LBid;
		if(RBid!=b.RBid) return RBid<b.RBid;
		return T<b.T;
	}
};
vector<QUERY> query;
int cur_ans,arr[MAXN],ans[MAXN];
void addTime(int L,int R,int T){}
void subTime(int L,int R,int T){}
void add(int x){}
void sub(int x){}
void solve(){
	sort(ALL(query));
	int L=0,R=0,T=-1;
	for(auto q:query){
		while(T<q.T) addTime(L,R,++T);
		while(T>q.T) subTime(L,R,T--);
		while(R<q.R) add(arr[++R]);
		while(L>q.L) add(arr[--L]);
		while(R>q.R) sub(arr[R--]);
		while(L<q.L) sub(arr[L++]);
		ans[q.id]=cur_ans;
	}
}
