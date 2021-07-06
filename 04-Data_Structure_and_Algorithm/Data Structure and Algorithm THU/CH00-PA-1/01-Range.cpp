#include <iostream>
using namespace std;

int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b);
}

int binarySearch(int arr[], int size, int value){
    int lo = 0, hi = size;
    while(lo < hi){
        
        int mid = (lo + hi) >> 1;
        if(value < arr[mid]){
            hi = mid;
        }else{
            lo = mid + 1;
        }
    }
    return --lo;
}

int searchRange(int arr[], int left, int right, int size){
    int leftPos = binarySearch(arr, size, left);
    int rightPos = binarySearch(arr, size, right);
    int cnt = 0;
    if(arr[leftPos] == left){
        cnt = rightPos - leftPos + 1;
    }else{
        cnt = rightPos - leftPos;
    }
    if(leftPos == -1){
        cnt = rightPos + 1;
    }
    
    // cout << "left pos: " << leftPos << endl;
    // cout << "right pos: " << rightPos << endl;
    return cnt;
}

int main(){
    int n = 0, m = 0;
    int* arr;
    cin >> n >> m;
    arr = new int[n];
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    
    qsort (arr, n, sizeof(int), compare);

    for(int i=0; i<m; i++){
        int left, right;
        cin >> left >> right;
        cout << searchRange(arr, left, right, n) << endl;
    }


    if(arr){
        delete[] arr;
    }
    return 0;
}