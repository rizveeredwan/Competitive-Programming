#include <bits/stdc++.h>
using namespace std;

int order(char a[], char b[], char c[], char d[]) {
    if(strlen(a) > strlen(b)) {
        strcpy(c,a);
        strcpy(d,b);
        return 0; // order did not change
    }
    else if(strlen(a) < strlen(b)){
        strcpy(c,b);
        strcpy(d,a);
        return 1; // order changed
    }
    else {
        if(strcmp(a,b) >= 0) {
            strcpy(c,a);
            strcpy(d,b);
            return 0;
        }
        else {
            strcpy(c,b);
            strcpy(d,a);
            return 1;
        }
    }
}

void reverse_array(char res[], int k){
    char temp;
    for(int i=0;i<=k/2;i++){
        temp = res[i];
        res[i] = res[k-i];
        res[k-i] = temp;
    }
}

void big_addition(char a[], char b[], char res[]){
    int d1,d2,s,c=0;
    int i,j,k;
    res[0] = '\0'; // ending null character
    for(i=strlen(a)-1,j=strlen(b)-1,k=1; i>=0; i--,j--,k++){
        d1 = a[i]-'0';
        d2 = 0;
        if(j>=0) {
            d2 = b[j]-'0';
        }
        s = d1 + d2 + c;
        res[k] = (s%10)+'0';
        c = s/10;
    }
    if(c>0) res[k] = c+'0';
    else k--;
    reverse_array(res,k);
    return;
}

void big_subtraction(char a[], char b[], char res[], int shift_flag){
    if(strcmp(a,b) == 0) {
        res[0] = '0';
        res[1] = '\0';
        return;
    }
    int d1,d2,s,c=0;
    int i,j,k;
    res[0] = '\0'; // ending null character
    for(i=strlen(a)-1,j=strlen(b)-1,k=1; i>=0; i--,j--,k++){
        d1 = a[i]-'0';
        d2 = c;
        if(j>=0) {
            d2 = d2+b[j]-'0';
        }
        if(d1>=d2) {
            s=d1-d2;
            c=0;
        }
        else {
            s=d1+10-d2;
            c=1;
        }
        res[k]=s+'0';
    }
    assert(c==0);
    if(shift_flag == 1) {
        // need to put a minus
        res[k] = '-';
    }
    else {
        k--;
    }
    reverse_array(res,k);
    k = strlen(res);
    if(k>0) {
        // removing initial zeros
        int init;
        if(res[0] == '-') {
            i=1;
            init=i;
        }
        else {
            i=0;
            init=0;
        }
        for(;i<k;i++){
            if(res[i] == '0') {
                // searching for the first non zero digit position
                continue;
            }
            else {
                // first non zero digit position
                for(j=init; i<=k ;j++,i++){
                    res[j]=res[i];
                }
                break;
            }
        }
    }
    return;
}

void big_multiplication(char a[], char b[], char res[]){
    int l,c,d1,d2,s;
    char temp2[30],temp[30];
    res[0] = '0';
    res[1] = '\0';
    for(int i=strlen(b)-1,k=0,level=0; i>=0; i--,k++, level++){
        temp[0] = '\0';
        l=1;
        for(; l<=k; l++){
            temp[l] = '0';
        }
        c = 0;
        for(int j=strlen(a)-1; j>=0; j--,l++){
            d1 = a[j] - '0';
            d2 = b[i] - '0';
            s = d1*d2 + c;
            temp[l] = s%10+'0';
            c = s/10;
        }
        if(c != 0) temp[l] = c+'0';
        else l--;
        reverse_array(temp, l);
        big_addition(temp,res,temp2);
        strcpy(res,temp2);
    }
    return;
}

/*int main(void){
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
}*/
