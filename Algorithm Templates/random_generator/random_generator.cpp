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

vector<ll> integer_generation(int n, ll min_value, ll max_value, bool repeat) {
    // integer number generation
    //srand(time(0));
    map<ll,bool>M;
    vector<ll>V;
    ll value;
    auto it = M.begin();
    while (V.size() < n) {
        value = rand()%max_value+min_value;
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
    print_vector(V);
    return V;
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


int main(void){
    freopen("in.txt", "w", stdout);
    // it is enough to write in main function once: the seeding
    srand(time(nullptr));
    //string_generator(30);
    //vector<ll> V = integer_generation(1, 1000000000000000, 100000000000000000, true);
    //map<int, bool>canceled;
    //canceled[0]=true;
    //grid_generator(12, 12, 0, 100, canceled, true);
    //integer_generation(100000, 100, 4900, true);
    int n,k;
    n=100;
    k=100;
    cout<<n<<" "<<k<<endl;
    for(int i=1; i<=n; i++){
        vector<ll> V = integer_generation(k, -2, -2, true);
    }
    return 0;
}
