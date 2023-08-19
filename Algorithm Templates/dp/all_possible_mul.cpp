#include <bits/stdc++.h>
using namespace std;

void print_total(vector<vector<int>>total){
    for(int i=0; i<total.size(); i++){
        for(int j=0; j<total[i].size(); j++){
            if(total[i][j] == -1) cout<<"(";
            else if(total[i][j] == -2) cout<<")";
            else {
                if(total[i][j-1] > 0) cout<<"  "<<total[i][j];
                else cout<<total[i][j];
            }
        }
        cout<<endl;
    }
}

vector<vector<int>> print_matrix_multiplication(int st, int en){
   vector<vector<int>>total;
   if(st == en){
    vector<int>t;
    t.push_back(-1);
    t.push_back(st);
    t.push_back(-2);
    total.push_back(t);
    print_total(total);
    return total;
   }
   for(int i=st; i<en; i++){
        vector<vector<int>>left = print_matrix_multiplication(st,i);
        vector<vector<int>>right = print_matrix_multiplication(i+1,en);
        for(int j=0; j<left.size(); j++){
            for(int k=0; k<right.size(); k++){
                vector<int>t;
                t.push_back(-1); // {
                for(int it=0; it < left[j].size(); it++){
                    t.push_back(left[j][it]);
                }
                for(int it=0; it < right[k].size(); it++){
                    t.push_back(right[k][it]);
                }
                t.push_back(-2); // }
                total.push_back(t);
            }
        }
   }
   return total;
}

int main(void){
    vector<vector<int>>total = print_matrix_multiplication(1, 3);
    print_total(total);
    return 0;
}
