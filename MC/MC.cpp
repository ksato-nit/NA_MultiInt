#include <bits/stdc++.h>
#define D 2

using namespace std;

double func(double*);
double lcg();

int main(void){
    ofstream outputfile("result.dat");
    double S, x[D] = {0};

    random_device r;
    mt19937 mt(r());
    minstd_rand mr(r());
    uniform_real_distribution<> ud(-1, 1);
    double truth = pow(M_PI / 2, D);

    for(int m = 1; m <= 20; ++m){
        int n = (int) pow(2, m);
        double avg = 0;
        for(int k = 0; k < 100; ++k){
            S = 0;
            for(int i = 1; i <= n; ++i){
                for(int j = 0; j < D; ++j){
                    x[j] = lcg();
                }
                S += func(x);
            }
            S = (pow(2, D) * S) / n;
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

double lcg(void){
    static long long int x = 15;
    long long int m = (long long int) pow(2, 31);
    int a = 1103515245, c = 12345;
    x = (a * x + c) % m;

    return (2.0 * x / m) - 1.0;
}
