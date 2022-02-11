#include <bits/stdc++.h>
#define MAX_SIZE 1000000
using namespace std;


void update_array(int arr[]) {
    arr[2] = 6;
}

template<typename T> void print_array(T arr[], int n) {
    for(int i=0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template<typename T> void merge_sort(T arr[], T temp[], int st, int en) {
    //T temp[MAX_SIZE+1];
    if (st == en) {
        return;
    }
    if (en-st == 1) {
        if (arr[en] < arr[st]) {
            swap(arr[en], arr[st]);
        }
        return;
    }
    int mid = (st+en)/2;
    // divide
    print_array(arr, en+1);
    // calling left partition
    merge_sort(arr, temp, st, mid);
    // calling right partition
    merge_sort(arr, temp, mid+1, en);
    // combining the results
    int i=st, j = mid+1, k = st;
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
    cout<<"some sorted " << endl;
    print_array(arr, 6);
    return;
}

main()
{
    int arr[6] = {7, 1, 2, -7, 17, 10};
    int t = sizeof(arr)/sizeof(arr[0]); //length calculation
    cout<<t<<endl;
    int temp[MAX_SIZE];
    merge_sort(arr, temp, 0, t-1);
    print_array(arr, 6);
    return 0;
}
