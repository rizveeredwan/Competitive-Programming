#include <bits/stdc++.h>
using namespace std;
#define MAX 501
#define MAX_INF 1000000000

int dp[MAX+1][MAX+1];
int grid[MAX+1][MAX+1];
int dx[] = {-1, -1, -1, 0, 0};
int dy[] = {0, 1, -1, 1, -1};
int pos_moves = 5;

pair<int,int> input(){
    int m,n;
    cin>>m>>n;
    for(int i=0; i<m;i++){
        for(int j=0; j<n; j++){
            cin>>grid[i][j];
            cout<<"grid "<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    pair<int,int> p;
    p.first = m;
    p.second = n;
    return p;
}

bool bounding_check(int i, int j, int row, int col) {
    if (i<0 || i>=row) return false;
    if (j<0 || j>=col) return false;
    return true;
}

int hill_climbing(int i, int j, int row, int col){
    cout<<" i " << i << " " << j << endl;
    int x,y;
    /*if (i == 0) {
        dp[i][j] = grid[i][j];
        return grid[i][j];
    }*/
    if (i < 0) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    int res = MAX_INF;
    for(int k=0; k<pos_moves; k++){
        x = i+dx[k];
        y = j+dy[k];
        if (bounding_check(x, y, row, col) == true) {
            res = min(res, grid[i][j]+hill_climbing(x, y, row, col));
        }
    }
    dp[i][j] = res;
    return dp[i][j];
}

void print_dp_table(int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(void){
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    pair<int,int> p = input();
    int res = MAX_INF;
    memset(dp, -1, sizeof(dp));
    //cout<<dp[0][0] << dp[0][2] << endl;
    /*
    for(int i=0;i<p.second;i++){
        res = min(res, hill_climbing(p.first-1, i, p.first, p.second));
    }*/
    int st=3, en=1;
    res = hill_climbing(st, en, p.first, p.second);
    cout<<res<<endl;
    print_dp_table(p.first, p.second);
    return 0;
}
