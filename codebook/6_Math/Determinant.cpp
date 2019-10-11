struct matrix
{
	ll M[MAXN][MAXN],n,m;
	matrix(ll n=0,ll m=0):n(n),m(m){FILL(M,0);}
	ll det()
	{
		vector<vector<double>> tM(n,vector<double>(m));
		const double eps=1e-9;
		double x=1;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)
				tM[i][j]=M[i][j];
		for(int i=0;i<n;++i)
		{
			int maxline=i;
			for(int j=i+1;j<n;++j)
				if(tM[j][i]>tM[maxline][i]) maxline=j;
			if(maxline!=i)
				tM[i].swap(tM[maxline]),x*=-1;
			if(fabs(tM[i][i])<eps) return 0;
			for(int j=i+1;j<n;++j)
			{
				double tmp=-tM[j][i]/tM[i][i];
				for(int k=i;k<m;++k)
					tM[j][k]+=tmp*tM[i][k];
			}
		}
		for(int i=0;i<n;++i)
			x=x*tM[i][i];
		return (ll)round(x);
	}
};
