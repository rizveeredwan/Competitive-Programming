#include <stdio.h>
#define MAX 101

/*
    solution is mainly to find increasing sequence
    if I encounter decreasing sequence, its the solution point
*/

int main(void){
    int n;
    scanf("%d", &n);
    int arr[MAX+1];
    for(int i=1; i<=n; i++){
        scanf("%d", &arr[i]);
    }
    int idx = 0;
    for(int i=2; i<=n; i++){
        if(arr[i] < arr[i-1]) {
            idx = i;
            break;
        }
    }
    printf("%d\n", idx);
    return 0;
}
