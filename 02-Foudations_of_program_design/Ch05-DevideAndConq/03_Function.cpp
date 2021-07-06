#include <iostream>

using namespace std;

int func(int x){
    if(x==1){
        return 1;
    }
    if(x > 1 && x%2 != 0){
        return func((x-1)/2) + func((x+1)/2);
    }else if(x > 1 && x%2 == 0){
        return func(x/2);
    }
}

int main(){
    int N;
    cin >> N;
    for(int i=0; i<N; i++){
        int x;
        cin >> x;
        cout << func(x) << endl;
    }
    return 0;
}