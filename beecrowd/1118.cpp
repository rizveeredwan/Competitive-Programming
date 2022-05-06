#include <bits/stdc++.h>
using namespace std;

int main(void){
    int X;
    float a,b;
    while(1){
        while(1){
            scanf("%f", &a); // trying to take a
            if(a >= 0.0 && a<= 10.0) {
                break;
            }
            else {
                printf("nota invalida\n"); // I haven't found proper a still
            }
        }
        // same work for b
        while(1){
            scanf("%f", &b); // trying to take a
            if(b >= 0.0 && b<= 10.0) {
                break;
            }
            else {
                printf("nota invalida\n"); // I haven't found proper b still
            }
        }
        // I found two valid numbers
        float sum = a + b;
        sum = sum/2.0;
        printf("media = %0.2f\n",sum);
        printf("novo calculo (1-sim 2-nao)\n"); // this printing is sort of like menu
        while(1){
            // So, now I am trying to take X
             scanf("%d", &X);
             if(X < 1 || X>2) { // I need to try again, after printing the msg
                printf("novo calculo (1-sim 2-nao)\n");
                continue;
             }
             if(X == 2) {
                return 0;
             }
             if(X == 1) { // again calculate avg from the beginning
                break;
             }
        }
    }
    return 0;
}
