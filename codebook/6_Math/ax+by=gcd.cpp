pll exgcd(ll a, ll b) {
    if(b == 0) return pll(1, 0);
    else { 
        ll p = a / b;
        pll q = exgcd(b, a % b);
        return pll(q.Y, q.X - q.Y * p);
    }
}
