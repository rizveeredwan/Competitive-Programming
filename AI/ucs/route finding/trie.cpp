#include <bits/stdc++.h>
using namespace std;

struct Trie{
    int node;
    Trie *parent=nullptr;
    Trie* create(int node, Trie* parent){
        Trie* t = new Trie();
        t->node = node;
        t->parent = parent;
        return t;
    }
    vector<int> traverse(Trie* node) {
        Trie* current = node;
        vector<int>path;
        while (current != nullptr) {
            path.push_back(current->node);
            current = current->parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

/*Trie* create(int node, Trie* parent){
    Trie* t = new Trie();

}*/

/*int main(){
    Trie t,t1;
    t.node = 10;
    t1.node = 20;
    t1.parent = &t;
    cout<<t1.parent->node<<endl;
}*/
