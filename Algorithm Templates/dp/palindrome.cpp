#include <bits/stdc++.h>
using namespace std;

int palindrome(string x, int dp[30][30], int i, int j){
    if(i==j) return 1; // 1 length palindrome
    if(j<i) return 0; // no more palindrome
    if(dp[i][j] != -1) return dp[i][j]; // memoization
    int ans = 0; // at least 0 solution
    if(x[i] == x[j]) {
        ans = 2+palindrome(x, dp, i+1, j-1); //finding the middle palindrome characters
    }
    else {
        // will try in both range finding max length palindrom in [i, j-1], [i+1, j]
        ans = max(palindrome(x, dp, i, j-1), palindrome(x, dp, i+1, j));
    }
    dp[i][j] = ans;
    return dp[i][j];
}

int main(void){

}
