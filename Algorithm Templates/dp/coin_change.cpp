#include <bits/stdc++.h>
using namespace std;
# define MAX 1000
# define MAX_IDX 30
# define MAX_INF 1000000000


struct NextState{
    int first,second;
};

vector<int> input_generation(int n, int min_value, int max_value) {
    srand(time(NULL));
    map<int,bool>M;
    vector<int>V;
    int value;
    auto it = M.begin();
    while (V.size() < n) {
        value = rand()%max_value+min_value;
        if (M.find(value) == M.end()) {
            M[value]=true;
            V.push_back(value);
        }
    }
    return V;
}

void print_vector(vector<int>V){
    for(int i=0; i<V.size(); i++){
        cout<<V[i]<<" ";
    }
    cout<<endl;
}

int NODES_CHECKED = 0;
int recursion1(vector<int>V, int idx, int amount, int dp[30][MAX+1], NextState next_state[30][MAX+1]){
    int ans1 = MAX_INF, ans2=MAX_INF;
    if (amount == 0) {
        return 0;
    }
    if (idx >= V.size()) {
        return MAX_INF;
    }
    if (dp[idx][amount] != -1) {
        return dp[idx][amount];
    }
    NODES_CHECKED++;
    if(amount-V[idx] >= 0) {
        ans1 = 1+recursion1(V,idx,amount-V[idx],dp, next_state);
    }
    ans2 = recursion1(V,idx+1,amount,dp, next_state);
    if (ans1<=ans2) {
        next_state[idx][amount].first = idx;
        next_state[idx][amount].second = amount-V[idx];
    }
    else {
        next_state[idx][amount].first = idx+1;
        next_state[idx][amount].second = amount;
    }
    dp[idx][amount] = min(ans1, ans2);
    return dp[idx][amount];
}

void get_path(NextState next_state[30][MAX+1], vector<int>V, int idx, int amount, map<int,int> &M) {
    if(amount == 0 || idx >= V.size()) {
        return;
    }
    int x = next_state[idx][amount].first;
    int y = next_state[idx][amount].second;
    if(y<amount) {
        // idx been considered
        if (M.find(V[idx]) == M.end()) M[V[idx]] = 0;
        M[V[idx]]++;
    }
    get_path(next_state, V, x, y, M);
    return;
}

int coin_change_greedy(vector<int>V, int amount){
    sort(V.begin(), V.end());
    int c = 0, temp = amount;
    int mul = 0;
    for(int i=V.size()-1; i >= 0; i--){
        if ((temp-V[i]) >= 0) {
            mul = temp/V[i];
            temp = temp-mul*V[i];
            c += mul;
            cout<< V[i]<<" "<<mul<<endl;
        }
        if(temp == 0) return c;
    }
    return -1;
}

pair<vector<int>,int> problem_input(){

    freopen("in.txt", "r", stdin);
    int n,k;
    cin>>n>>k;
    vector<int>V;
    int v;
    for(int i=0;i<n;i++){
        cin>>v;
        cout<<v<<endl;
        V.push_back(v);
    }
    pair<vector<int>,int> P;
    P.first = V;
    P.second = k;
    return P;
}

void iterative_dp(vector<int>V, int K){
    vector<int>C;
    C.push_back(0);
    for(int i=0;i<V.size();i++){
        C.push_back(V[i]);
    }
    int dp[MAX_IDX+1][MAX];
    memset(dp, MAX_INF, sizeof(dp));
    cout<<dp[0][0]<<" "<<dp[0][1]<<endl;
    dp[0][0] = 0;
    // no coin, making taka
    for(int i=1; i<=K;i++) dp[0][i] = MAX_INF;
    // using coin, no taka
    int r1,r2;
    for(int i=0;i<C.size(); i++) dp[i][0] = 0;
    for(int i=1;i<C.size(); i++){
        for(int j=1;j<=K;j++){
            r1 = MAX_INF, r2 = MAX_INF;
            if((j-C[i])>=0){
                r1 = 1+dp[i][j-C[i]];
            }
            r2 = dp[i-1][j];
            dp[i][j] = min(r1,r2);
        }
    }
    cout<<dp[C.size()-1][K]<<endl;
}

int main(void){
    /*int n = 10, min_value = 1, max_value = 100;
    vector<int>V = input_generation(n, min_value, max_value);
    sort(V.begin(), V.end());
    print_vector(V);*/
    // 1 13 20 23 36 37 38 51 61 94 97
    pair<vector<int>,int> P = problem_input();
    vector<int>V = P.first;
    int amount = P.second;
    /*** Greedy **/
    /*int gr_soln = coin_change_greedy(V, amount);
    cout<<"greedy solution"<<endl;
    cout<<gr_soln << endl;*/
    /** dp **/
    int dp[30][MAX+1];
    memset(dp, -1, sizeof(dp));
    //cout<<dp[0][0]<<" "<<dp[0][5]<<endl;
    NextState next_state[30][MAX+1];
    int dp_soln = recursion1(V,0,amount,dp, next_state);
    cout<<"dp solution"<<endl;
    cout<<dp_soln<<endl;
    cout<<"nodes checked "<<NODES_CHECKED<<endl;
    map<int,int>M;
    /*get_path(next_state, V, 0, amount, M);
    vector<pair<int,int>>pr_info;
    for(auto it = M.begin(); it != M.end(); it++) {
        //cout<<it->first<<" "<< it->second<<endl;
        pr_info.push_back({it->first, it->second});
    }
    sort(pr_info.begin(), pr_info.end());
    for(int i=0; i<pr_info.size(); i++){
        cout<<pr_info[i].first<<" "<<pr_info[i].second<<endl;
    }*/
    /*** iterative DP ****/
    //cout<<"iterative"<<endl;
    //iterative_dp(V, amount);
    return 0;
}
