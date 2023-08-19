#include <bits/stdc++.h>
using namespace std;

void solution1(){
    int n;
    cin>>n;
    map<int,int>M;
    int v;
    for(int i=0; i<n; i++){
        cin>>v;
        M[v]++;
    }
    map<int,int>::iterator it;
    int cnt = 0;
    for(it = M.begin(); it != M.end(); it++){
        if(it->first > 0 && (it->first)%2 == 0 && it->second == 1){
            cnt++;
        }
    }
    cout<<cnt<<endl;
    // Runtime Complexity: O(NlogN) due to map soring
    // Memory Complexity: O(N) size of Map
}

void solution2(){
    int n,v;
    cin>>n;
    vector<int>V;
    for(int i=0; i<n; i++){
        cin>>v;
        V.push_back(v);
    }
    sort(V.begin(), V.end());
    bool flag = 0;
    int cnt=0;
    for(int i=0; i<V.size(); i++){
        if(a[i] > 0 && a[i]%2 == 0) { // positive even number
            flag = 0; // no problem
            if((i+1)<n) {
                if(a[i+1] == a[i]) flag=1;
            }
            if((i-1) >= 0){
                if(a[i-1] == a[i]) flag=1;
            }
            if(flag == 0) cnt++;
        }
    }
    cout<<cnt<<endl;
    // Runtime Complexity: O(NlogN) due to map soring
    // Memory Complexity: O(N) size of Map

}

int main(void){

}
