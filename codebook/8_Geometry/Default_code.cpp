typedef pair<double,double> pdd;
typedef pair<pdd,pdd> Line;
const double eps=1e-8;
pdd operator+(const pdd &a,const pdd &b)
{ return pdd(a.X+b.X,a.Y+b.Y);}
pdd operator-(const pdd &a,const pdd &b)
{ return pdd(a.X-b.X,a.Y-b.Y);}
pdd operator*(const pdd &a,const double &b)
{ return pdd(a.X*b,a.Y*b);}
pdd operator/(const pdd &a,const double &b)
{ return pdd(a.X/b,a.Y/b);}
double dot(const pdd &a,const pdd &b)
{ return a.X*b.X+a.Y*b.Y;}
double cross(const pdd &a,const pdd &b)
{ return a.X*b.Y-a.Y*b.X;}
double abs2(const pdd &a)
{ return dot(a,a);}
double abs(const pdd &a)
{ return sqrt(dot(a,a));}
int ori(const pdd &a,const pdd &b,const pdd &c){
	double res=cross(b-a,c-a);
	if(fabs(res)<eps) return 0;
	return res > 0 ? 1 : -1;
}
bool collinearity(const pdd &p1, const pdd &p2, const pdd &p3){
	return fabs(cross(p1-p3,p2-p3))<eps;
}
bool btw(const pdd &p1,const pdd &p2,const pdd &p3){
	if(!collinearity(p1,p2,p3)) return 0;
	return dot(p1-p3,p2-p3)<eps;
}
bool seg_intersect(const pdd &p1,const pdd &p2,const pdd &p3,const pdd &p4){
	int a123=ori(p1,p2,p3);
	int a124=ori(p1,p2,p4);
	int a341=ori(p3,p4,p1);
	int a342=ori(p3,p4,p2);
	if(a123==0 && a124==0)
		return btw(p1,p2,p3)||btw(p1,p2,p4)||btw(p3,p4,p1)||btw(p3,p4,p2);
	return a123*a124<=0&&a341*a342<=0;
}
pdd intersect(const pdd &p1,const pdd &p2,const pdd &p3,const pdd &p4){
	double a123=cross(p2-p1,p3-p1);
	double a124=cross(p2-p1,p4-p1);
	return (p4*a123-p3*a124)/(a123-a124);
}
pdd foot(const pdd &p1,const pdd &p2,const pdd &p3){
	pdd tmp=p2-p1;
	swap(tmp.X,tmp.Y),tmp.Y*=-1;
	return intersect(p1,p2,p3,p3+tmp);
}
