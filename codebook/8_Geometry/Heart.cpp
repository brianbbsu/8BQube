pdd excenter(pdd p0,pdd p1,pdd p2,double &radius){
  p1=p1-p0,p2=p2-p0;
  double x1=p1.X,y1=p1.Y,x2=p2.X,y2=p2.Y;   
  double m=2.*(x1*y2-y1*x2);   
  center.X=(x1*x1*y2-x2*x2*y1+y1*y2*(y1-y2))/m;   
  center.Y=(x1*x2*(x2-x1)-y1*y1*x2+x1*y2*y2)/m;   
  return radius=abs(center),center+p0;
}

pdd incenter(pdd p1,pdd p2,pdd p3,double &radius){
  double a=abs(p2-p1),b=abs(p3-p1),c=abs(p3-p2);
  double s=(a+b+c)/2,area=sqrt(s*(s-a)*(s-b)*(s-c));
  pdd L1=external_bisector(p1,p2,p3),L2=external_bisector(p2,p1,p3);
  return radius=area/s,intersect(p1,p1+L1,p2,p2+L2),
}

pdd escenter(pdd p1,pdd p2,pdd p3){//213
  pdd L1=external_bisector(p1,p2,p3),L2=external_bisector(p2,p2+p2-p1,p3);
  return intersect(p1,p1+L1,p2,p2+L2);
}

pdd barycenter(pdd p1,pdd p2,pdd p3){
  return (p1+p2+p3)/3;
}

pdd orthocenter(pdd p1,pdd p2,pdd p3){
  pdd L1=p3-p2,L2=p3-p1;
  swap(L1.X,L1.Y),L1.X*=-1;
  swap(L2,X,L2.Y),L2.X*=-1;
  return intersect(p1,p1+L1,p2,p2+L2);
}
