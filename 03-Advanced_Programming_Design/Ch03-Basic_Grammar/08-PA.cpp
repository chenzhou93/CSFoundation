#include <iostream>
using namespace std;

class ArraySort{
    private:
    void mySort(int* array, int size);
    public:
    //overload operator ()
    void operator()(int* array, int size){
        mySort(array, size);
    }
};

//Bubble Sort
void ArraySort::mySort(int* array, int size){
    for(int i=0; i<size-1; i++){
        for(int j=0; j<size-i-1; j++){
            if(array[j] < array[j+1]){
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

int main(){
    //test case
    int arr[5] = {1,2,3,4,5};
    int size = 5;
    //test function operator overloading
    ArraySort obj;
    obj(arr, size);
    //output result after sort
    for(int i=0; i<5; i++){
        cout << arr[i] << ' ';
    }
    cout << endl;
    return 0;
}