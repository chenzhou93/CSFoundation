#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const long N = 1000000;
int isPrime[N] = {0};
int prime[N];
int numPrime;
int totalPrime;

long prime2[N];

void filterPrimeNumbers(){
	isPrime[1] = 1;
	numPrime = 0;
	for (long i = 2; i < N; i++){
		if (!isPrime[i]){
			prime[++numPrime] = i;
			for (long j = 2 * i; j < N; j += i){
                isPrime[j] = 1;
            }
		}
	}
}

int main(){
    filterPrimeNumbers();
    long long L, U;
    cin >> L >> U;
    memset(isPrime, 0, sizeof(isPrime));
	for (int i = 1; i <= numPrime; i++){
		long p = L / prime[i];
		if (p <= 1){
            p = 2;
        }
		for (long j = prime[i]*p; j<=U; j+=prime[i]){
			if (j >= L) {
                isPrime[j-L] = 1;
            }
		}
    }
    if(L==1){
        isPrime[0] = 1;
    }
    totalPrime = 0;
    for(int i=0; i<=U-L; i++){
        if(!isPrime[i]){
            prime2[++totalPrime] = i+L;
        }
    }
    if(totalPrime <=1){
        cout << -1 << endl;
    }else{
        long min = 1000000;
        long max = -1000000;
        long minL, minR, maxL, maxR;

        for(int i=1; i<totalPrime; i++){
            if(prime2[i+1] - prime2[i] > max){
                max = prime2[i+1] - prime2[i];
                maxL = prime2[i];
                maxR = prime2[i+1];
            }

            if(prime2[i+1] - prime2[i] < min){
                min = prime2[i+1] - prime2[i];
                minL = prime2[i];
                minR = prime2[i+1];
            }
        }

        cout << minL << ' ' << minR << endl;
        cout << maxL << ' ' << maxR << endl;
    }
	
    return 0;
}