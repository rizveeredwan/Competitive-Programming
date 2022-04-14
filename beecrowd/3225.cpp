#include <bits/stdc++.h>
using namespace std;
#define MAX 100000

int position_array[MAX+1];
int mapper[MAX+1];

void swap_position(int arr[], int c){
    swap(arr[c],arr[c-1]);
    swap(arr[c-1], arr[c-2]);
    return;
}

void print_array(int a[], int n){
    for(int i=0; i<n;i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return;
}

void soln(int A[], int B[], int n){
    int value, curr_pos;
    int last_set = -1;
    for(int i=0; i<n; i++){
        position_array[A[i]] = i;
        mapper[i] = -1;
    }
    bool flag=false;
    int temp;
    for(int i=0; i<n;i++){
        value = B[i];
        flag = false;
        curr_pos = position_array[value]; // currently in this position
        if(curr_pos == i){
            flag=true;
            last_set=i; // ei porjonto milano done
            continue; // jekhane chaisilam okhane ache
        }
        //cout<<"Value "<<B[i]<<endl;
        last_set=i; // [last_set, n-1] er moddhe khujbo
        while(true){
            //cout<<"curr_pos "<<curr_pos<<" "<<i<<endl;
            if(i == curr_pos) {
                // desired jaiga te chole asche
                flag=true;
                break;
            }
            if((curr_pos-2) >= last_set) {
                // shamne ante parbo and ekhane age ashi nai tai
                //cout<<"dhuksi ekhane"<<endl;
                swap_position(A,curr_pos);
                for(int j=curr_pos; j>=curr_pos-2; j--){
                    position_array[A[j]]=j;
                }
                curr_pos = curr_pos-2;
                continue;
            }
            else {
                //cout<<"ashe"<<endl;
                if((curr_pos-last_set) == 1 && (curr_pos+1)<n) {
                    swap_position(A, curr_pos+1);
                    curr_pos = curr_pos+1;
                    for(int j=curr_pos; j>=curr_pos-2; j--){
                        position_array[A[j]]=j;
                    }
                    swap_position(A, curr_pos);
                    for(int j=curr_pos; j>=curr_pos-2; j--){
                        position_array[A[j]]=j;
                    }
                    curr_pos = curr_pos-2;
                    //mapper[curr_pos]=i;
                    //print_array(A, n);
                    continue;
                }
                if((curr_pos-last_set) == 2) {
                    swap_position(A, curr_pos);
                    for(int j=curr_pos; j>=curr_pos-2; j--){
                        position_array[A[j]]=j;
                    }
                    curr_pos = last_set;
                    continue;
                }
                else {
                    flag = false;
                    break;
                }
            }
        }
    }
    if(flag) cout<<"Possible"<<endl;
    else cout<<"Impossible"<<endl;
}
// segment tree with lazy propagation
// ekta segment er shobai (+1) kore right e shorlo
// tokhon (nlogn) e sort korte parbo

int main(){
    //freopen("in1.txt", "r", stdin);
    int n;
    cin>>n;
    int A[MAX+1],B[MAX+1];
    for(int i=0;i<n;i++){
        cin>>A[i];
    }
    for(int i=0;i<n;i++){
        cin>>B[i];
    }
    soln( A, B, n);
    return 0;
}
