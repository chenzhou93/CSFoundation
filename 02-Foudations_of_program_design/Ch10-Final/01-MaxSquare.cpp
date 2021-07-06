#include <iostream>

using namespace std;
int arr[100000][2];


int main(){
    int n = 0;
    int xMax, xMin, yMax, yMin;
    cin >> n;
    cin >> arr[0][0] >> arr[0][1];
    xMax = xMin = arr[0][0];
    yMax = yMin = arr[0][1];

    for(int i=1; i<n; i++){
        
        cin >> arr[i][0] >> arr[i][1];
        if(arr[i][0] > xMax){
            xMax = arr[i][0];
        }else if(arr[i][0] < xMin){
            xMin = arr[i][0];
        }

        if(arr[i][1] > yMax){
            yMax = arr[i][1];
        }else if(arr[i][1] < yMin){
            yMin = arr[i][1];
        }
        
    }

    // cout << "xMax= " << xMax << endl;
    // cout << "xMin= " << xMin << endl;
    // cout << "yMax= " << yMax << endl;
    // cout << "yMin= " << yMin << endl;

    int x = xMax - xMin;
    //cout << "x= " << x << endl;
    int y = yMax - yMin;
    //cout << "y= " << y << endl;
    
    int res = x > y ? x : y;

    cout << res << endl;
    


    return 0;
}