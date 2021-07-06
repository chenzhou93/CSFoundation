#include <iostream>
#include "Queue.h"
using namespace std;

struct Customer{
    int window;
    unsigned int time;
};

int bestWindow(Queue<Customer> windows[], int nWin){
    int minSize = windows[0].size(), optiWin = 0;
    for(int i=1; i<nWin; i++){
        if(minSize > windows[i].size()){
            minSize = windows[i].size();
            optiWin = i;
        }
    }
    return optiWin;
}

void simulate(int nWin, int servTime){
    Queue<Customer>* windows = new Queue<Customer>[nWin];
    for(int now = 0; now<servTime; now++){
        if(rand() % (1 + nWin)){
            Customer c;
            c.time = 1 + rand() % 98;
            c.window = bestWindow(windows, nWin);
            windows[c.window].enqueue(c);
        }
        for(int i=0; i<nWin; i++){
            if(!windows[i].empty()){
                if(--windows[i].front().time <= 0){
                    windows[i].dequeue();
                }
            }
        }
    }
    delete[] windows;
}


int main(){
    return 0;
}