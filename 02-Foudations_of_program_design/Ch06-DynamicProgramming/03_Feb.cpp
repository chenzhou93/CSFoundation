#include <iostream>
using namespace std;

int feb(int n){
    if(n<2){
        return 1;
    }
    int a=0, b=1;
    int c = 0;
    for(int i=1; i<=n; i++){
        c = a+b;
        a = b;
        b = c;
    }
    return c;
}

int main(){
    int n;
    while (cin >> n) {
       cout << feb(n) << endl;
    }
    return 0;
}