vector<pdd> line_interCircle(const pdd &p1,const pdd &p2,const pdd &c,const double r){
  pdd ft=foot(p1,p2,c),vec=p2-p1;
  double dis=abs(c-ft);
  if(fabs(dis-r)<eps) return vector<pdd>{ft};
  if(dis>r) return {};
  vec=vec*sqrt(r*r-dis*dis)/abs(vec);
  return vector<pdd>{ft+vec,ft-vec};
}
