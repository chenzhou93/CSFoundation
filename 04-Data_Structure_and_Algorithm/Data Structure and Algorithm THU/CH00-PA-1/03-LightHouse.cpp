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

long invBetween(LightHouse* lights, long left, long mid, long right){
    //cout << "lights[left] " << lights[left].x << lights[left].y <<  "lights[right] " << lights[right].x << lights[right].y << endl;
    long total;
    LightHouse* A = lights+left;
    long lb = mid - left;
    LightHouse* L = new LightHouse[lb];
    for(long i=0; i<lb; i++){
        L[i] = A[i];
    }

    long lc = right - mid;
    LightHouse* R = lights + mid;

    for(long i=0, j=0, k=0; j<lb;){
        if((lc <= k)||(L[j].y <= R[k].y)){
            A[i++] = L[j++];
            //add total here
            //cout << L[j].y << ", " << R[k].y << endl;
            total = lb - j + 1;
        }

        if((k<lc) && (R[k].y < L[j].y)){
            A[i++] = R[k++];
        }
    }

    return total;
}

long invInside(LightHouse* lights, long left, long right){
    if(right - left < 2){
        return 0;
    }
    //cout << "left " << left << " right " << right << endl;
    long mid = (left+right) >> 1;
    long leftTotal = invInside(lights,left, mid);
    long rightTotal = invInside(lights,mid, right);
    long mergeTotal = invBetween(lights, left, mid, right);
    //cout << leftTotal << ", " << rightTotal << ", " << mergeTotal << endl;
    return leftTotal + rightTotal + mergeTotal;
}

int main(){
    long n = 0;
    LightHouse* lights;
    cin >> n;
    lights = new LightHouse[n];
    for(int i=0; i<n; i++){
        cin >> lights[i].x >> lights[i].y;
    }

    qsort(lights, n, sizeof(LightHouse), compare);
    cout << invInside(lights, 0, n-1) << endl;

    delete[] lights;
    return 0;
}