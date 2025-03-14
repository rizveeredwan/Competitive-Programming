#include <bits/stdc++.h>
using namespace std;

#define MAX 505

typedef long long int ll;


// function definition
template<typename T> void print_grid(T grid[MAX+1][MAX+1], int row, int col);
template<typename T> void print_vector(vector<T>V);



void string_generator(int n){
    // generation of random string
    char ch;
    vector<char>V;
    /*for(int i=0;i<32;i++){
        ch = 'A'+i;
        cout<<ch<<endl;
    }*/
    V.push_back('A');
    V.push_back('B');
    V.push_back('C');
    //V.push_back('D');
    string s= "";
    int idx;
    for(int i=0;i<n;i++){
        idx = rand()%V.size();
        s = s + V[idx];
    }
    cout<<s<<endl;
    //cout<<s.size()<<endl;
}

vector<char> eng_letter_gen(string s){
    vector<char>opt; 
    if(s == "upper" || s == "lower") {
        for(int i=0; i<26; i++){
            if(s == "upper") opt.push_back(i+'A');
            else if(s == "lower") opt.push_back(i+'a');
        }
    }
    if(s == "digit"){
        for(int i=0; i<=9; i++){
            opt.push_back(i+'0'); 
        }
    }
    return opt; 
}

string random_up_low(string s, string cat){
    for(int i=0; i<s.size(); i++){
        if(cat == "upper" && s[i] >= 'a' && s[i] <= 'z') s[i] = s[i]-'a' + 'A';  
        if(cat == "lower" && s[i] >= 'A' && s[i] <= 'Z')  s[i] = s[i]-'A' + 'a';  
    }
    return s; 
}

string random_string_gen(vector<char>char_choices, int n) {
    int idx; 
    string s = ""; 
    for(int i=0; i<n; i++){
        idx = rand()%char_choices.size(); 
        s = s + char_choices[idx]; 
    }
    return s; 
}

vector<ll> integer_generation(int n, ll min_value, ll max_value, bool repeat) {
    // integer number generation
    //srand(time(0));
    //cout<<"min "<<min_value<<" "<<max_value<<endl;
    map<ll,bool>M;
    vector<ll>V;
    ll value;
    auto it = M.begin();
    while (V.size() < n) {
        value = rand()% max_value+min_value;
        if (repeat == true) {
            V.push_back(value);
        }
        else {
            if (M.find(value) == M.end()) {
            M[value]=true;
            V.push_back(value);
            }
        }
    }
    //print_vector(V);
    return V;
}

vector<ll> copy_same_val(ll val, int sz){
    vector<ll>temp;
    for(int i=0; i<sz; i++){
        temp.push_back(val);
    }
    return temp;
}

void grid_generator(int row, int col, int min_range, int max_range, map<int,bool>canceled, bool repeat_allow){
    int value;
    int grid[MAX+1][MAX+1];
    int gap = max_range-min_range;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            while (true){
                value = rand()%gap+min_range;
                if(canceled.find(value) == canceled.end()) {
                    grid[i][j] = value; // not canceled value
                    if(repeat_allow) {}
                    else { // no repeatition allowed
                        canceled[value] = true; // to cancel repeating value
                    }
                    break;
                }
            }
            //cout<<i<< " "<<j<<" "<< value << " value"<<endl;
        }
    }
    print_grid(grid, row, col);
    return;
}

template<typename T> void print_grid(T grid[MAX+1][MAX+1], int row, int col) {
    // printing grid
    cout<<row<<" "<<col<<endl;;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
}

template<typename T> void print_vector(vector<T>V){
    // printing any sort of vector
    for(int i=0; i<V.size(); i++){
        cout<<V[i]<<" ";
    }
    cout<<endl;
}

template<typename T> void print_multiple_vectors(vector<vector<T>>V){
    for(int i=0; i<V.size(); i++){
        for(int j=0; j<V[i].size(); j++){
            if(i == (V.size()-1) && j == (V[i].size()-1)){
                cout<<V[i][j];
            }
            else cout<<V[i][j]<<" ";
        }
    }
    cout<<endl;
}

template<typename T> vector<T> shuffling_vector(vector<T>myVector) {
    // Seed the random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // Shuffle the vector
    std::shuffle(myVector.begin(), myVector.end(), rng);
    return myVector; 
}


/*
int main(void){
    freopen("in.txt", "w", stdout);
    // it is enough to write in main function once: the seeding
    srand(time(nullptr));
    //string_generator(30);
    int sz = 100000;
    cout<<sz<< " "<< 400 << endl;
    vector<ll> V1 = copy_same_val(1000, 300);
    vector<ll> V2 = copy_same_val(323, 400);
    vector<ll> V3 = copy_same_val(424, 400);
    vector<ll> V4 = integer_generation(sz-400-400-300, 543, 100000000, true);
    vector<vector<ll>>V;
    V.push_back(V1);
    V.push_back(V2);
    V.push_back(V3);
    V.push_back(V4);
    //cout<<"WHAT THE "<<V[1][0]<<endl;
    print_multiple_vectors(V);
    //cout<<rand()%V.size()+1<<endl;
    //map<int, bool>canceled;
    //canceled[0]=true;
    //grid_generator(4, 4, 1, 7, canceled);
}
*/