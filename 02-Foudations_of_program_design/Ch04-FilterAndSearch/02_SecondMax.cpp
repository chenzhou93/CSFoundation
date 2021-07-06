#include <iostream>
using namespace std;

int a1, a2;

int main(){
    int n;
    cin >> n;
    if(n>=2){
        cin >> a1 >> a2;
        if(a1 < a2){
            swap(a1, a2);
        }
        for(int i=3; i<=n; i++){
            int num;
            cin >> num;
            //cout << "a1: " << a1 << " a2: " << a2 << endl;
            if(num > a1 && num > a2){
                a2 = a1;
                a1 = num;
            }else if(num > a2 && num < a1){
                a2 = num;
            }
        }  
    }
   
    cout << a2 << endl;
    return 0;
}