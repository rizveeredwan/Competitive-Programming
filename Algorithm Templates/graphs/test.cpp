#include <bits/stdc++.h>
using namespace std;

/* Tested need reference to work with */

struct Test{
    int a;
    void update(){
        a = 20;
    }
};



int main(void){
    Test t;
    t.a = 100;
    cout<<t.a<<endl;
    t.update();
    cout<<t.a<<endl;
    return 0;
}
