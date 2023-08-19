#include <bits/stdc++.h>
using namespace std;

#define MAX 100
#define MAX_INF 100000000

int mcm(vector<pair<int,int>>V, int i, int k, int dp[MAX+1][MAX+1]){
    if ((k-i) == 1) {
        return V[i].first * V[i].second * V[k].second;
    }
    if (k == i) return 0;
    if (k<i) return MAX_INF;
    if (dp[i][k] != -1) {
        return dp[i][k];
    }
    int res = MAX_INF;
    for(int j=i; j<k;j++){
        res = min(res, mcm(V, i, j, dp) + mcm(V, j+1, k, dp) + (V[i].first * V[j].second * V[k].second));
    }
    dp[i][k] = res;
    return res;
}

void iterative_mcm(vector<pair<int,int>>V, int dp[MAX+1][MAX+1]){
    int n = V.size();
    int k, j;
    int res;
    for(int i = 0; i< n; i++)
        dp[i][i] = 0;
    for (int length = 2; length<=n; length++)
    {
        for(int i = 0; i<=n-2; i++)
        {
            k = i+length-1;
            res = MAX_INF;
            for(int mid=1; mid<length; mid++)
            {
                j = i+mid-1;
                res = min(res, dp[i][j] + dp[j+1][k] + V[i].first * V[j].second * V[k].second);
            }
            dp[i][k] = res;
        }
    }
}


void print_mcm(int i, int j, int dp[MAX+1][MAX+1], vector<pair<int,int>>V){
    if(i == j) {
        cout<<i<<" ";
        return;
    }
    if((j-i) == 1) {
        cout<<i<<" "<<j<<" ";
        return;
    }
    int value = 0;
    int best = -1;
    for(int k=i; k<j; k++){
        if(dp[i][j] == (dp[i][k]+dp[k+1][j] + V[i].first * V[k].second * V[j].second)){
            cout<<"(";
            print_mcm(i,k, dp, V);
            cout<<")";
            cout<<"(";
            print_mcm(k+1, j, dp, V);
            cout<<")";
            break;
        }
    }
    return;
}

vector<pair<int, int>> input(){
    int n;
    cin>>n;
    pair<int,int>p;
    vector<pair<int, int>>V;
    for(int i=0;i<n;i++){
        cin>>p.first>>p.second;
        V.push_back(p);
    }
    return V;
}

int main(void){
    freopen("in.txt", "r", stdin);
    vector<pair<int, int>>V = input();
    int dp[MAX+1][MAX+1];
    memset(dp, -1, sizeof(dp));
    //cout<<dp[0][2] << dp[0][5]<<endl;
    int res = mcm(V, 0, V.size()-1, dp);
    cout<<res<<endl;
    // iterative DP
    iterative_mcm(V, dp);
    cout<<dp[0][V.size()-1]<<endl;
    cout<<"(";
    print_mcm(0, V.size()-1, dp, V);
    cout<<")"<<endl;
    return 0;
}
