#include <bits/stdc++.h>
using namespace std;

#define MAX 100


// function definition
template<typename T> void print_grid(T grid[MAX+1][MAX+1], int row, int col);

void string_generator(int n){
    // generation of random string
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

void grid_generator(int row, int col, int min_range, int max_range){
    srand(time(0));
    int value;
    int grid[MAX+1][MAX+1];
    int gap = max_range-min_range;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            value = rand()%gap+min_range;
            grid[i][j] = value;
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
    //string_generator(27);
    //vector<int> V = input_generation(10, 1, 70);
    //print_vector(V);
    grid_generator(3, 4, 1, 5);
}
