#include <iostream>
using namespace std;

int Hab[1000][1000];
int Vab[1000][1000];
int N,M;
int maxValue = -1;

void pathSearch(int x, int y, char dir, int sum){
    //cout << "call search " << x << y << dir << sum << endl;
    if(dir == 'v' && x != 0){
        sum += Vab[x-1][y];
    }

    if(dir == 'h' && y != 0){
        sum += Hab[x][y-1];
    }

    if(x == N-1 && y== M-1){
        if(sum > maxValue){
            maxValue = sum;
        }
        return;
    }

    //cout << "x:" << x << ", y:" << y << ",sum:" << sum << endl;
    //cout << "max: " << maxValue << endl;
    if(x+1 < N){
        pathSearch(x+1, y, 'v', sum);
    }
    
    if(y+1 < M){
        pathSearch(x, y+1, 'h', sum);
    }
    
}

int main(){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> Hab[i][j];
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> Vab[i][j];
        }
    }

    pathSearch(0, 0, 'v', 0);

    cout << maxValue << endl;

    return 0;
}