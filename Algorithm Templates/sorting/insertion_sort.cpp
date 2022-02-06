#include <bits/stdc++.h>
using namespace std;


template <typename T> vector<T> insertion_sort(vector<T> v){
    T temp;
    for(int i=0; i<v.size(); i++){
        for(int j=i-1; j>=0 ;j--){
            // comparing with the previous value
            if (v[j+1] < v[j]) {
                temp = v[j+1];
                v[j+1] = v[j];
                v[j] = temp;
            }
            else break;
        }
    }
    return v;
}

template <typename T> void print_vector(vector<T> v){
    for(int i =0; i<v.size(); i++){
        cout<<v[i]<< " ";
    }
    cout<<endl;
}

int main(void){
    vector<int>v = {10, 7, 1, 12, 9, 4, 3};
    print_vector(v);
    v = insertion_sort(v);
    print_vector(v);

    vector<string>s = {"abc", "aa", "akm", "a"};
    print_vector(s);
    s = insertion_sort(s);
    print_vector(s);

    return 0;
}
