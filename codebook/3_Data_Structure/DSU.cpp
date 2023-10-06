struct DSU {
  vector<int> arr;
  DSU(int n = 0): arr(n) {
    iota(ALL(arr), 0);
  }
  int boss(int x) {
    if (arr[x] == x) return x;
    return arr[x] = boss(arr[x]);
  }
  bool Union(int x, int y) {
    x = boss(x), y = boss(y);
    if (x == y) return 0;
    arr[y] = x;
    return 1;
  }
};
