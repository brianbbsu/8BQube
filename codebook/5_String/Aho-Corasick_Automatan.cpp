const int len = 400000, sigma = 26;
struct AC_Automatan {
  int nx[len][sigma], fl[len], cnt[len], pri[len], top;
  int newnode() {
    fill(nx[top], nx[top] + sigma, -1);
    return top++;
  }
  void init() { top = 1, newnode(); }
  int input(
    string &s) { // return the end_node of string
    int X = 1;
    for (char c : s) {
      if (!~nx[X][c - 'a']) nx[X][c - 'a'] = newnode();
      X = nx[X][c - 'a'];
    }
    return X;
  }
  void make_fl() {
    queue<int> q;
    q.push(1), fl[1] = 0;
    for (int t = 0; !q.empty();) {
      int R = q.front();
      q.pop(), pri[t++] = R;
      for (int i = 0; i < sigma; ++i)
        if (~nx[R][i]) {
          int X = nx[R][i], Z = fl[R];
          for (; Z && !~nx[Z][i];) Z = fl[Z];
          fl[X] = Z ? nx[Z][i] : 1, q.push(X);
        }
    }
  }
  void get_v(string &s) {
    int X = 1;
    fill(cnt, cnt + top, 0);
    for (char c : s) {
      while (X && !~nx[X][c - 'a']) X = fl[X];
      X = X ? nx[X][c - 'a'] : 1, ++cnt[X];
    }
    for (int i = top - 2; i > 0; --i)
      cnt[fl[pri[i]]] += cnt[pri[i]];
  }
};
