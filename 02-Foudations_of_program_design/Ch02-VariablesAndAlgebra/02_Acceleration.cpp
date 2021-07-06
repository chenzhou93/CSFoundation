#include <iostream>
#include <iomanip> // 注意加上这一行
using namespace std;
 
int main() {
    int v,t;
    cin >> v >> t;
    double res = (double)v/t;
    cout<< fixed << setprecision(4) << res <<endl;
    return 0;
}