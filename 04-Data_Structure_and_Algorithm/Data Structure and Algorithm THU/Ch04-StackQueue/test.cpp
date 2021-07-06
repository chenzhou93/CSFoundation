#include "test.h"
#include <iostream>
using namespace std;

int main(){
    TestChild test;
    cout << test.size() << endl;
    test.output();
    return 0;
}