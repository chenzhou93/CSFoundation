#include <iostream>

using namespace std;

class GradeCount{
    private:
    int* arr;
    int _n;
    int grade[10];

    public:
    GradeCount(){
        arr = new int[10];
    }
    GradeCount(int n){
        arr = new int[n];
        _n = n;
    }

    GradeCount(int* a, int n){
        arr = new int[n];
        for(int i=0; i<n; i++){
            arr[i] = a[i];
        }
        _n = n;
    }
    
    int& operator[] (int k);
};

int& GradeCount::operator[] (int k){
    for(int i=0; i<_n; i++){
        int index = arr[i]/10;
        if(index >= 0 && index < 11){
            grade[index]++;
        }
    }
    return grade[k];
}

int main(){
    int test[11] = {1,11,21,31,41,51,61,71,81,91,19};
    GradeCount gcnt(test, 11);
    cout << gcnt[3] << endl;
    return 0;
}