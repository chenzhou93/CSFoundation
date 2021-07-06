#include <iostream>

using namespace std;

int main(){
    int isOut[10] = {0};
    int death = 0;
    int cnt = 0;
    int index = 0;
    int n = 10;

    while(death < n-1){
        ++index;
        //cout << "index: " << index << endl;
        if(index > n-1){
            index=0;
        }
        if(!isOut[index]){
            cnt++;
            //cout << "cnt: " << cnt << endl;
        }
        if(cnt == 5){
            //cout << "found" << endl;
            cnt = 0;
            death++;
            int i = index;
            //cout << "i: " << i << endl;
            while(1){
                //cout << "in while loop i: " << i << endl;
                if(i > n-1){
                    i = 0;
                }
                if(!isOut[i]){
                    isOut[i] = 1;
                    break;
                }
                i++;
            }
        }
    }

    for(int j=0; j<10; j++){
        if(!isOut[j]){
            cout << j << endl;
        }
    }
    return 0;
}