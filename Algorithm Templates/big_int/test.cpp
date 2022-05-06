#include <bits/stdc++.h>
#include "big_int.cpp"

int main(void){
    char a[20],b[20], c[20], d[20];
    scanf("%s", a);
    scanf("%s", b);
    int flag = order(a, b, c, d);
    //printf("%s %s %s %s\n", a, b, c, d);
    //printf("%d\n",flag);
    char res[25];
    big_addition(c, d, res);
    printf("%s\n", res);
    big_subtraction(c, d, res, flag);
    printf("%s\n", res);
    big_multiplication(a, b, res);
    printf("%s\n", res);
    return 0;
}
