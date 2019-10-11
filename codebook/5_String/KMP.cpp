int F[MAXN];
vector<int> match(string A,string B){
	vector<int> ans;
	F[0]=-1,F[1]=0;
	for(int i=1,j=0;i<B.size();F[++i]=++j){
		if(B[i]==B[j]) F[i]=F[j];//optimize
		while(j!=-1&&B[i]!=B[j]) j=F[j];
	}
	for(int i=0,j=0;i-j+B.size()<=A.size();++i,++j){
		while(j!=-1&&A[i]!=B[j]) j=F[j];
		if(j==B.size()-1) ans.pb(i-j);
	}
	return ans;
}
