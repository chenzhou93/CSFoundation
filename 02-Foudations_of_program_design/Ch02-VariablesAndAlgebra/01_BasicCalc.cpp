#include <iostream>
#include <iomanip> // 注意加上这一行
using namespace std;

const double PI = 3.1415926;
 
int main() {
    double r = 2.52384;
    double res = (double)PI * r * r;
    cout<< fixed << setprecision(4) << res <<endl;
    return 0;
}