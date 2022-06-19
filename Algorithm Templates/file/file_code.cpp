#include <stdio.h>
#include <string.h>

/* A demo of how to work with file */

void file_read(char file_name[]){
    FILE *f = fopen(file_name,"r");
    while(1) {
        char ch;
        char o = fscanf(f, "%c", &ch); // in case of EOF output is -1, else output is 1
        if (o == EOF) break;
        printf("%c",ch);
    }
    fclose(f);
}

void file_write(char file_name[]){
    char arr[] = "10 30 40";
    FILE *f = fopen(file_name,"w");
    for(int i=0; i<strlen(arr); i++){
        fprintf(f, "%c", arr[i]);
    }
    fclose(f);
}

int main(){
    char arr[] = "out.txt";
    file_write(arr);
    file_read(arr);
    return 0;
}
