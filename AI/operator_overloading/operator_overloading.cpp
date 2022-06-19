#include <bits/stdc++.h>
using namespace std;

struct TicTacToeState{
    char arr[10] = {'X', 'X', 'X', 'X', 'X', 'X' , 'X', 'X', 'X'};
    bool operator == (const TicTacToeState & a) const {
        // with the base element (this): we are going to compare variable a
        for(int i=0; i<9; i++){
            if(a.arr[i]>arr[i] || a.arr[i]<arr[i]) return false; // means that they are not same
        }
        return true; // means they are same
    }
};

struct CompareStateStyle1{
    int v; // elements of the state
    bool operator < (const CompareStateStyle1  a) const {
        // overloading operator <
        // with the base element (this): we are going to compare variable a
        if(v < a.v) return true; // main one is small -> true for <
        return false; // other wise false
    }
};




int main(void){
    // Example 1
    TicTacToeState s;
    TicTacToeState s1,s2;
    s2.arr[0] = '0';
    cout<<(s == s1) << endl; // will return true (>0)
    cout<<(s == s2) << endl; // will return false (0)

    // Example 2
    CompareStateStyle1 c1,c2;
    c1.v = 10;
    c2.v = 20;
    cout<< (c1<c2) << endl;
    map<CompareStateStyle1, int> M1;
    M1[c1] = 89;
    cout<<M1[c1]<<endl;
    M1[c2] = 95;
    cout<<M1[c1]<<endl;

}
