#include <bits/stdc++.h>
using namespace std;

//C++ implementation of fenwick tree/binary index tree  

struct FenwickTree{
	
	//tree to store the memory 
	vector<int>tree;
	
	void initialize(int max_index){
		//max_index: max_index in the tree array, index [0: max_index]
		//initialization of the array 
		tree.clear();
		for(int i=0;i<=max_index;i++){
			tree.push_back(0);
		}
	}
	
	//query from fenwick tree 
	int query(int idx){
		int sum=0;
		while(idx>0){
			sum += tree[idx];
			idx = idx-(idx & (-idx));
		}
		return sum;
	}
	
	//update of fenwicktree
	void update(int idx, int value){
		//updating the idx of tree with value 
		while(idx<(int)tree.size()){
			tree[idx] += value;
			idx = idx+ (idx & (-idx));
		}
	}
	
};

int main(void){
	struct FenwickTree fen=FenwickTree();
	fen.initialize(16);
	//array 
	int arr[] = {0,1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
	//updating
	for(int i=1;i<=16;i++){
		fen.update(i,arr[i]);
	}
	//query 
	for(int i=1;i<=16;i++){
		cout<<fen.query(i)<<endl;
	}
	
}
