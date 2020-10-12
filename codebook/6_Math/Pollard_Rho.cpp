// does not work when n is prime
ll f(ll x,ll mod){ return add(mul(x,x,mod),1,mod); }
ll pollard_rho(ll n){
  if(!(n&1)) return 2;
  while(1){
    ll y=2,x=rand()%(n-1)+1,res=1;
    for(int sz=2;res==1;y=x,sz*=2)
      for(int i=0;i<sz&&res<=1;++i)
        x=f(x,n),res=__gcd(abs(x-y),n);
    if(res!=0&&res!=n) return res;
  }
}
