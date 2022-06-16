#include <bits/stdc++.h>
using namespace std;

vector<int> randomized_weight(int min_range, int max_range, int n, bool neg_cycle){
        // randomization weight
        vector<int>values;
        int diff = max_range-min_range;
        for(int i=0; i<n; i++){
            values.push_back(rand()%diff + min_range);
        }
        sort(values.begin(), values.end());
        if(neg_cycle == true) {
            int choice = rand()%10+1;
            vector<int>sum;
            int t_sum = 0;
            for(int i=0; i<n; i++) {
                t_sum = t_sum + values[i];
                sum.push_back(t_sum);
            }
            int split_idx;
            int l_sum,r_sum;
            int sol_idx = -1;
            int i=0;
            while (i<choice){
                split_idx = rand()%n;
                l_sum = 0;
                if(split_idx >= 0) {
                    l_sum = sum[split_idx];
                }
                r_sum = 0;
                if(split_idx <= (n-1)) {
                    r_sum = sum[n-1]-sum[split_idx];
                }
                if(l_sum != r_sum) {
                    cout<<l_sum<<" "<<r_sum<<" "<<split_idx<<endl;
                    i++; // a valid solution
                    if(sol_idx == -1)sol_idx = split_idx;
                    else rand()%2==1?sol_idx = split_idx:0;
                }
            }
            if(l_sum > r_sum) {
                for(int i=0; i<split_idx; i++) {
                    values[i] = values[i] * -1;
                }
            }
            else {
                for(int i=split_idx+1; i<n; i++){
                    values[i] = values[i] * -1;
                }
            }
        }
         // using built-in random generator
        random_shuffle(values.begin(), values.end());
        return values;
    }


int main(){
    srand(time(nullptr));
    vector<int> temp = randomized_weight(10, 50, 10, true);
    for(int i=0; i<temp.size(); i++){
        cout<<temp[i]<<" ";
    }
    cout<<endl;
}
