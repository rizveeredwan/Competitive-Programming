#include <bits/stdc++.h>
using namespace std;
#define MAX_NUMBER 1000001


/*
Writer: Redwan Ahmed Rizvee
Tested On: https://www.spoj.com/problems/DQUERY/
Algorithm Idea: https://blog.anudeep2011.com/mos-algorithm/
*/

struct Query{
    int l,r;
    int res;
    int id;
};

vector<int>V;
vector<Query>Q;
int sqrtN;

bool cmp(Query a, Query b){
    //comparison function for MO's algorithm
    if(a.l/sqrtN>b.l/sqrtN) return false;
    if(a.l/sqrtN>b.l/sqrtN) return true;
    if(a.l/sqrtN == b.l/sqrtN) {
        if(a.r < b.r) return true;
        return false;
    }
}

bool cmpMoPrint(Query a, Query b){
	if(a.id<b.id)return true;
	return false;
}

int answer;
int freq[MAX_NUMBER+1];
void _add(int index){
    freq[V[index]]++;
    if(freq[V[index]] == 1) answer++; //new unique number encountered
}

void _remove(int index){
    freq[V[index]]--;
    if(freq[V[index]] == 0) answer--; //some number is lost
}

void mosAlgorithm(){
    sort(Q.begin(),Q.end(),cmp);
    Query temp;
    int currentL=-1;
    int currentR=-1;
    answer=0;
    memset(freq,0,sizeof(freq));
    for(int i=0;i<(int)Q.size();i++){
        temp=Q[i];
        while(temp.l<currentL) {
            currentL--;
            _add(currentL);
        }
        while(temp.l>currentL) {
			if(currentL != -1) {
				_remove(currentL);
			}
            currentL++;
        }
        while(temp.r<currentR) {
            _remove(currentR);
            currentR--;
        }
        while(temp.r>currentR) {
            currentR++;
            _add(currentR);
        }
        Q[i].res=answer;
    }
    return;
}

void mosAlgorithmPrint(){
	sort(Q.begin(),Q.end(),cmpMoPrint);
	for(int i=0;i<(int)Q.size();i++){
		printf("%d\n",Q[i].res);
	}
	return;
}

int main(void){
	
	//freopen("in.txt","r",stdin);
	
    int n;
    scanf("%d",&n);
    sqrtN=sqrt(n);
    int v;
    for(int i=0;i<n;i++){
        scanf("%d",&v);
        V.push_back(v);
    }
    int q;
    scanf("%d",&q);
    int l,r;
    for(int i=0;i<q;i++){
        scanf("%d %d",&l,&r);
        l--;
        r--; //0 based index
        Q.push_back({l,r,0,i});
    }
    mosAlgorithm();
    mosAlgorithmPrint(); 
    return 0;
}
