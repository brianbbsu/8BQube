double eps=1e-12;
struct P {
	double x,y,z;
	P(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
	P operator+(const P &b)const{return P(x+b.x,y+b.y,z+b.z);}
	P operator-(const P &b)const{return P(x-b.x,y-b.y,z-b.z);}
	P operator^(const P &b)const{return P(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}
	double operator*(const P&b)const{return x*b.x+y*b.y+z*b.z;}
};
double abs(P a){return sqrt(a*a);}
double absvol(const P a,const P b,const P c,const P d) {
    return abs(((b-a)^(c-a))*(d-a))/6;
}
struct convex3D {
static const int maxn=1010;
struct T{
    int a,b,c;
    bool res;
    T(){}
    T(int a,int b,int c,bool res=1):a(a),b(b),c(c),res(res){}
};
int n,m;
P p[maxn];
T f[maxn*8];
int id[maxn][maxn];
void init(int _n){n=_n,m=0;}
bool on(T &t,P &q){return ((p[t.c]-p[t.b])^(p[t.a]-p[t.b]))*(q-p[t.a])>eps;}
void meow(int q,int a,int b){
    int g=id[a][b];
    if(f[g].res){
        if(on(f[g],p[q]))dfs(q,g);
        else{
            id[q][b]=id[a][q]=id[b][a]=m;
            f[m++]=T(b,a,q,1);
        }
    }
}
void dfs(int p,int i){
    f[i].res=0;
    meow(p,f[i].b,f[i].a);
    meow(p,f[i].c,f[i].b);
    meow(p,f[i].a,f[i].c);
}
void operator()(){
    if(n<4)return;
    if([&](){
        for(int i=1;i<n;++i)if(abs(p[0]-p[i])>eps)return swap(p[1],p[i]),0;
        return 1;
    }() || [&](){
        for(int i=2;i<n;++i)if(abs((p[0]-p[i])^(p[1]-p[i]))>eps)return swap(p[2],p[i]),0;
        return 1;
    }() || [&](){
        for(int i=3;i<n;++i)if(abs(((p[1]-p[0])^(p[2]-p[0]))*(p[i]-p[0]))>eps)return swap(p[3],p[i]),0;
        return 1;
    }())return;
    for(int i=0;i<4;++i){
        T t((i+1)%4,(i+2)%4,(i+3)%4,1);
        if(on(t,p[i]))swap(t.b,t.c);
        id[t.a][t.b]=id[t.b][t.c]=id[t.c][t.a]=m;
        f[m++]=t;
    }
    for(int i=4;i<n;++i)for(int j=0;j<m;++j)if(f[j].res && on(f[j],p[i])){
        dfs(i,j);
        break;
    }
    int mm=m; m=0;
    for(int i=0;i<mm;++i)if(f[i].res)f[m++]=f[i];
}
bool same(int i,int j){
    return !(absvol(p[f[i].a],p[f[i].b],p[f[i].c],p[f[j].a])>eps || absvol(p[f[i].a],p[f[i].b],p[f[i].c],p[f[j].b])>eps || absvol(p[f[i].a],p[f[i].b],p[f[i].c],p[f[j].c])>eps);
}
int faces(){
    int r=0;
    for(int i=0;i<m;++i){
        int iden=1;
        for(int j=0;j<i;++j)if(same(i,j))iden=0;
        r+=iden;
    }
    return r;
}
}tb;
