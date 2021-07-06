#include <iostream>

using namespace std;
int x;

int func(int n){
    if(n == 1){
        return x;
    }
    if(n == 0){
        return 0;
    }

    return func(n-1) + func(n/2) + func(n/3);
}

int main(){
    int n;
    cin >> x >> n;

    cout << func(n) << endl;
    
    return 0;
}