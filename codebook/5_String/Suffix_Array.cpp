struct suffix_array{
	int box[MAXN],tp[MAXN],k,m;
	bool not_equ(int *ra,int a,int b,int k,int n){
		return ra[a]!=ra[b]||a+k>=n||b+k>=n||ra[a+k]!=ra[b+k];
	}
	void radix(int *box,int *key,int *it,int *ot,int m,int n){
		fill_n(box,m,0);
		for(int i=0;i<n;++i) ++box[key[i]];
		partial_sum(box,box+m,box);
		for(int i=n-1;i>=0;--i) ot[--box[key[it[i]]]]=it[i];
	}
	void make_sa(int *sa,int *ra,string s,int n){
		for(int i=0;i<n;++i) ra[i]=s[i];
		do{
			iota(tp,tp+k,n-k),iota(sa+k,sa+n,0);
			radix(box,ra+k,sa+k,tp+k,m,n-k);
			radix(box,ra,tp,sa,m,n);
			tp[sa[0]]=0,m=1;
			for(int i=1;i<n;++i){
				m+=not_equ(ra,sa[i],sa[i-1],k,n);
				tp[sa[i]]=m-1;
			}
			for(int i=0;i<n;++i) ra[i]=tp[i];
			k*=2;
		}while(k<n&&m!=n);
	}
	void make_he(int *he,int *sa,int *ra,string s,int n){
		for(int j=0,k=0;j<n;++j){
			if(ra[j])
				for(;s[j+k]==s[sa[ra[j]-1]+k];++k);
			he[ra[j]]=k,k=max(0,k-1);
		}
	}
	int sa[MAXN],ra[MAXN],he[MAXN];
	void build(string s){
		FILL(sa,0),FILL(ra,0),FILL(he,0);
		FILL(box,0),FILL(tp,0),k=1,m=256;
		make_sa(sa,ra,s,s.size());
		make_he(he,sa,ra,s,s.size());
	}
};
