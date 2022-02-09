#include <bits/stdc++.h>
#define D 2

using namespace std;

double func(double*);
double lcg(double, double);
void randomPoint(double, double, double*);

int main(void){
    ofstream outputfile("result.dat");
    double S, x[D] = {0};
    double truth = M_PI * (1 - exp(-9));

    random_device r;
    mt19937 mt(r());
    minstd_rand mr(r());
    uniform_real_distribution<> ud(-1, 1);

    for(int m = 1; m <= 20; ++m){
        int n = (int) pow(2, m);
        double avg = 0;
        for(int k = 0; k < 100; ++k){
            S = 0;
            double S1 = 0, S2 = 0, S3 = 0;
            for(int i = 1; i <= n / 2; ++i){
                randomPoint(0, 1.0, x);
                S1 += func(x);
            }
            S += (M_PI * S1) / (n / 2);

            for(int i = 1; i <= (3 * n) / 4; ++i){
                randomPoint(1.0, 2.0, x);
                S2 += func(x);
            }
            S += (3 * M_PI * S2) / ((3 * n) / 4);

            for(int i = 1; i <= n / 4; ++i){
                randomPoint(2.0, 3.0, x);
                S3 += func(x);
            }
            S += (5 * M_PI * S3) / (n / 4);

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
        S *= exp(-pow(x[d], 2));
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

void randomPoint(double r1, double r2, double* x){
    double normSquared;
    do{
        normSquared = 0;
        for(int i = 0; i < D; ++i){
            x[i] = lcg(-r2, r2);
            normSquared += pow(x[i], 2);
        }
    }while(normSquared >= pow(r2, 2) || normSquared <= pow(r1, 2));
}
