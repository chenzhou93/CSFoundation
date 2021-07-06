#include <iostream>
#include <iomanip> // 注意加上这一行
#include <cmath>
using namespace std;
  
int main() {
    double a, b, c;
    cin >> a >> b >> c;
    double s = (a+b+c)/2.0;
    
    if(a+b > c && b+c > a && a+c>b){
        double area = sqrt(s * (s-a) * (s-b) * (s-c));
        cout<< fixed << setprecision(2) << area <<endl;
    }

    return 0;
}