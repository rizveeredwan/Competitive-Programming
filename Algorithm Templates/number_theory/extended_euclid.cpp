#include <bits/stdc++.h>
using namespace std;

struct ExtEuclid{
    int _gcd,x,y;
};

ExtEuclid extended_euclid(int a, int b){
    // function to calculate ax + by = gcd(a,b);
    ExtEuclid temp;
    if (b == 0) {
        temp._gcd = a;
        temp.x = 1;
        temp.y = 0;
        return temp;
    }
    temp = extended_euclid(b, a%b);
    ExtEuclid temp2;
    temp2.y = temp.x - (a/b)*temp.y;
    temp2.x = temp.y;
    temp2._gcd = temp._gcd;
    return temp2;
}

int main(){
    int x,y;
    ExtEuclid temp;
    temp = extended_euclid(56, 15);
    cout<<temp._gcd<<" "<<temp.x<<" "<< temp.y << endl;
    return 0;
}
