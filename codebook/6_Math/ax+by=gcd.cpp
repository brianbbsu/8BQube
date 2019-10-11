pii gcd(int a,int b){
	if(b==0) return pii(1,0);
	else{ 
		int p=a/b;
		pii q=gcd(b,a%b);
		return MP(q.Y,q.X-q.Y*p);
	}
}
