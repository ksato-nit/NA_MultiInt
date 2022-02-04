#include <bits/stdc++.h>
#define DMAX 100

using namespace std;

double func(double*, int);
double lcg();

int main(void){
    double S, x[DMAX] = {0};

    random_device r;
    mt19937 mt(r());
    minstd_rand mr(r());
    uniform_real_distribution<> ud(-1, 1);

    for(int D = 2; D <= 20; ++D){
        string filename = "result_MC";
        filename += to_string(D);
        filename += "d.dat";
        ofstream outputfile(filename);
        for(int m = 1; m <= 20; ++m){
            int n = (int) pow(2, m);
            double avg = 0;
            for(int k = 0; k < 100; ++k){
                S = 0;
                for(int i = 1; i <= n; ++i){
                    for(int j = 0; j < D; ++j){
                        x[j] = lcg();
                    }
                    S += func(x, D);
                }
                S = (pow(2, D) * S) / n;
                avg += S;
            }
            avg = avg / 100;
            outputfile << setprecision(30) << abs(avg - pow(exp(1) - exp(-1), D)) / (pow(exp(1) - exp(-1), D)) << endl;
        }
        outputfile.close();
    }
    return 0;
}

/* 被積分関数．*/
double func(double* x, int D){
    double e = 0;
    for(int d = 0; d < D; ++d){
        e += -x[d];
    }
    return exp(e);
}

double lcg(void){
    static long long int x = 15;
    long long int m = (long long int) pow(2, 31);
    int a = 1103515245, c = 12345;
    x = (a * x + c) % m;

    return (2.0 * x / m) - 1.0;
}
