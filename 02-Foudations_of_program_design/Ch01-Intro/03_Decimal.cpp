/*
    Calculate 1+1/(1+1/(1+1/5))
*/
#include <iostream>
#include <iomanip>
#include <math.h> 

using namespace std;
 
int main() {
    double t = (double) 1.0/5.0;
    //cout << t << endl;
    double a = (double)(1.0+t);
    //cout << a << endl;
    double b = (double)1.0/a;
    //cout << b << endl;
    double c = (double)1.0+b;
    //cout << c << endl;
    double d = (double)1.0/c;
    //cout << d << endl;

    double y = (double)1.0 + d;
    cout<< fixed << setprecision(4) << y <<endl; 
    return 0;
}