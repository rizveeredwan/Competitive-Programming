#include <bits/stdc++.h>
#define MAX_SIZE 1000000
using namespace std;


template <typename T> void random_choosing(T arr, int st, int en) {
    srand(time(0));
    int pivot_idx = en;
    int gap = (en-st)+1;
    int random_idx = rand()%gap+st;
    swap(arr[random_idx], arr[en]);
    return;
}

int choose_median_index(int v1, int v2, int v3) {
    if ((v2 >= v1 and v2 <= v3) || (v2 >= v3 and v2 <= v1)) {
        return 1;
    }
    if ((v1 >= v2 and v1 <= v3) || (v1 >= v3 and v1 <= v2)) {
        return 0;
    }
    if ((v3 >= v1 and v3 <= v2) || (v3 >= v2 and v3 <= v1)) {
        return 2;
    }
    return 0;
}

template <typename T> void median_based_choosing(T arr, int st, int en) {
    int mid = (st+en)/2;
    int median = choose_median_index(arr[st], arr[mid], arr[en]);
    if (median == 0) {
        swap(arr[st], arr[en]);
    }
    else if (median == 1) {
        swap(arr[mid], arr[en]);
    }
    return;
}

template <typename T> int _partition(T arr, int st, int en){
    // using random generation of index
    random_choosing(arr, st, en);
    // median based choosing
    //median_based_choosing(arr, st, en);
    int i=st-1, j=st;
    for(;j<en;j++) {
        if (arr[j] <= arr[en]) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    int pivot_idx = en;
    if ((i+1) < en) {
        i=i+1;
        swap(arr[i], arr[en]);
        pivot_idx = i+1;
    }
    return pivot_idx;
}

template<typename T> void print_array(T arr[], int n) {
    for(int i=0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T> void quick_sort(T arr, int n, int st, int en) {
    if (en < st) {
        return;
    }
    int pivot_idx = _partition(arr, st, en);
    print_array(arr, n);
    int gap = en-st;
    if (gap == 0) {
        return;template<typename T> void print_array(T arr[], int n) {
    for(int i=0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
    }
    if (gap == 1) {
        if (arr[st] > arr[en]) {
            swap(arr[en], arr[st]);
        }
        return;
    }
    if (pivot_idx == en) {
        // a bad partition: reducing one element
        quick_sort(arr, n, st, pivot_idx-1);
    }
    else{
         // a normal partition
         quick_sort(arr, n, st, pivot_idx);
    }
    if (pivot_idx < en) {
        // can be called right part
        quick_sort(arr, n, pivot_idx+1, en);
    }
    return;
}


int main(void){
    int arr[6] = {7, 1, 2, -7, 17, 10};
    int n = sizeof(arr)/sizeof(arr[0]); //length calculation
    cout<<n<<endl;
    quick_sort(arr, n, 0, n-1);
}
