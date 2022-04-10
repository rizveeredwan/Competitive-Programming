#include <bits/stdc++.h>
using namespace std;

int func(int a,int b){
    int value = a+b+abs(a-b);
    value = value/2;
    return value;
}

int main(void) {
    int a,b,c;
    cin>>a>>b>>c;
    int ans1 = func(a,b);
    ans1 = max(ans1, func(a,c));
    ans1 = max(ans1, func(b,c));
    cout<<ans1<<" eh o maior"<<endl;
    return 0;
}
