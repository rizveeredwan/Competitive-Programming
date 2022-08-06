#include <bits/stdc++.h>
using namespace std;

int rod_cut(int n, int dp[], int L[], int B[]){
    if(n == 0) return 0; // all done
    if (dp[n] != -1) return dp[n]; // memoization
    int best = -1000; // best result
    for(int i=1; i<=4; i++){ // trying with all partitions
        if(n-L[i] >= 0) {
            best = max(best, B[i] + rod_cut(n-L[i], dp, L, B));
        }
    }
    dp[n] = best;
    return best;
}

int main(void){

}
