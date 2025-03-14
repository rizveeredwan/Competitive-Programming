#include <bits/stdc++.h>
#include "random_generator.cpp"
using namespace std;

int main(void){
    srand(time(nullptr));
    vector<char> a = eng_letter_gen("upper"); 
    vector<char> b = eng_letter_gen("lower");
    vector<char>digits = eng_letter_gen("digit"); 
    a.insert(a.end(), b.begin(), b.end());  
    a.push_back(' '); 
    int n = 500;
    string prefix = "inception"; 
    vector<string>names;
    vector<string>phone; 
    int fix = 130; 
    for(int i=0; i<fix; i++){
        string one = random_string_gen(a, rand()%30+1); 
        string two = random_string_gen(a, rand()%40+1); 
        string fin = ""; 
        int ch = rand()%3; 
        if(ch == 0){
            fin = random_up_low(prefix, "upper") + one + two; 
        }
        else if(ch == 1){
            fin = one + random_up_low(prefix, "lower") + two; 
        }
        else {
            if(rand() % 2 == 0) fin = one + two + random_up_low(prefix, "lower"); 
            else fin = one + two + random_up_low(prefix, "upper"); 
        }
        names.push_back(fin);
    }
    shuffling_vector(names); 
    for(int i=0; i<(n-fix); i++){
        string fin = random_string_gen(a, 15); 
        names.push_back(fin); 
    }
    for(int i=0; i<n; i++){
        string temp=""; 
        if(rand()%2 == 0) {
            temp = "+880"; 
        }
        temp += random_string_gen(digits, 11); 
        phone.push_back(temp); 
    }
    freopen("IN.txt", "w", stdout);
    cout<<n<<endl;
    for(int i=0; i<n; i++){
        cout<<names[i]<<endl;
        cout<<phone[i]<<endl; 
    }
    cout<<prefix<<endl;
    return 0; 
}
