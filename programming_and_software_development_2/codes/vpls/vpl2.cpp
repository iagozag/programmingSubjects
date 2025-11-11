#include<bits/stdc++.h>
using namespace std;

int main(){
    string word; cin >> word;
    map<char,int> letters;
    vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    for(int i = 0; i < word.size(); i++){
        if(letters.find(word[i]) != letters.end()) letters[word[i]] += 1;
        else letters[word[i]] = 1;
    }

    for(int i = 0; i < vowels.size(); i++){
        if(letters.find(vowels[i]) != letters.end())
            cout << vowels[i] << " " << letters[vowels[i]] << "\n";
    }
}
