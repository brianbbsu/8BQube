vector<pdd> interCircle(pdd o1 ,double r1 ,pdd o2 ,double r2){
	if(abs(o1-o2)<max(r1,r2)-min(r1,r2)) return {};
	double d2=abs2(o1-o2);
	double d=sqrt(d2);
	if(d>r1+r2) return {};
	pdd u = (o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
	double A = sqrt((r1+r2+d)*(r1-r2+d)*(r1+r2-d)*(-r1+r2+d));
	pdd v = pdd(o1.Y-o2.Y,-o1.X+o2.X)*A/(2*d2);
	return {u+v, u-v};
}
