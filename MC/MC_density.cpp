#include <bits/stdc++.h>
#define D 2

using namespace std;

double func(double*);
double lcg(double, double);

int main(void){
    ofstream outputfile("result.dat");
    double S, x[D] = {0};
    double truth = pow(M_PI / 2, D);

    random_device r;
    mt19937 mt(r());
    minstd_rand mr(r());
    uniform_real_distribution<> ud(-1, 1);

    for(int m = 4; m <= 19; ++m){
        int n = (int) pow(2, m);
        double avg = 0;
        for(int k = 0; k < 100; ++k){
            S = 0;
            double S1 = 0, S2 = 0, S3 = 0;

            /* 分点数を大きく 8 分割し，領域 1, 3, 7, 9 に 2, 領域 2, 4, 6, 8 に 4，領域 5 に 2 を割り当てる．*/
            for(int i = 1; i <= n / 16; ++i){
                x[0] = lcg(-1.0, -1.0 / 3);
                x[1] = lcg(1.0 / 3, 1.0);
                S1 += func(x);
            }
            for(int i = 1; i <= n / 16; ++i){
                x[0] = lcg(1.0 / 3, 1.0);
                x[1] = lcg(1.0 / 3, 1.0);
                S1 += func(x);
            }
            for(int i = 1; i <= n / 16; ++i){
                x[0] = lcg(-1.0, -1.0 / 3);
                x[1] = lcg(-1.0, -1.0 / 3);
                S1 += func(x);
            }
            for(int i = 1; i <= n / 16; ++i){
                x[0] = lcg(1.0 / 3, 1.0);
                x[1] = lcg(-1.0, -1.0 / 3);
                S1 += func(x);
            }
            S += (4 * (4.0 / 9) * S1) / (n / 4);

            for(int i = 1; i <= n / 8; ++i){
                x[0] = lcg(-1.0 / 3, 1.0 / 3);
                x[1] = lcg(1.0 / 3, 1.0);
                S2 += func(x);
            }
            for(int i = 1; i <= n / 8; ++i){
                x[0] = lcg(-1.0, -1.0 / 3);
                x[1] = lcg(-1.0 / 3, 1.0 / 3);
                S2 += func(x);
            }
            for(int i = 1; i <= n / 8; ++i){
                x[0] = lcg(1.0 / 3, 1.0);
                x[1] = lcg(-1.0 / 3, 1.0 / 3);
                S2 += func(x);
            }
            for(int i = 1; i <= n / 8; ++i){
                x[0] = lcg(-1.0 / 3, 1.0 / 3);
                x[1] = lcg(-1.0, -1.0 / 3);
                S2 += func(x);
            }
            S += (4 * (4.0 / 9) * S2) / (n / 2);

            for(int i = 1; i <= (n / 4) + n; ++i){
                x[0] = lcg(-1.0 / 3, 1.0 / 3);
                x[1] = lcg(-1.0 / 3, 1.0 / 3);
                S3 += func(x);
            }

            S += ((4.0 / 9) * S3) / ((n / 4) + n);
            avg += S;
        }
        avg = avg / 100;
        outputfile << setprecision(30) << abs(avg - truth) / truth << endl;
    }
    outputfile.close();
    return 0;
}

/* 被積分関数．*/
double func(double* x){
    double S = 1;
    for(int d = 0; d < D; ++d){
        S *= 1 / (1 + pow(x[d], 2));
    }
    return S;
}

/* [b1, b2] 内の一様乱数を線形合同法により生成する．*/
double lcg(double b1, double b2){
    if(b1 > b2){
        swap(b1, b2);
    }
    static long long int x = 15;
    long long int m = (long long int) pow(2, 31);
    int a = 1103515245, c = 12345;
    x = (a * x + c) % m;

    return ((b2 - b1) * x / m) - b2;
}
