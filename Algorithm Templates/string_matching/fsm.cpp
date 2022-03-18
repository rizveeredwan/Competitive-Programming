#include <bits/stdc++.h>
using namespace std;

vector<char> calc_alphabets(string p){
    sort(p.begin(), p.end());
    vector<char>v;
    for(int i=0;i<p.size();i++){
        if(i == 0) v.push_back(p[i]);
        else if(v[v.size()-1] != p[i]) v.push_back(p[i]);
    }
    return v;
}

template<typename T> print_vector(vector<T> v){
    for(int i=0; i<v.size(); i++) cout<<v[i]<< " ";
    cout<<endl;
}
 vector<char> shift_string(string p){
    vector<char>v;
    v.push_back(NULL);
    for(int i=0;i<p.size();i++) v.push_back(p[i]);
    return v;
 }

map<int,map<char,int>> calculate_transition_function(string p, string t){
    vector<char>alphabets = calc_alphabets(p+t);
    //print_vector(alphabets);
    vector<char>modified_p = shift_string(p);
    int m = p.size();
    int k;
    bool match;
    map<int,map<char,int>>delta;
    int st;
    for(int q=0; q <= m ; q++){
        // for each index
        for(int a = 0; a < alphabets.size(); a++){
            // for each alphabet
            k = 1 + min(m,q+1);
            if (k>=modified_p.size()) k--; // for wrong place access
            while(true){
                // starting from max suffix with prefix match within p_k and p_q+a
                // p_k is first k letters[1...k]
                if (k==0) {
                    break;
                }
                if (alphabets[a] == modified_p[k]) {
                    match = true;
                    st = k;
                    for(int j=1; j<=k-1; j++){
                        if(modified_p[j] == modified_p[q-k+j+1]) continue;
                        else {
                            match = false;
                            k--;
                            break;
                        }
                    }
                    if(match == true) break;
                }
                else k--;
            }
            //cout<< "q " << q << " " << k << endl;
            if (delta.find(q) == delta.end()) {
                map<char,int>temp;
                delta[q] = temp;
            }
            if (delta[q].find(alphabets[a]) == delta[q].end()) {
                delta[q][alphabets[a]] = k;
                cout<<q << " "<< alphabets[a] << " " << k << endl;
            }
        }
    }
    return delta;
}

void search_in_text(string t, map<int,map<char,int>>delta, int final_state){
    int current_state = 0;
    for(int i=0; i<t.size(); i++){
        current_state = delta[current_state][t[i]];
        if(current_state == final_state) {
            // found one occurrence
            cout<<"found within [" << i-final_state+1<< "," <<i<<"] "<<endl;
        }
    }
    return;
}

int main(void){
    freopen("in.txt", "r", stdin);
    string t,p;
    cin>>t>>p;
    map<int,map<char,int>>delta = calculate_transition_function(p,t);
    search_in_text(t, delta, p.size());
    return 0;
}
