#include <iostream>
using namespace std;

int n, m;
long matrix[100][100];

void add(int x1, int y1, int x2, int y2, int d){
    for(int i=x1; i<=x2; i++){
        for(int j=y1; j<=y2; j++){
            matrix[i][j] += d;
        }
    }
}

void exchange(int x1, int x2){
    for(int j=1; j<=m; j++){
        int tmp = matrix[x1][j];
        matrix[x1][j] = matrix[x2][j];
        matrix[x2][j] = tmp;
    }
}

void query(int x, int y){
    cout << matrix[x][y] << endl;
}

int main(){
    int numOfOps;
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin >> matrix[i][j];
        }
    }

    cin >> numOfOps;
    for(int i=0; i<numOfOps; i++){
        char operation;
        cin >> operation;
        if(operation == 'A'){
            int x1,y1,x2,y2,d;
            cin >> x1 >> y1 >> x2 >> y2 >> d;
            add(x1,y1,x2,y2,d);
        }else if(operation == 'E'){
            int x1, x2;
            cin >> x1 >> x2;
            exchange(x1, x2);
        }else if(operation == 'Q'){
            int x,y;
            cin >> x >> y;
            query(x, y);
        }
    }


    return 0;
}