#include <bits/stdc++.h>
using namespace std;
#define MAX 501
#define MAX_INF 1000000000

int dp[MAX+1][MAX+1];
int grid[MAX+1][MAX+1];
int dx[] = {-1,-1}; // {-1,-1,-1}
int dy[] = {1,-1}; // {1,0,-1}

pair<int,int> input(){
    int m,n;
    cin>>m>>n;
    for(int i=0; i<m;i++){
        for(int j=0; j<n; j++){
            cin>>grid[i][j];
        }
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
    int x,y;
    if (i == 0) {
        return grid[i][j];
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    int res = MAX_INF;
    for(int k=0; k<2; k++){
        x = i+dx[k];
        y = j+dy[k];
        if (bounding_check(x, y, row, col) == true) {
            res = min(res, grid[i][j]+hill_climbing(x, y, row, col));
        }
    }
    dp[i][j] = res;
    return dp[i][j];
}


int main(void){
    freopen("in.txt", "r", stdin);
    //freopen("large_out2.txt", "w", stdout);
    pair<int,int> p = input();
    int res = MAX_INF;
    memset(dp, -1, sizeof(dp));
    //cout<<dp[0][0] << dp[0][2] << endl;
    for(int i=0;i<p.second;i++){
        res = min(res, hill_climbing(p.first-1, i, p.first, p.second));
    }
    cout<<res<<endl;
    return 0;
}
