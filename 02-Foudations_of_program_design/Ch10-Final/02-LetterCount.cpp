#include <iostream>
#include <string>

using namespace std;

int main(){
    string s;
    int Q;
    cin >> s;
    cin >> Q;
    
    for(int i=0; i<Q; i++){
        int alpha[26] = {0};
        int left, right;
        cin >> left >> right;

        for(int j=left; j<=right; j++){
            alpha[s[j] - 'a']++;
        }
        for(int k=0; k<26; k++){
            if(alpha[k] != 0){
                char ch = (char)k+'a';
                cout << ch << ':' << alpha[k] << ' ';
            }
        }
        cout << endl;
    }

    return 0;
}