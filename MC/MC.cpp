#include <bits/stdc++.h>
#define D 2

using namespace std;

double func(double*);

int main(void){
    ofstream outputfile("result.dat");
    double S, x[D] = {0};

    random_device r;
    mt19937 mt(r());
    uniform_real_distribution<> ud(-1, 1);

    for(int n = 10; n < 10000; ++n){
        S = 0;
        for(int i = 1; i <= n; ++i){
            for(int d = 0; d < D; ++d){
                x[d] = ud(mt);
            }
            S += func(x);
        }
        S = (pow(2, D) * S) / n;
        outputfile << setprecision(30) << abs(S - pow(exp(1) - exp(-1), D)) / (pow(exp(1) - exp(-1), D)) << endl;
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
