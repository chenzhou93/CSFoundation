#include <iostream>

using namespace std;

int main(){
    for(int i=1; i<=6; i++){
        int cnt=0;

        if(i!=1){
            cnt++;
        }
        if(i==1||i==3){
            cnt++;
        }
        if(i!=6){
            cnt++;
        }
        if(i!=1 && i!=3 && i!=6){
            cnt++;
        }
        if(i==6){
            cnt++;
        }
            
        if(cnt==3){
            if(i==1){
                cout<<"A"<<endl;
            }
            if(i==2){
                cout<<"B"<<endl;
            }
            if(i==3){
                cout<<"C"<<endl;
            }
            if(i==4){
                cout<<"D"<<endl;
            }
            if(i==5){
                cout<<"E"<<endl;
            }
            if(i==6){
                cout<<"F"<<endl;
            }
        }
    }
    return 0;
}