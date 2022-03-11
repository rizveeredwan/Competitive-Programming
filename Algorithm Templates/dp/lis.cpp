#include<bits/stdc++.h>
using namespace std;
#define MAX 100

struct LIS{
    void lis(vector<int> A){
        cout<<A.size()<<endl;
        vector<pair<int,int>>B;
        vector<int>parent;
        // initializing parent indexes;
        for(int i=0;i<A.size(); i++){
            parent.push_back(-1);
        }
        pair<int,int>p;
        int idx;
        char ch;
        for(int i=0; i<A.size(); i++){
            //cin>>ch;
            idx = this->bs(B, A[i]);
            //cout<<"idx = "<<idx<<" "<<A[i]<<endl;
            p.first = i;
            p.second = A[i];
            if(idx == -1) {
                B.push_back(p);
                idx = B.size()-1;
            }
            else{
                if(B[idx].second > A[i]) {
                    // replace
                    B[idx] = p;
                }
                else if(B[idx].second < A[i]){
                    // last append
                    B.push_back(p);
                    idx = B.size()-1;
                }
                else if(B[idx].second == A[i]){
                    assert(idx == (B.size()-1));
                    B.push_back(p);
                    idx = B.size()-1;
                }
            }
            if(B.size()>1 && idx > 0){
                parent[i] = B[idx-1].first;
            }
            this->print(B);
            this->extract_lis(A, parent, B);
        }
    }
    int bs(vector<pair<int,int>>B, int key){
        int low = 0, high = B.size()-1;
        int mid=-1, ans=-1;
        while (low<=high){
            if (low == high) {
                cout<<"dhuki"<<endl;
                if(B[low].second >= key) {
                    ans = low;
                }
                break;
            }
            mid = (low+high+1)/2;
            if(B[mid].second>key){
                high=mid-1, ans=mid;
            }
            else if(B[mid].second < key){
                low=mid+1;
            }
            else if(B[mid].second == key){
                low=mid+1, ans=mid;
            }
        }
        return ans;
    }
    void print(vector<pair<int,int>>V){
        for(int i=0;i<V.size();i++){
            cout<<V[i].first<<" "<<V[i].second<<endl;
        }
        return;
    }
    void extract_lis(vector<int>A, vector<int>parent, vector<pair<int, int>>B){
        int last = B[B.size()-1].first;
        vector<int>seq;
        seq.push_back(A[last]);
        int par = last;
        while(true){
            par = parent[par];
            if (par == -1) break;
            seq.push_back(A[par]);
        }
        reverse(seq.begin(), seq.end());
        for(int i=0;i<seq.size();i++){
            cout<<seq[i]<< " ";
        }
        cout<<endl;
    }
};

vector<int> input(){
    int n;
    cin>>n;
    vector<int>A;
    int val;
    for(int i=0;i<n;i++){
        cin>>val;
        A.push_back(val);
    }
    return A;
}

int main(void){
    //freopen("in.txt", "r", stdin);
    vector<int>A = input();
    LIS lis;
    lis.lis(A);
}
