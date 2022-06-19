#include <bits/stdc++.h>
using namespace std;

#define MAX 505


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
    V.push_back('D');
    string s= "";
    int idx;
    for(int i=0;i<n;i++){
        idx = rand()%V.size();
        s = s + V[idx];
    }
    cout<<s<<endl;
    //cout<<s.size()<<endl;
}

vector<int> integer_generation(int n, int min_value, int max_value, bool repeat) {
    // integer number generation
    //srand(time(0));
    map<int,bool>M;
    vector<int>V;
    int value;
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

void grid_generator(int row, int col, int min_range, int max_range){
    int value;
    int grid[MAX+1][MAX+1];
    int gap = max_range-min_range;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            value = rand()%gap+min_range;
            grid[i][j] = value;
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
    //string_generator(1000);
    //vector<int> V = integer_generation(500, 1, 300);
    grid_generator(500, 500, 2, 50);
    //integer_generation(100000, 100, 4900, true);
}
