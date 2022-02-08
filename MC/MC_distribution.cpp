#include <bits/stdc++.h>
#define DMAX 100

using namespace std;

enum mode {UNIFORM, NORMAL, EXP, CAUCHY};

double func(double*, int);
double lcg(mode);

int main(void){
    double S, x[DMAX] = {0};

    int D = 1;
    for(mode M = UNIFORM; M <= CAUCHY; M = static_cast<mode>((static_cast<int>(M) + 1))){
        string filename = "result_MC";
        filename += to_string(M);
        filename += ".dat";
        ofstream outputfile(filename);
        for(int m = 10; m <= 10; ++m){
            int n = (int) pow(2, m);
            double avg = 0;
            for(int k = 99; k < 100; ++k){
                S = 0;
                for(int i = 1; i <= n; ++i){
                    for(int j = 0; j < D; ++j){
                        x[j] = lcg(M);
                    }
                    S += func(x, D);
                }
                S = S * pow(10, D) / n;
                cout << S << endl;
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
    double f = 1;
    for(int d = 0; d < D; ++d){
        f *= exp(-x[d] * x[d]);
    }
    cout << f << endl;
    return f;
}

double lcg(mode M){
    random_device r;
    mt19937 mt(r());
    minstd_rand mr(r());
    uniform_real_distribution<> ud(-5, 5);
    normal_distribution<> nd(0, 1);
    exponential_distribution<> ed(1);
    cauchy_distribution<> cd(0, 0.5);

    double ret = 0;
    do{
        switch (M){
            case UNIFORM:
                ret = ud(mr);
                break;
            case NORMAL:
                ret = nd(mr);
                break;
            case EXP:
                ret = ed(mr);
                break;
            case CAUCHY:
                ret = cd(mr);
                break;
        }
    }while(abs(ret) >= 5);

    return ret;
}
