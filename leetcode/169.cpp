#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sz = nums.size();
        int last_count = 1;
        int last_element = nums[0];
        int best_count = 1;
        int best_element = nums[0];
        for(int i=1; i<sz; i++){
            if(nums[i] == nums[i-1]) {
                last_count++;
            }
            else {
                last_count = 1;
                last_element = nums[i];
            }
            if(last_count > best_count) {
                best_count = last_count;
                best_element = nums[i];
            }
        }
        return best_element;
    }
};

int main(){

}
