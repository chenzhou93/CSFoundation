#include <iostream>

using namespace std;

struct LightHouse{
    int x;
    int y;
};

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

    delete[] lights;
    return 0;
}