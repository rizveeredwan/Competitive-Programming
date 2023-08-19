#include <bits/stdc++.h>
using namespace std;

int upper_bound_func(vector<int>V, int s){
    int low=0, high=V.size()-1;
    int ans=-1,ans_idx=-1;
    while(low<=high){
        int mid = (low+high+1)/2;
        if(V[mid] > s){ // possible answer, need to make it smaller
            ans_idx = mid;
            ans = V[mid];
            high = mid-1;
        }
        else if(V[mid] <= s){
            low = mid+1;
        }
    }
    return ans_idx;
}

int move_right(vector<int>V, int idx){
    int s = V[idx];
    int low = idx, high = V.size()-1;
    int ans_idx=idx;
    while (low<=high){
        int mid = (low+high+1)/2;
        if(V[mid] > s){ // became big, make smaller
            high = mid-1;
        }
        else if(V[mid] == s){
            ans_idx = mid; // possible answer, go to right more if possible
            low = mid+1;
        }
        assert(V[mid]>=s);
    }
    return ans_idx;
}

int move_left(vector<int>V, int idx){
    int s = V[idx];
    int low = 0, high = idx;
    int ans_idx=idx;
    while (low<=high){
        int mid = (low+high+1)/2;
        if(V[mid] < s){ // became smaller, go to right more to make it bigger
            low = mid+1;
        }
        else if(V[mid] == s){
            ans_idx = mid; // possible answer, go to left more if possible
            high = mid-1;
        }
        assert(V[mid]<=s);
    }
    return ans_idx;
}

int lower_bound_func(vector<int>V, int s){
    int low=0, high=V.size()-1;
    int ans=-1,ans_idx=-1;
    while(low<=high){
        int mid = (low+high+1)/2;
        if(V[mid] <= s){ // possible answer, need to make it bigger if possible
            ans_idx = mid;
            ans = V[mid];
            low = mid+1;
        }
        else if(V[mid] > s){
           high =  mid-1;
        }
    }
    return ans_idx;
}


int main(void){
    int n;
    int s;
    cin>>n>>s;
    vector<int>V;
    for(int i=0; i<n; i++){
        V.push_back(-1);
        cin>>V[i];
    }
    int up_idx = upper_bound_func(V, s);
    int low_idx = lower_bound_func(V, s);
    if(up_idx == -1){ // no soln found
        up_idx = V.size(); // as per the question
    }
    else {
        // going to move right
        up_idx = move_right(V, up_idx);
    }
    if(low_idx == -1){ // no solution found
        low_idx = 0;
    }
    else {
        low_idx = move_left(V, low_idx);
    }
    cout<<up_idx<<" "<<low_idx<<endl;
    return 0;
}
