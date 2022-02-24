#include <bits/stdc++.h>
#define MAX_SIZE 1000000
#define MAX_INFINITY 1000000000000000000
using namespace std;


struct Point {
    double x,y;
};

Point p[MAX_SIZE+1];
vector<Point>V;

bool compare_by_x(Point i1, Point i2)
{
    if (i1.x < i2.x) {
        return -1;
    }
    return 0;
}

bool compare_by_y(Point i1, Point i2) {
    if (i1.y < i2.y) {
        return -1;
    }
    return 0;
}

double euclid_distance(Point p1, Point p2) {
    double dist = (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
    dist = sqrt(dist);
    return dist;
}


double closest_two_pairs(Point arr[], int st, int en){
    double d;
    if (st == en) {
        return MAX_INFINITY;
    }
    if ((en-st) == 1) {
        double dist = euclid_distance(arr[st], arr[en]);
        return dist;
    }
    int mid = (st+en)/2;
    double dl = closest_two_pairs(arr, st, mid);
    double dr = closest_two_pairs(arr, mid+1, en);
    d = min(dl, dr);
    V.clear();
    for(int i=mid-1; i>=st; i--){
        if (abs(arr[i].x-arr[mid].x) <= d) {
            V.push_back(arr[i]);
        }
    }
    for(int i=mid+1; i<=en; i++){
        if (abs(arr[i].x-arr[mid].x) <= d) {
            V.push_back(arr[i]);
        }
    }
    sort(V.begin(), V.end(), compare_by_y);
    for(int i=0;i<V.size();i++){
        for(int j=i+1; j<V.size() && abs(V[i].y-V[j].y) <= d;j++){
            d = min(d, euclid_distance(V[i], V[j]));
        }
    }
    return d;
}

int input(){
    int n;
    scanf("%d", &n);
    double x,y;
    for(int i=0; i<n;i++){
        scanf("%lf %lf", &x, &y);
        p[i].x = x;
        p[i].y = y;
    }
    return n;
}

int main(void){
    int n = input();
    sort(p,p+n,compare_by_x);
    double dist = closest_two_pairs(p, 0, n-1);
    printf("%lf\n", dist);
    return 0;
}
