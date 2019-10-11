//paring heap
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/priority_queue.hpp>
typedef __gnu_pbds::priority_queue<int> heap;
int main(){
    heap h1,h2;
    h1.push(1); h1.push(3);
    h2.push(2); h2.push(4);
    h1.join(h2);
    cout<<h1.size()<< '\n';
    cout<<h2.size()<< '\n';
}

//rb_tree
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
using namespace std;
using namespace __gnu_pbds;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> st;
    tree<ll,ll,less<ll>,rb_tree_tag,tree_order_statistics_node_update> mp;
    
    st.insert(0);
    st.insert(2);
    st.insert(3);
    st.insert(4);
    cout<<*st.find_by_order(2)<<endl;
    cout<<st.order_of_key(1)<<endl;
}

//__int128_t
__int128_t,__float128_t
