#include <bits/stdc++.h>
using namespace std;
# define MAX 10000
# define MAX_INF 10000000000

struct Knapsack{
    int b,w;
};

int recursion1(vector<Knapsack>V, int idx, int amount, int dp[30][MAX+1]){
    int ans = -MAX_INF;
    if (amount == 0) {
        return 0;
    }
    if (idx >= V.size()) {
        return 0;
    }
    if (dp[idx][amount] != -1) {
        return dp[idx][amount];
    }
    if(amount-V[idx].w >= 0) {
        ans = V[idx].b+recursion1(V,idx+1,amount-V[idx].w,dp);
    }
    ans = max(ans, recursion1(V,idx+1,amount,dp));
    dp[idx][amount] = ans;
    return dp[idx][amount];
}

pair<vector<Knapsack>,int> input(){
    int n,k;
    cin>>n>>k;
    vector<Knapsack>V;
    Knapsack temp;
    for(int i=0;i<n;i++){
        cin>>temp.b;
        V.push_back(temp);
    }
    for(int i=0;i<n;i++){
        cin>>temp.w;
        V[i].w = temp.w;
    }
    pair<vector<Knapsack>,int> P;
    P.first = V;
    P.second = k;
    return P;
}

void iterative_calculation(int dp[30][MAX+1], int w, vector<Knapsack>V){
    // P[i][w] = max(P[i-1][w-wi]+bi, P[i-1][w])
    memset(dp,-1,sizeof(dp));
    // 0 knapsack weight
    for(int i=0;i<V.size();i++) dp[i][0] = 0;
    for(int i=0; i<=w; i++) dp[0][i] = 0;
    for(int i=1; i<V.size(); i++){
        for(int j=1; j<=w; j++){
            dp[i][j] = max(dp[i-1][j], dp[i][j]);
            if((j-V[i].w) >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j-V[i].w]+V[i].b);
        }
    }
    return;
}

void path_print(int dp[30][MAX+1], int w, vector<Knapsack>V) {
     int i = V.size()-1, j = w;
     vector<int>idx;
     int nr,nc;
     bool problem;
     vector<int>chosen;
     while(true){
        if(i == 0) {
            break;
        }
        else {
            if(dp[i-1][j] == dp[i][j]) {
                i=i-1;
            }
            else if(dp[i][j] == (dp[i-1][j-V[i].w] + V[i].b)){
                chosen.push_back(i);
                i=i-1;
                j=j-V[i].w;
            }
            else {
                problem = true;
                assert(problem==false);
            }
        }
     }
     for(int i=0; i<chosen.size(); i++) cout<<chosen[i]<<endl;
     return;
}

void print_knapsack_table(int dp[30][MAX+1], int w, int item_count){
    for(int j=0; j<item_count; j++){
        for(int i=0;i<=w;i++){
            cout<<dp[j][i]<<" ";
        }
        cout<<endl;
    }

}

void print_vector(vector<Knapsack>V){
    for(int i=0; i<V.size(); i++) cout<<V[i].b << " "<< V[i].w<<endl;
}

int main(void){
    freopen("in.txt", "r", stdin);
    pair<vector<Knapsack>,int> P = input();
    int dp[30][MAX+1];
    /*memset(dp, -1, sizeof(dp));
    cout<<recursion1(P.first, 0, P.second, dp)<<endl;
    print_knapsack_table(dp, P.second, P.first.size());*/
    Knapsack temp;
    temp.b = 0;
    temp.w = 0;
    P.first.insert(P.first.begin()+0, temp);
    print_vector(P.first);
    iterative_calculation(dp, P.second, P.first);
    cout<<"table calculation complete"<<endl;
    print_knapsack_table(dp, P.second, P.first.size());
    path_print(dp, P.second, P.first);
    return 0;
}
