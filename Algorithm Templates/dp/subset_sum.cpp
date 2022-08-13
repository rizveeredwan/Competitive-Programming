#include <bits/stdc++.h>
using namespace std;
#define MAX_SUM 1000
#define MAX_N 100


int rec(int i, int curr_sum, int tot_sum, int n, int dp[MAX_N][MAX_SUM], int a[MAX_N]){
    if(i>=n) return abs(curr_sum-(tot_sum-curr_sum));
    if (dp[i][curr_sum] != -1){
         return dp[i][curr_sum];
    }
    dp[i][curr_sum] = min( rec(i+1, curr_sum+a[i], tot_sum, n, dp, a),
                          rec(i+1, curr_sum, tot_sum, n, dp, a));
    return dp[i][curr_sum];
}

int subset_sum(int a[], int n){
    int sum = 0;
    int min_val;
    for(int i=0; i<n; i++){
        if(i==0) min_val = a[i];
        else min_val = min(min_val, a[i]);
    }
    if(min_val<0) {
        for(int i=0; i<n; i++){
            a[i] = a[i]+abs(min_val);
        }
    }
    for(int i=0; i<n; i++){
            sum += a[i];
    }
    int dp[MAX_N][MAX_SUM];
    memset(dp, -1, sizeof(dp));
    int ans = rec(0, 0, sum, n, dp, a);
    cout<<ans<<endl;
}


int main(void){
    int n;
    cin>>n;
    int a[MAX_N];
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    subset_sum(a, n);
    return 0;
}
