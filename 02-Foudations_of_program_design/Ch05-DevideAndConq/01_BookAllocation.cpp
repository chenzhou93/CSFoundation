#include <iostream>
using namespace std;

int num;
int take[25];
int n;

bool assigned[25];

int like[25][25];

void Try(int id){
    if(id == n){
        num++;

        for(int i=0; i<n; i++){
            cout << take[i]+1 << ' ';
        }
        cout << endl;
        return;
    }

    for(int book=0; book <= n-1; book++){
        if((like[book][id] == 1) && !assigned[book]){
            take[id] = book;
            assigned[book] = true;

            Try(id+1);
            assigned[book] = false;
        }
    }
}

int main(){
    num = 0;
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> like[i][j];
        }
    }

    for(int book=0; book<n; book++){
        assigned[book] = false;
    }

    Try(0);

    //cout << num << " ways" << endl;

    return 0;
}