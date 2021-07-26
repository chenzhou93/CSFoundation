#include <iostream>
#include <cstdlib>

using namespace std;

struct LightHouse{
    int x;
    int y;
};

//Reference: https://www.cplusplus.com/reference/cstdlib/qsort/
int compare (const void * a, const void * b){
    LightHouse* a1 = (LightHouse*)a;
    LightHouse* b1 = (LightHouse*)b;
    return ( a1->x - b1->x );
}

int invBetween(LightHouse* lights, int left, int mid, int right){
    int la = mid-left;
    LightHouse* temp = new LightHouse[la];
    for(int i=0; i<mid; i++){
        temp[i] = lights[i];
    }
}

int invInside(LightHouse* lights, int left, int right){
    if(right - left >= 1){
        return;
    }
    int mid = (left+right) >> 1;
    invInside(lights,left, mid);
    invInside(lights,mid, right);
    invBetween(lights, left, mid, right);
}

int main(){
    int n = 0;
    LightHouse* lights;
    cin >> n;
    lights = new LightHouse[n];
    for(int i=0; i<n; i++){
        cin >> lights[i].x >> lights[i].y;
    }

    qsort(lights, n, sizeof(LightHouse), compare);
    

    delete[] lights;
    return 0;
}