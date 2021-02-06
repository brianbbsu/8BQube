// only works for integer coordinates!!

bool Flag; // 0: insert Line, 1: lower_bound x
template<class val = ll, class compare = less<val>> // sort lines with comp
struct DynamicConvexTrick{
  static const ll minx = 0, maxx = ll(1e9) + 5;
  static compare comp;
  struct Line{
    val a, b, l, r; // line ax + b in [l, r]
    Line(val _a, val _b, val _l = minx, val _r = maxx):a(_a), b(_b), l(_l), r(_r){}
    val operator () (val x) const {
      return a * x + b;
    }
  };
  struct cmp{
    bool operator () (const Line a, const Line b){
      if(Flag == 0)return comp(a.a, b.a);
      return a.r < b.l;
    }
  };
  inline val idiv(val a, val b){
    return a / b - (a % b && a < 0 ^ b < 0);
  }
  set<Line, cmp> st;
  void ins(val a, val b){
    Flag = 0;
    Line L(a, b);
    auto it = st.lower_bound(L);
    if(it != st.begin() && it != st.end())
      if(!comp((*prev(it))(it->l - 1), L(it->l - 1)) && !comp((*it)(it->l), L(it->l)))
        return;
    while(it != st.end()){
      if(it->a == L.a && !comp(it->b, L.b))return;
      if(comp((*it)(it->r), L(it->r)))it = st.erase(it);
      else{
        Line M = *it;
        st.erase(it);
        L.r = max(idiv(L.b - M.b, M.a - L.a), minx);
        M.l = L.r + 1;
        it = st.insert(M).X;
        break;
      }
    }
    while(it != st.begin()){
      auto pit = prev(it);
      if(comp((*pit)(pit->l), L(pit->l)))st.erase(pit);
      else{
        Line M = *pit;
        st.erase(pit);
        M.r = min(idiv(L.b - M.b, M.a - L.a), maxx - 1);
        L.l = M.r + 1;
        st.insert(M);
        break;
      }
    }
    st.insert(L);
  }
  val operator () (val x){
    Flag = 1;
    auto it = st.lower_bound({0, 0, x, x});
    return (*it)(x);
  }
};

DynamicConvexTrick<> DCT;
