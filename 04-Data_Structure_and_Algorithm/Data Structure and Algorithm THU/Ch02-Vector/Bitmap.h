#ifndef BIT_MAP_H__
#define BIT_MAP_H__

typedef int Rank;

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

class Bitmap{
    private:
    char* M;//bitmap space M
    int N;// N*sizeof(char)*8

    protected:
    void init(int n){
        M = new char[N = (n+7)/8];
        std::memset(M, 0, N);
    }

    public:
    Bitmap(int n = 8){
        init(n);
    }

    Bitmap(char* file, int n = 8){
        init(n);
        FILE* fp = fopen(file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
    }

    ~Bitmap(){
        delete[] M;
        M = NULL;
    }

    void set(int k){
        expand(k);
        M[k>>3] |= (0x80 >> (k&0x07));
    }

    void clear(int k){
        expand(k);
        M[k>>3] &= ~(0x80 >> (k&0x07));
    }

    bool test(int k){
        expand(k);
        return M[k>>3] & (0x80 >> (k&0x07));
    }

    void dump(char* file){
        FILE* fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }

    char* bitsToString(int n){
        expand(n-1);
        char* s = new char[n+1];
        s[n] = '\0';
        for(int i=0; i<n; i++){
            s[i] = test(i) ? '1' : '0';
        }
        return s;
    }

    void expand(int k){
        if(k < 8 * N){
            return;
        }
        int oldN = N;
        char* oldM = M;
        init(2 * k);
        //memcpy_s(M, N, oldM, oldN);
        delete[] oldM;
    }
};

class Bitmap2{
    private:
    Rank* F; Rank N;
    Rank* T; Rank top;

    protected:
    inline bool valid(Rank r){
        return (0<=r)&&(r<top);
    }
    inline bool erased(Rank k){
        return valid(F[k]) && !(T[F[k]] + 1 + k);
    }

    public:
    Bitmap2(Rank n = 8){
        N = n;
        F = new Rank[N];
        T = new Rank[N];
        top = 0;
    }

    ~Bitmap2(){
        delete[] F;
        delete[] T;
    }

    inline void set(Rank k){
        if(test(k)){
            return;
        }

        if(!erased(k)){
            F[k] = top++;
        }

        T[F[k]] = k;
    }

    inline void clear(Rank k){
        if(test(k)){
            T[F[k]] = -1 - k;
        }
    }

    inline bool test(Rank k){
        return valid(F[k]) && (k == T[F[k]]);
    }

};

#endif