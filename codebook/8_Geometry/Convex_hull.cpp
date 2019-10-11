struct convex_hull{
	vector<pdd> dots;
	void add_dot(double a,double b){
		dots.pb(pdd(a,b));
	}
	vector<pdd> hull(){
		vector<pdd> ans;
		sort(dots.begin(),dots.end());
		ans.pb(dots[0]),ans.pb(dots[1]);
		for(int i=2;i<SZ(dots);++i){
			while(SZ(ans)>=2) 
				if(ori(ans[SZ(ans)-2],ans.back(),dots[i])<=0) 
					ans.pop_back();
				else break;
			ans.pb(dots[i]);
		}
		for(int i=SZ(dots)-2,t=SZ(ans);i>=0;--i){
			while(SZ(ans)>t)
				if(ori(ans[SZ(ans)-2],ans.back(),dots[i])<=0) 
					ans.pop_back();
				else break;
			ans.pb(dots[i]);
		}
		ans.pop_back();
		return ans;
	}
};
