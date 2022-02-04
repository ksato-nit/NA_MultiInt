#include <bits/stdc++.h>
#define DMAX 100

using namespace std;

enum mode {UNIFORM, NORMAL, EXP, CAUCHY};

double func(double*, int);
double lcg(mode);

int main(void){
    double S, x[DMAX] = {0};

    int D = 5;
    for(mode M = UNIFORM; M <= CAUCHY; M = static_cast<mode>((static_cast<int>(M) + 1))){
        string filename = "result_MC";
        filename += to_string(M);
        filename += ".dat";
        ofstream outputfile(filename);
        for(int m = 1; m <= 10; ++m){
            int n = (int) pow(2, m);
            double avg = 0;
            for(int k = 0; k < 100; ++k){
                S = 0;
                for(int i = 1; i <= n; ++i){
                    for(int j = 0; j < D; ++j){
                        x[j] = lcg(M);
                    }
                    S += func(x, D);
                }
                S = (pow(2, D) * S) / n;
                avg += S;
            }
            avg = avg / 100;
            outputfile << setprecision(30) << avg << endl;
            //outputfile << setprecision(30) << abs(avg - pow(exp(1) - exp(-1), D)) / (pow(exp(1) - exp(-1), D)) << endl;
        }
        outputfile.close();
    }
    return 0;
}

/* 被積分関数．*/
double func(double* x, int D){
    double e = 0;
    for(int d = 0; d < D; ++d){
        e += -pow(x[d], 2);
    }
    return exp(e);
}

double lcg(mode M){
    random_device r;
    mt19937 mt(r());
    minstd_rand mr(r());
    uniform_real_distribution<> ud(-5, 5);
    normal_distribution<> nd(0, 1);
    exponential_distribution<> ed(1);
    cauchy_distribution<> cd(0, 0.5);

    switch (M){
        case UNIFORM:
            return ud(mr);
        case NORMAL:
            return nd(mr);
        case EXP:
            return ed(mr);
        case CAUCHY:
            return cd(mr);
    }
}
