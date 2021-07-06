#include <iostream>
using namespace std;

int cnt = 0;

void stair(int n, int x, int y){
    if(n == 0){
        cnt++;
        return;
    }
    if(n < 0){
        return;
    }

    if(n >= x){
        stair(n-x, x, y);
    }
    if(n >= y){
        stair(n-y, x, y);
    }
}

int main(){
    int n = 0, x = 0, y = 0;
    cin >> n >> x >> y;

    if(x == y){
        if(n%x == 0){
            cout << 1 << endl;
        }else{
            cout << "sorry" << endl;
        }
    }

    stair(n, x, y);

    if(cnt != 0){
        cout << cnt << endl;
    }else{
        cout << "sorry" << endl;
    }

    return 0;
}