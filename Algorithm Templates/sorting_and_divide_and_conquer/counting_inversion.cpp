#include <bits/stdc++.h>
#define MAX_SIZE 100000
using namespace std;


template<typename T> int count_inversion(T arr[], T temp[], int st, int en) {
    //T temp[MAX_SIZE+1];
    cout<<st<<" "<<en<<endl;
    if (st == en) {
        return 0;
    }
    if (en-st == 1) {
        if (arr[en] < arr[st]) {
            swap(arr[en], arr[st]);
            return 1;
        }
        return 0;
    }
    int mid = (st+en)/2;
    // calling left partition
    int left = count_inversion(arr, temp, st, mid);
    // calling right partition
    int right = count_inversion(arr, temp, mid+1, en);
    // combining the results
    int i=st, j = mid+1, k = st;
    int local = 0;
    while (i<=mid || j <=en) {
        // will continue till all checking
        if (i <= mid && j<=en) {
            // pointer based: Take the small one
            if (arr[i] <= arr[j]) {
                temp[k] = arr[i];
                i++;
            }
            else {
                temp[k] = arr[j];
                j++;
                local += (mid-i+1);
            }
        }
        else if(i<=mid) {
            temp[k] = arr[i];
            i++;
        }
        else if (j<=en) {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    // reverse copying the result
    for(i=st,k=st; i<=en; i++,k++) {
        arr[i] = temp[k];
    }
    cout<<"p q r "<<st<<" "<<mid<<" "<<en<< " "<<left<<" "<<right<<" "<<local<<endl;
    return left+right+local;
}

int main(void){
    // 1 5 4 6 2 7 -3
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    int arr[MAX_SIZE+1], temp[MAX_SIZE+1];
    for(int i=0; i<n;i++){
        scanf("%d", &arr[i]);
    }
    int inv = count_inversion(arr, temp, 0, n-1);
    printf("%d\n", inv);
    return 0;
}
