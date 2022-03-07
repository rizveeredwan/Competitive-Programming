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

vector<int> input_generation(int n, int min_value, int max_value) {
    srand(time(0));
    map<int,bool>M;
    vector<int>V;
    int value;
    auto it = M.begin();
    while (V.size() < n) {
        value = rand()%max_value+min_value;
        V.push_back(value);
        /*if (M.find(value) == M.end()) {
            M[value]=true;
            V.push_back(value);
        }*/
    }
    return V;
}

template<typename T> void print_vector(vector<T>V){
    for(int i=0; i<V.size(); i++){
        cout<<V[i]<<" ";
    }
    cout<<endl;
}


int main(void){
    //string_generator(12);
    vector<int> V = input_generation(10, 1, 70);
    print_vector(V);
}
