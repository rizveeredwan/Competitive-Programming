#include <bits/stdc++.h>
using namespace std;

string string_generator(int n, vector<char>V){
    // generation of random string
    srand(time(0));
    char ch;
    /*vector<char>V;
    /*for(int i=0;i<32;i++){
        ch = 'A'+i;
        cout<<ch<<endl;
    }
    V.push_back('A');
    V.push_back('B');
    V.push_back('C');
    V.push_back('E');*/
    string s= "";
    int idx;
    for(int i=0;i<n;i++){
        idx = rand()%V.size();
        s = s + V[idx];
    }
    cout<<s<<endl;
    return s;
}

void string_matching_case_gen(int text_length, int pattern_length){
    srand(time(0));
    vector<char>characters;
    //pattern generation
    characters.push_back('A');
    characters.push_back('B');
    characters.push_back('C');
    string pattern = string_generator(pattern_length, characters);
    cout<<"pattern "<<pattern<<endl;
    characters.clear();

    //text generation
    characters.push_back('A');
    characters.push_back('B');
    characters.push_back('C');
    //characters.push_back('D');
    string text = string_generator(text_length, characters);
    int i=0, curr_pos=0, gap;
    while(i<text.size()){
        gap = text.size()-i;
        i = i+rand()%gap;
        if((i+pattern_length-1)<=(text_length-1)){
            for(int j=0; j<pattern_length; j++){
                text[i+j] = pattern[j];
            }
            i = i+pattern_length;
        }
        else break;
    }
    cout<<"text "<<text<<endl;
    return;
}

int main(void){
    string_matching_case_gen(30, 5);
    return 0;
}
