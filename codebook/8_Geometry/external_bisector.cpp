pdd external_bisector(pdd p1,pdd p2,pdd p3){//213
  pdd L1=p2-p1,L2=p3-p1;
  L2=L2*abs(L1)/abs(L2);
  return L1+L2;
}
