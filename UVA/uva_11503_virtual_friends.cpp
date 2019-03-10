#include <bits/stdc++.h>
using namespace std;
#define MAX 100005


map<string,int>M;
int parent[MAX+5];
int totalConn[MAX+5];

int findParent(int a){
    if(parent[a] == a) return a;
    parent[a]=findParent(parent[a]);
    return parent[a];
}


int main(void){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    int T,t;
    scanf("%d",&T);
    int n;
    string a,b;
    int cnt=0;
    for(t=1;t<=T;t++){
        scanf("%d",&n);
        M.clear();
        cnt=0;
        for(int i=0;i<MAX;i++){
            parent[i]=i;
            totalConn[i]=1;
        }
        for(int i=0;i<n;i++){
            cin >>a>>b;
            if(M[a]==0){
                cnt++;
                M[a]=cnt;
            }
            if(M[b] == 0){
                cnt++;
                M[b]=cnt;
            }
            int p_a=findParent(M[a]);
            int p_b=findParent(M[b]);
            if(p_a == p_b) {
                cout<<totalConn[p_a]<<endl;
            }
            else{
                parent[p_a]=p_b;
                totalConn[p_b] += totalConn[p_a];
                cout<<totalConn[p_b]<<endl;
            }
        }
    }
    return 0;
}

