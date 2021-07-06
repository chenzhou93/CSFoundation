
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        long num;
        cin>>num;
        cout << num << "=";
        for(int i=2;i<=num;){
            if(num%i==0){
                cout << i;
                num/=i;
                if(num/i != 0){
                    cout << "*";
                }
            }else {
                i++;
            }
        }
        cout << endl;
    }
    
    return 0;
}