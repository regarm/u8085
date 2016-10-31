#include <iostream>
#include <string>
#include <set>
using namespace std;
int main () {
    int N;
    cin >> N;
    int tc;
    cin >> tc;
    set<int> ss;
    while(tc--){
        string op;
        cin >> op;
        if(op == "PUT"){
            if((int)ss.size() == N){
                ss.erase(ss.begin());
            }
            int x;
            cin >> x;
            ss.insert(x);
        } else{
            if(!ss.empty()){
                set<int> :: iterator it = ss.end();
                --it;
                ss.erase(it);
            }
        }
    }
    cout << ss.size() << " ";
   // cout<< ss.size() + 1 << endl;
    // cout the size of set + 1.
    for(set<int> :: iterator it = ss.begin();it != ss.end();++it){
        cout << *it << " ";
    }
    return 0;
}
