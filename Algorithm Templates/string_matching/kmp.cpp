#include <bits/stdc++.h>
using namespace std;
#define MAX 100000


void shift_string(char P[]){
    int m=strlen(P);
    for(int i=m; i>=0;i--){
        P[i+1]=P[i];
    }
}

void compute_prefix_function(char P[], int pi[]){
    // 1 based indexing
    cout<<P<<endl;
    int m = strlen(P);
    pi[0] = 0;
    pi[1] = 0;
    int k = 0;
    for(int q=2; q<m; q++){
        while (k>0 && P[k+1] != P[q]){
            k = pi[k];
        }
        if(P[k+1] == P[q]) {
            k++;
        }
        pi[q] = k;
    }
    return;
}

void print_prefix_array(int pi[], int m){
    for(int i=1; i<=m ; i++){
        if(i==m) cout<<pi[i]<<endl;
        else {
            cout<<pi[i]<<" ";
        }
    }
    return;
}

int main(void){
    freopen("in2.txt", "r", stdin);
    char T[MAX+1], P[MAX+1];
    int pi[MAX+1];
    cin>>T;
    cin>>P;
    shift_string(P);
    compute_prefix_function(P, pi);
    int m = strlen(P);
    cout<<"m = "<<m<<endl;
    print_prefix_array(pi,m-1);
    return 0;
}
