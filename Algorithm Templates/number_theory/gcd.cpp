#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
    int rem;
    while(1){
        rem=a%b;
        cout<<a<<" "<<b<<" "<<rem<<" "<<a/b<<endl;
        if(rem == 0) return b;
        a=b;
        b=rem;
    }
    if(a==0) return b;
    if(b==0) return a;
}

int main(void){
    int a,b;
    cin>>a>>b;
    int value = gcd(a,b);
    cout<<value<<endl;
    return 0;
}
