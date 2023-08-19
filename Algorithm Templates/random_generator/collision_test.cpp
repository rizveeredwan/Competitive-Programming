#include <bits/stdc++.h>
using namespace std;

int hash_val(string T, int st, int len, int B, int M){
    int value = 0;
    bool flag=false;
    if ((st+len-1) < T.size()){
        for(int i=st; i<st+len && i<T.size(); i++){
            value = (value%M * B%M + T[i]%M)%M;
        }
        return value;
    }
    else return -1;
}
/*
aafbfccce
2 11 3
3 7 3
*/


int main(void){
    string T;
    cin>>T;
    int B,M,len;
    cin>>B>>M>>len;
    int value = 0;
    for(int i=0; i<T.size(); i++){
        cout<<i<<" "<<hash_val(T,i,len, B, M)<<endl;
    }
    return 0;
}
