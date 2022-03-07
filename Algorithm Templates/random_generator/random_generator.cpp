#include <bits/stdc++.h>
using namespace std;

void string_generator(int n){
    srand(time(0));
    char ch;
    vector<char>V;
    /*for(int i=0;i<32;i++){
        ch = 'A'+i;
        cout<<ch<<endl;
    }*/
    V.push_back('A');
    V.push_back('B');
    V.push_back('C');
    V.push_back('E');
    string s= "";
    int idx;
    for(int i=0;i<n;i++){
        idx = rand()%V.size();
        s = s + V[idx];
    }
    cout<<s<<endl;
}

int main(void){
    string_generator(12);
}
