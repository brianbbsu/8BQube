#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp> // rb_tree
#include <ext/rope> // rope
using namespace __gnu_pbds;
using namespace __gnu_cxx; // rope
typedef __gnu_pbds::priority_queue<int> heap;
int main() {
  heap h1, h2; // max heap
  h1.push(1), h1.push(3), h2.push(2), h2.push(4);
  h1.join(h2); // h1 = {1, 2, 3, 4}, h2 = {};
  tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> st;
  tree<ll, ll, less<ll>, rb_tree_tag, tree_order_statistics_node_update> mp;
  for (int x : {0, 3, 20, 50}) st.insert(x);
  assert(st.order_of_key(3) == 1 && st.order_of_key(4) == 2);
  assert(*st.find_by_order(2) == 20 && *st.lower_bound(4) == 20);
  rope<char> *root[10]; // nsqrt(n)
  root[0] = new rope<char>();
  root[1] = new rope<char>(*root[0]);
  // root[1]->insert(pos, 'a');
  // root[1]->at(pos); 0-base
  // root[1]->erase(pos, size);
}
// __int128_t,__float128_t
// for (int i = bs._Find_first(); i < bs.size(); i = bs._Find_next(i));
