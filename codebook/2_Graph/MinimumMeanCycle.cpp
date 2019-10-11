ll road[MAXN][MAXN];//input here
struct MinimumMeanCycle{//0-base
	ll dp[MAXN+5][MAXN],n;
	pll solve(){//watch out overflow
		ll k=1,a=-1,b=-1,ta,tb,L=n+1;
		for(ll i=2;i<=L;++i)
			for(ll k=0;k<n;++k)
				for(ll j=0;j<n;++j)
					dp[i][j]=min(dp[i-1][k]+road[k][j],dp[i][j]);
		for(ll i=0;i<n;++i)
		{
			if(dp[L][i]>=INF) continue;
			ta=0,tb=1;
			for(ll j=1;j<n;++j)
				if(dp[j][i]<INF&&ta*(L-j)<(dp[L][i]-dp[j][i])*tb) 
					ta=dp[L][i]-dp[j][i],tb=L-j;
			if(ta==0) continue;
			if(a==-1) a=ta,b=tb;
			else if(a*tb>ta*b) a=ta,b=tb;
		}
		if(a!=-1) return k=__gcd(a,b),MP(a/k,b/k);
		return MP(-1LL,-1LL);
	}
	void init(int _n){n=_n;
		for(ll i=0;i<n;++i)
			for(ll j=0;j<n;++j)
				dp[i+2][j]=INF;
	}
};
