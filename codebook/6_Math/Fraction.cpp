struct fraction{
  ll n,d;
  fraction(const ll &_n=0,const ll &_d=1):n(_n),d(_d){
    ll t=__gcd(n,d);
    n/=t,d/=t;
    if(d<0) n=-n,d=-d;
  }
  fraction operator-()const{
    return fraction(-n,d);
  }
  fraction operator+(const fraction &b)const{
    return fraction(n*b.d+b.n*d,d*b.d);
  }
  fraction operator-(const fraction &b)const{
    return fraction(n*b.d-b.n*d,d*b.d);
  }
  fraction operator*(const fraction &b)const{
    return fraction(n*b.n,d*b.d);
  }
  fraction operator/(const fraction &b)const{
    return fraction(n*b.d,d*b.n);
  }
  void print(){
    cout << n;
    if(d!=1) cout << "/" << d;
  }
};
