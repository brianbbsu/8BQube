template<class T, class Info>
struct min_heap {
  priority_queue<pair<T, Info>, vector<pair<T, Info>>, greater<pair<T, Info>>> pq;
  T lazy = 0;
  void push(pair<T, Info> v) {
    pq.emplace(v.X - lazy, v.Y);
  }
  pair<T, Info> top() {
    return make_pair(pq.top().X + lazy, pq.top().Y);
  }
  void join(min_heap &rgt) {
    if (SZ(pq) < SZ(rgt.pq)) {
      swap(pq, rgt.pq);
      swap(lazy, rgt.lazy);
    }
    while (!rgt.pq.empty()) {
      push(rgt.top());
      rgt.pop();
    }
  }
  void pop() {
    pq.pop();
  }
  bool empty() {
    return pq.empty();
  }
  void add_lazy(T v) {
    lazy += v;
  }
};
