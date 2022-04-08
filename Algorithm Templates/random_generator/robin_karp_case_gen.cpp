#include <bits/stdc++.h>
using namespace std;

vector<string> string_gen(int patt_len){
    queue<string>Q;
    string temp;
    char c;
    for(int i='a';i<='f';i++){
        temp = i;
        Q.push(temp);
    }
    string s;
    vector<string>options;
    while(Q.empty() != true) {
        s=Q.front();
        cout<<s<<" "<<s.size()<<endl;
        Q.pop();
        if(s.size() >= patt_len) {
            options.push_back(s);
            continue;
        }
        for(int i='a';i<='f';i++){
            temp = s+(char)i;
            Q.push(temp);
        }
    }
    return options;
}

int hash_value_gen(string s, int base, int M){
    int res = 0;
    int base_add = 1;
    for(int i=s.size()-1; i >= 0; i--){
        res = (res + (base_add * s[i])%M)%M;
        base_add = (base_add * base)%M;
    }
    return res;
}

vector<int> numeric_value_gen(vector<string> options, int base, int M) {
    vector<int>all_result;
    int hash_value;
    for(int i=0; i<options.size(); i++){
        hash_value = hash_value_gen(options[i], base, M);
        all_result.push_back(hash_value);
    }
    return all_result;
}

void case_gen(int patt_len, int base, int M){
    vector<string>options =  string_gen(patt_len);
    for(int i=0;i<options.size();i++) cout<<i<<" "<<options[i]<<endl;
    vector<int>all_result = numeric_value_gen(options, base, M);
    int conflict_count = 0;
    map<string,vector<string>>conf_string;
    for(int i=0;i<all_result.size();i++){
        for(int j=i+1; j<all_result.size();j++){
            if(all_result[i] == all_result[j]) {
                conflict_count++;
                cout<<"conflict "<<conflict_count<<" "<<options[i]<<" "<<options[j]<<" ("<<all_result[i]<<")"<<endl;
                if(conf_string.find(options[i]) == conf_string.end()){
                    vector<string>temp;
                    conf_string[options[i]] = temp;
                }
                conf_string[options[i]].push_back(options[j]);
            }
        }
    }
    cout<<options.size()<<endl;
    if(conf_string.find("bba") != conf_string.end()){
        for(int i=0; i<conf_string["bba"].size(); i++){
            cout<<conf_string["bba"][i]<<endl;
        }
    }
    // ab bba//issue ab bcf//issue aba caf//issue
    // bcf
}


int main(void){
    case_gen(3,2,7);
}
