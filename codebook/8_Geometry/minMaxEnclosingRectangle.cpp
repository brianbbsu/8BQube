pdd solve(vector<pll> &dots){
  vector<pll> hull;
  const double INF=1e18,qi=acos(-1)/2*3;
  cv.dots=dots;
  hull=cv.hull();
  double Max=0,Min=INF,deg;
  ll n=hull.size();
  hull.pb(hull[0]);
  for(int i=0,u=1,r=1,l;i<n;++i){
    pll nw=hull[i+1]-hull[i];
    while(cross(nw,hull[u+1]-hull[i])>cross(nw,hull[u]-hull[i]))
      u=(u+1)%n;
    while(dot(nw,hull[r+1]-hull[i])>dot(nw,hull[r]-hull[i]))
      r=(r+1)%n;
    if(!i) l=(r+1)%n;
    while(dot(nw,hull[l+1]-hull[i])<dot(nw,hull[l]-hull[i]))
      l=(l+1)%n;
    Min=min(Min,(double)(dot(nw,hull[r]-hull[i])-dot(nw,hull[l]-hull[i]))*cross(nw,hull[u]-hull[i])/abs2(nw));
    deg=acos((double)dot(hull[r]-hull[l],hull[u]-hull[i])/abs(hull[r]-hull[l])/abs(hull[u]-hull[i]));
    deg=(qi-deg)/2;
    Max=max(Max,(double)abs(hull[r]-hull[l])*abs(hull[u]-hull[i])*sin(deg)*sin(deg));
  }
  return pdd(Min,Max);
}
