#include <bits/stdc++.h>
using namespace std;

int partition(int arr[],int l,int h)
{
    cout<<"before ";
    for(int i=l; i<=h; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    int i=l+1;
    int j=h;
    while(i<j)
    {
        int pivot=arr[l];
        while(arr[i]<=pivot)
        {
            i++;
        }
        while(arr[j]>pivot)
        {
            j--;
        }
        if(i<j && arr[i] > arr[j])
        {
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    if(arr[j] < arr[l]) { // by chance if arr[j] is not small than arr[l],not blindly swapping
        int temp=arr[l];
        arr[l]=arr[j];
        arr[j]=temp;
    }
    cout<<"pivot idx "<<j<<" "<<"after ";
    for(int i=l; i<=h; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return j;
}
int quicksort(int arr[],int l,int h)
{
    if(l<h)
    {
        int par=partition(arr,l,h);
        quicksort(arr,l,par-1);
        quicksort(arr,par+1,h);
    }
}
void print(int arr[],int size)
{
    int i;
    printf("sorted array is :\n");
    for(i=0; i<size; i++)
    {
        printf("%d\n",arr[i]);
    }

}
/*
5
5 2 6 8 1
*/
int main()
{
    int arr1[100], n, l,h,i;
    printf("how many elements :");
    scanf("%d",&n);
    for(i=0; i<n; i++)
        scanf("%d",&arr1[i]);
    /*for(int j=0; j<n; j++)
    {
        cout<<arr1[j]<<endl;
    }
    cout<<"call kori"<<endl;
    cout<<partition(arr1, 0, n-1)<<endl;
    cout<<"call shesh"<<endl;
    for(int j=0; j<n; j++)
    {
        cout<<arr1[j]<<endl;
    }
    */
    quicksort(arr1,0,n-1 );
    print(arr1,n);
    return 0;
}
