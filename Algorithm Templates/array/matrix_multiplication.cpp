#include <stdio.h>

void matrix_multiplication(int A[][30], int B[][30], int C[][30], int ra, int ca, int rb, int cb){
    for(int i=0; i<ra; i++){
        for(int j=0; j<cb; j++){
            C[i][j] = 0;
            for(int k=0; k<ca; k++){
                C[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }
    return;
}

void input(int *r, int *c, int A[30][30]){
    int _r, _c;
    scanf("%d %d", &_r, &_c);
    *r = _r;
    *c = _c;
    for(int i=0; i<*r; i++){
        for(int j = 0; j<*c; j++){
            scanf("%d", &A[i][j]);
        }
    }
    return;
}

void print_matrix(int r, int c, int A[30][30]){
    printf("%d %d\n",r,c);
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(j == (c-1)) {
                printf("%d\n",A[i][j]);
            }
            else {
                printf("%d ",A[i][j]);
            }
        }
    }
    return;
}

int main(void){
    freopen("in.txt", "r", stdin);
    printf("done\n");
    int ra, ca, rb, cb, A[30][30], B[30][30], C[30][30];
    input(&ra, &ca, A);
    print_matrix(ra, ca, A);
    input(&rb, &cb, B);
    print_matrix(rb, cb, B);
    matrix_multiplication(A, B, C, ra, ca, rb, cb);
    print_matrix(ra, cb, C);
    return 0;
}
