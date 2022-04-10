#include <bits/stdc++.h>
using namespace std;

void func(int a){
    int hour = a/3600;
    a = a-hour*3600;
    int m = a/60;
    a = a - m*60;
    cout<<hour<<":"<<m<<":"<<a<<endl;
    return;
}

int main(void) {
    int a;
    cin>>a;
    func(a);
    return 0;
}
