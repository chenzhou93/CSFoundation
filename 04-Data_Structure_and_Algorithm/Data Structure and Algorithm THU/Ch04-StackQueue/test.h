#include <iostream>
using namespace std;

class Test{
    public:
    int _size = 10;
    int size(){
        return _size;
    }
};

class TestChild : public Test{
    public:
    int number;
    void output(){
        cout << size() << endl;
    }
};