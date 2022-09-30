const int MAXM = 1000010;
struct SAM {
  int tot, root, lst, mom[MAXM], mx[MAXM];
  int nxt[MAXM][33], cnt[MAXM], in[MAXM];
  int newNode() {
    int res = ++tot;
    fill(nxt[res], nxt[res] + 33, 0);
    mom[res] = mx[res] = cnt[res] = in[res] = 0;
    return res;
  }
  void init() {
    tot = 0;
    root = newNode();
    mom[root] = 0, mx[root] = 0;
    lst = root;
  }
  void push(int c) {
    int p = lst;
    int np = newNode();
    mx[np] = mx[p] + 1;
    for (; p && nxt[p][c] == 0; p = mom[p])
      nxt[p][c] = np;
    if (p == 0) mom[np] = root;
    else {
      int q = nxt[p][c];
      if (mx[p] + 1 == mx[q]) mom[np] = q;
      else {
        int nq = newNode();
        mx[nq] = mx[p] + 1;
        for (int i = 0; i < 33; i++)
          nxt[nq][i] = nxt[q][i];
        mom[nq] = mom[q];
        mom[q] = nq;
        mom[np] = nq;
        for (; p && nxt[p][c] == q; p = mom[p])
          nxt[p][c] = nq;
      }
    }
    lst = np, cnt[np] = 1;
  }
  void push(char *str) {
    for (int i = 0; str[i]; i++)
      push(str[i] - 'a' + 1);
  }
  void count() {
    for (int i = 1; i <= tot; ++i)
      ++in[mom[i]];
    queue<int> q;
    for (int i = 1; i <= tot; ++i)
      if (!in[i]) q.push(i);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      cnt[mom[u]] += cnt[u];
      if (!--in[mom[u]])
        q.push(mom[u]);
    }
  }
} sam;
