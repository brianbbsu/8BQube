#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

const int MAXC = 200005;
const ll INF = 1e18;

struct node {
  ll sum;
  ll mx, mxcnt, smx;
  ll mi, micnt, smi;
  ll lazymax, lazymin, lazyadd;
  node(ll k = 0)
    : sum(k), mx(k), mxcnt(1), smx(-INF), mi(k),
      micnt(1), smi(INF), lazymax(-INF), lazymin(INF),
      lazyadd(0) {}
  node operator+(const node &a) const {
    node rt;
    rt.sum = sum + a.sum;
    rt.mx = max(mx, a.mx);
    rt.mi = min(mi, a.mi);
    if (mx == a.mx) {
      rt.mxcnt = mxcnt + a.mxcnt;
      rt.smx = max(smx, a.smx);
    } else if (mx > a.mx) {
      rt.mxcnt = mxcnt;
      rt.smx = max(smx, a.mx);
    } else {
      rt.mxcnt = a.mxcnt;
      rt.smx = max(mx, a.smx);
    }
    if (mi == a.mi) {
      rt.micnt = micnt + a.micnt;
      rt.smi = min(smi, a.smi);
    } else if (mi < a.mi) {
      rt.micnt = micnt;
      rt.smi = min(smi, a.mi);
    } else {
      rt.micnt = a.micnt;
      rt.smi = min(mi, a.smi);
    }
    rt.lazymax = -INF;
    rt.lazymin = INF;
    rt.lazyadd = 0;
    return rt;
  }
} seg[MAXC << 2];

ll a[MAXC];

void give_tag_min(int rt, ll t) {
  if (t >= seg[rt].mx) return;
  seg[rt].lazymin = t;
  seg[rt].lazymax = min(seg[rt].lazymax, t);
  seg[rt].sum -= seg[rt].mxcnt * (seg[rt].mx - t);
  if (seg[rt].mx == seg[rt].smi) seg[rt].smi = t;
  if (seg[rt].mx == seg[rt].mi) seg[rt].mi = t;
  seg[rt].mx = t;
}

void give_tag_max(int rt, ll t) {
  if (t <= seg[rt].mi) return;
  seg[rt].lazymax = t;
  seg[rt].sum += seg[rt].micnt * (t - seg[rt].mi);
  if (seg[rt].mi == seg[rt].smx) seg[rt].smx = t;
  if (seg[rt].mi == seg[rt].mx) seg[rt].mx = t;
  seg[rt].mi = t;
}

void give_tag_add(int l, int r, int rt, ll t) {
  seg[rt].lazyadd += t;
  if (seg[rt].lazymax != -INF) seg[rt].lazymax += t;
  if (seg[rt].lazymin != INF) seg[rt].lazymin += t;
  seg[rt].mx += t;
  if (seg[rt].smx != -INF) seg[rt].smx += t;
  seg[rt].mi += t;
  if (seg[rt].smi != INF) seg[rt].smi += t;
  seg[rt].sum += (ll)(r - l + 1) * t;
}

void tag_down(int l, int r, int rt) {
  if (seg[rt].lazyadd != 0) {
    int mid = (l + r) >> 1;
    give_tag_add(l, mid, rt << 1, seg[rt].lazyadd);
    give_tag_add(
      mid + 1, r, rt << 1 | 1, seg[rt].lazyadd);
    seg[rt].lazyadd = 0;
  }
  if (seg[rt].lazymin != INF) {
    give_tag_min(rt << 1, seg[rt].lazymin);
    give_tag_min(rt << 1 | 1, seg[rt].lazymin);
    seg[rt].lazymin = INF;
  }
  if (seg[rt].lazymax != -INF) {
    give_tag_max(rt << 1, seg[rt].lazymax);
    give_tag_max(rt << 1 | 1, seg[rt].lazymax);
    seg[rt].lazymax = -INF;
  }
}

void build(int l, int r, int rt) {
  if (l == r) return seg[rt] = node(a[l]), void();
  int mid = (l + r) >> 1;
  build(l, mid, rt << 1);
  build(mid + 1, r, rt << 1 | 1);
  seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
}

void modifymax(
  int L, int R, int l, int r, int rt, ll t) {
  if (L <= l && R >= r && t < seg[rt].smi)
    return give_tag_max(rt, t);
  if (l != r) tag_down(l, r, rt);
  int mid = (l + r) >> 1;
  if (L <= mid) modifymax(L, R, l, mid, rt << 1, t);
  if (R > mid)
    modifymax(L, R, mid + 1, r, rt << 1 | 1, t);
  seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
}

void modifymin(
  int L, int R, int l, int r, int rt, ll t) {
  if (L <= l && R >= r && t > seg[rt].smx)
    return give_tag_min(rt, t);
  if (l != r) tag_down(l, r, rt);
  int mid = (l + r) >> 1;
  if (L <= mid) modifymin(L, R, l, mid, rt << 1, t);
  if (R > mid)
    modifymin(L, R, mid + 1, r, rt << 1 | 1, t);
  seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
}

void modifyadd(
  int L, int R, int l, int r, int rt, ll t) {
  if (L <= l && R >= r)
    return give_tag_add(l, r, rt, t);
  if (l != r) tag_down(l, r, rt);
  int mid = (l + r) >> 1;
  if (L <= mid) modifyadd(L, R, l, mid, rt << 1, t);
  if (R > mid)
    modifyadd(L, R, mid + 1, r, rt << 1 | 1, t);
  seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
}

ll query(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) return seg[rt].sum;
  if (l != r) tag_down(l, r, rt);
  int mid = (l + r) >> 1;
  if (R <= mid) return query(L, R, l, mid, rt << 1);
  if (L > mid)
    return query(L, R, mid + 1, r, rt << 1 | 1);
  return query(L, R, l, mid, rt << 1) +
    query(L, R, mid + 1, r, rt << 1 | 1);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  build(1, n, 1);
  while (m--) {
    int k, x, y;
    ll t;
    cin >> k >> x >> y, ++x;
    if (k == 0) cin >> t, modifymin(x, y, 1, n, 1, t);
    else if (k == 1)
      cin >> t, modifymax(x, y, 1, n, 1, t);
    else if (k == 2)
      cin >> t, modifyadd(x, y, 1, n, 1, t);
    else cout << query(x, y, 1, n, 1) << "\n";
  }
}
