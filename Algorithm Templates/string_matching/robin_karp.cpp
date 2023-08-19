#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll multiplication(int power, ll base, ll M){
    if (power==1) return base%M;
    if (power%2 == 0) {
        ll res = multiplication(power/2, base, M)%M;
        return (res * res)%M;
    }
    if(power%2 == 1) {
        ll res = multiplication((power-1)/2, base, M)%M;
        return (((base%M) * res)%M * res)%M;
    }
}

ll hash_conversion(string s, ll base, ll M){
    ll p = 0;
    for(int i=0; i<s.size(); i++){
        p = ((base * p)%M + s[i]%M)%M;
    }
    return p;
}

void robin_karp(string P, string T, ll base, ll M){
    int m = P.size();
    ll factor = multiplication(m-1, base, M);
    ll pattern_hash = hash_conversion(P, base, M);
    vector<ll>t;
    ll text_hash = 0;
    for(int i=0;i<m;i++){
        // complete hasing for first index
        text_hash = ((base * text_hash)%M + T[i]%M)%M;
    }
    t.push_back(text_hash);
    ll val;
    ll k;
    for(int i=1;i<=T.size()-m;i++){
        val = ((base * (t[i-1]-(factor*T[i-1])%M))%M + T[i+m-1])%M;
        if (val<0) {
            // negative number modulus
            k=abs(val)/M+1;
            val = (val + k*M)%M;
        }
        t.push_back(val);
    }
    bool match;
    for(int i=0; i<=T.size()-m; i++){
        if(t[i] == pattern_hash) {
            //matched, critical matching
            match = true;
            for(int j=0;j<m;j++){
                if(T[i+j] == P[j]) continue;
                else {
                    match = false;
                    break;
                }
            }
            if(match == true) {
                cout<<i << " " << i+m-1<<endl;
            }
        }
    }
    return;
}

pair<string,string> input(){
    string T,P;
    cin>>T>>P;
    pair<string,string> p;
    p.first = T;
    p.second = P;
    return p;
}

int main(void){
    //freopen("in.txt", "r", stdin);
    pair<string,string> p = input();
    string T = p.first;
    string P = p.second;
    ll base = 26;
    ll M = 1000000000+7;
    robin_karp(P, T, base, M);
    return 0;
}
