/*
    Calculate y = sin(π/4)^2 + sin(π/4)cos(π/4) - cos(π/4）^2
*/

#include <iostream>
#include <iomanip>
#include <math.h> 

using namespace std;

const double PI = 3.14159265;
 
int main() {
    double y = sin(PI/4) * sin(PI/4)  + sin(PI/4)*cos(PI/4) - cos(PI/4) * cos(PI/4);
    cout<< fixed << setprecision(5) << y <<endl; 
    return 0;
}