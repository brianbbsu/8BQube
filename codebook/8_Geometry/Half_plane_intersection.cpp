bool isin( Line l0, Line l1, Line l2 ){
  // Check inter(l1, l2) in l0
  pdd p = intersect(l1.X,l1.Y,l2.X,l2.Y);
  return cross(l0.Y - l0.X,p - l0.X) > eps;
}
/* If no solution, check: 1. ret.size() < 3
 * Or more precisely, 2. interPnt(ret[0], ret[1])
 * in all the lines. (use (l.Y - l.X) ^ (p - l.X) > 0
 */
/* --^-- Line.X --^-- Line.Y --^-- */
vector<Line> halfPlaneInter(vector<Line> lines){
  int sz = lines.size();
  vector<double> ata(sz),ord(sz);
  for(int i=0; i<sz; ++i) {
    ord[i] = i;
    pdd d = lines[i].Y - lines[i].X;
    ata[i] = atan2(d.Y, d.X);
  }
  sort(ord.begin(), ord.end(), [&](int i,int j){
      if( fabs(ata[i] - ata[j]) < eps )
      return (cross(lines[i].Y-lines[i].X, 
            lines[j].Y-lines[i].X))<0;
      return ata[i] < ata[j];
      });
  vector<Line> fin;
  for (int i=0; i<sz; ++i)
    if (!i || fabs(ata[ord[i]] - ata[ord[i-1]]) > eps)
      fin.pb(lines[ord[i]]);
  deque<Line> dq;
  for (int i=0; i<SZ(fin); i++){
    while(SZ(dq)>=2&&!isin(fin[i],dq[SZ(dq)-2],dq.back())) 
      dq.pop_back();
    while(SZ(dq)>=2&&!isin(fin[i],dq[0],dq[1]))
      dq.pop_front();
    dq.push_back(fin[i]);
  }
  while(SZ(dq)>=3&&!isin(dq[0],dq[SZ(dq)-2],dq.back()))
    dq.pop_back();
  while(SZ(dq)>=3&&!isin(dq.back(), dq[0], dq[1])) 
    dq.pop_front();
  vector<Line> res(ALL(dq));
  return res;
}
