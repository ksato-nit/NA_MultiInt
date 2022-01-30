#include <bits/stdc++.h>
#define D 4

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

    for(int m = 1; m <= 25; ++m){
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
        outputfile << setprecision(30) << abs(avg - pow(exp(1) - exp(-1), D)) / (pow(exp(1) - exp(-1), D)) << endl;
    }
    outputfile.close();
    return 0;
}

/* 被積分関数．*/
double func(double* x){
    double e = 0;
    for(int d = 0; d < D; ++d){
        e += -x[d];
    }
    return exp(e);
}

double lcg(void){
    static long long int x = 15;
    long long int m = (long long int) pow(2, 31);
    int a = 65539, c = 0;
    x = (a * x + c) % m;

    return (2.0 * x / m) - 1.0;
}
