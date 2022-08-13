char suit[4]={'C','D','H','S'},ranks[13]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
int rk[256];
/*
   for(int i=0;i<13;++i)
   rk[ranks[i]]=i;
   for(int i=0;i<4;++i)
   rk[suit[i]]=i;
   */
struct cards{
  vector<pii> v;
  int suit_count[4],hands;
  void reset(){v.clear(),FILL(suit_count,0),hands=-1;}
  void insert(char a,char b){//suit,rank
    ++suit_count[rk[a]];
    int flag=0;
    for(auto &i:v)
      if(i.Y==rk[b])
      {
        ++i.X,flag=1;
        break;
      }
    if(!flag) v.pb(pii(1,rk[b]));
  }
  void insert(string s){insert(s[0],s[1]);}
  void ready(){
    int Straight=0,Flush=(*max_element(suit_count,suit_count+4)==5);
    sort(ALL(v),[](ii a,ii b){return a>b;});
    if(SZ(v)==5&&v[0].Y==v[1].Y+1&&v[1].Y==v[2].Y+1&&v[2].Y==v[3].Y+1&&v[3].Y==v[4].Y+1)
      Straight=1;
    else if(SZ(v)==5&&v[0].Y==12&&v[1].Y==3&&v[2].Y==2&&v[3].Y==1&&v[4].Y==0)
      v[0].Y=3,v[1].Y=2,v[2].Y=1,v[1].Y=0,v[0].Y=-1,Straight=1;
    if(Straight&&Flush) hands=1;
    else if(v[0].X==4) hands=2;
    else if(v[0].X==3&&v[1].X==2) hands=3;
    else if(Flush) hands=4;
    else if(Straight) hands=5;
    else if(v[0].X==3) hands=6;
    else if(v[0].X==2&&v[1].X==2) hands=7;
    else if(v[0].X==2) hands=8;
    else hands=9;
  }
  bool operator>(const cards &a)const{
    if(hands==a.hands) return v>a.v;
    return hands<a.hands;
  }
};
