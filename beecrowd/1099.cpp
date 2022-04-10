#include <bits/stdc++.h>
using namespace std;

void sum(int a, int b){
    int st = min(a,b);
    st++;
    int en = max(a,b);
    en--;
    int sum = 0;
    while(st<=en){
        if(st%2==1) sum+=st, st+=2;
        else st+=1;
    }
    cout<<sum<<endl;
    return;
}


void sum2(int a, int b){
    int st = min(a,b);
    st++;
    if(st%2 == 0) st++;
    int en = max(a,b);
    en--;
    if(en%2 == 0) en--;
    int sum = 0;
    if(st<=en){
        int gap=(en-st)/2;
        sum = (en+st) * (gap+1);
        sum = sum/2;
    }
    else {
        sum=0;
    }
    cout<<sum<<endl;
    return;
}

int main(void) {
    int a;
    cin>>a;
    int st,en;
    while(a != 0) {
        cin>>st>>en;
        sum2(st,en);
        a--;
    }
    return 0;
}
