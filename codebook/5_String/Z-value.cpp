int z[100005];
void Z_value(string s){
	int L=0,R=0;
	for(int i=1;i<SZ(s);i++){
		if(i>R){
			L=R=i;
			while(R<SZ(s) && s[R-L]==s[R]) ++R;
			z[i]=R-L;R--;
		}
		else{
			int k=i-L;
			if(z[k]<R-i+1) z[i]=z[k];
			else{
				L=i;
				while(R<SZ(s) && s[R-L]==s[R]) ++R;
				z[i]=R-L,R--;
			}
		}
	}
}
