#include <bits/stdc++.h>
#include <boost/math/constants/constants.hpp>
#define D 6

using namespace std;

double func(double*);
double rec(int, int, double*);
double zero(int, int);
double weight(int, int);
double zeroOfBessel(int);
double Jsquared(int);

int main(void){
    double pi = boost::math::constants::pi<double>();
    ofstream outputfile("result.dat");
    double S;
    auto start = chrono::system_clock::now();
    int n = 24;
    double x[100] = {0};
    S = rec(n, 1, x);
    outputfile << setprecision(30) << abs(S - pow(exp(1) - exp(-1), D)) / pow(exp(1) - exp(-1), D) << endl;
    outputfile.close();
    auto end = chrono::system_clock::now();
    auto duration = end - start;
    cout << "実行時間 : " << chrono::duration_cast<std::chrono::milliseconds>(duration).count() << endl;
    return 0;
}

/* Gauss--Legendre 積分公式を再帰的に適用する．n^D 分点で (k - 1) 番目の変数まで見たときの積分を計算する．*/
double rec(int n, int k, double* x){
    if(k > D){
        return func(x);
    }else{
        double S = 0;
        for(int l = 1; l <= n; ++l){
            x[k] = zero(n, l);
            S += weight(n, l) * rec(n, k + 1, x);
        }
        return S;
    }
}

/* 被積分関数．*/
double func(double* x){
    double s = 0;
    for(int i = 1; i <= D; ++i){
        s += x[i];
    }
    return exp(-s);
}

/* n 次 Legendre 多項式における k 番目の零点を返す．*/
double zero(int n, int k){
    double x, s, v, a, u;
    v = 1 / (n + 0.5);
    a = v * zeroOfBessel(k);
    u = cos(a) / sin(a);

    s = a;
    s += ((u * a - 1) / (8 * a)) * pow(v, 2);
    s += ((6 * pow(a, 2) * (1 + pow(u, 2)) + 25 - u * (31 * pow(u, 2) + 33) * pow(a, 3)) / (384 * pow(a, 3))) * pow(v, 4);

    s += ((u * (2595 + 6350 * pow(u, 2) + 3779 * pow(u, 4))) / 15360) * pow(v, 6);
    s += ((-1073 / 5120.0) * pow(a, -5)) * pow(v, 6);
    s += ((1 + pow(u, 2)) * ( -((31 * pow(u, 2) + 11) / 1024.0) * pow(a, -1) + (u / 512) * pow(a, -2) - (25 / 3072.0) * pow(a, -3) )) * pow(v, 6);

    /*
    s += - (6277237 * pow(u, 6) + 14682157 * pow(u, 4) + 10808595 * pow(u, 2) + 2407755) * u / 3440640.0;
    s += (375733 / 229376.0) * pow(a, -7);
    s += (1 + pow(u, 2)) * ( (3799 * pow(u, 4) + 3810 * pow(u, 2) + 519 / 24576) * pow(a, -1) - ((21 + 31 * pow(u, 2)) * u / 4096) * pow(a, -2) + ((787 * pow(u, 2) + 279) / 49152) * pow(a, -3) - (25 * u / 12288) * pow(a, -4) + (1073 / 40960.0) * pow(a, -5) );
    */

    x = cos(s);
    return x;
}

/* n 次 Legendre 多項式における k 番目のウエイトを返す．*/
double weight(int n, int k){
    double w, s, v, a, u;
    v = 1 / (n + 0.5);
    a = v * zeroOfBessel(k);
    u = cos(a) / sin(a);

    s = 1;
    s += ((u * a + pow(a, 2) - 1) / (8 * pow(a, 2))) * pow(v, 2);
    s += ((81 - 31 * u * a - (3 - 6 * pow(u, 2)) * pow(a, 2) + 6 * u * pow(a, 3) - (27 + 84 * pow(u, 2) + 56 * pow(u, 4)) * pow(a, 4)) / (384 * pow(a, 4))) * pow(v, 4);

    s += ((187 / 96.0) * pow(u, 4) + (295 / 256.0) * pow(u, 2) + (151 / 160.0) * pow(u, 6) + (153 / 1024.0)) * pow(v, 6);
    s += ( (-119 / 768.0) * pow(u, 3) - (35 / 384.0) * pow(u, 5) - (65 / 1024.0) * u ) * pow(a, -1) * pow(v, 6);
    s += ( (5 / 512.0) + (7 / 384.0) * pow(u, 4) + (15 / 512.0) * pow(u, 2) ) * pow(a, -2) * pow(v, 6);
    s += ( (1 / 512.0) * pow(u, 3) - (13 / 1536.0) * u ) * pow(a, -3) * pow(v, 6);
    s += ( (-7 / 384.0) * pow(u, 2) + (53 / 3072.0) ) * pow(a, -4) * pow(v, 6);
    s += ( (3749 / 15360.0) * u) * pow(a, -5) * pow(v, 6);
    s += ( -1125 / 1024.0 ) * pow(a, -6) * pow(v, 6);

    /*
    s += (-21429 / 32768.0) - (27351 / 1024.0) * pow(u, 4) - (3626248438009 / 338228674560.0) * pow(u, 8) - (36941 / 4096.0) * pow(u, 2) - (669667 / 23040.0) * pow(u, 6);
    s += ( (8639 / 6144.0) * pow(u, 3) + (2513 / 8192.0) * u + (7393 / 3840.0) * pow(u, 5) + (997510355 / 1207959552.0) * pow(u, 7) ) * pow(a, -1);
    s += ( (-1483 / 8192.0) * pow(u, 2) - (1909 / 6144.0) * pow(u, 4) - (1837891769 / 12079595520.0) * pow(u, 6) - (371 / 16384.0)) * pow(a, -2);
    s += ( (355532953 / 6039797760.0) * pow(u, 5) + (1849 / 18432.0) * pow(u, 3) + (675 / 16384.0) * u) * pow(a, -3);
    s += ( (-1183 / 24576.0) * pow(u, 2) - (147456121 / 4831838208.0) * pow(u, 4) - (1565 / 98304.0) ) * pow(a, -4);
    s += ( (-19906471 / 6039797760.0) * pow(u, 3) + (6823 / 245760.0) * u) * pow(a, -5);
    s += ( (149694043 / 2415919104.0) * pow(u, 2) - (156817 / 1474560.0)) * pow(a, -6);
    s += ( -76749336551 / 42278584320.0) * u * pow(a, -7);
    s += (568995840001 / 48318382080.0) * pow(a, -8);

    s += (97620617026363819 / 487049291366400.0) * pow(u, 10) + (202966472595331 / 300647710720.0) * pow(u, 8) + (17266857 / 20480.0) * pow(u, 6) + (22973795 / 49152.0) * pow(u, 4) + (3401195 / 32768.0) * pow(u, 2) + (1268343 / 262144.0);
    s += ( (-65272472659909 / 5411658792960.0) * pow(u, 9) - (2717368577869 / 75161927680.0) * pow(u, 7) - (4729993 / 122880.0) * pow(u, 5) - (548439 / 32768.0) * pow(u, 3) - (612485 / 262144.0) * u) * pow(a, -1);
    s += ( (26455 / 262144.0) + (6324614896949 / 3607772528640.0) * pow(u, 8) + (45578037433 / 9663676416.0) * pow(u, 6) + (52739 / 12288.0) * pow(u, 4) + (93673 / 65536.0) * pow(u, 2)) * pow(a, -2);
    s += ( (-181651 / 196608.0) * pow(u, 3) - (40779010513 / 32212254720.0) * pow(u, 5) - (63001776779 / 115964116992.0) * pow(u, 7) - (19795 / 98304.0) * u) * pow(a, -3);
    s += ( (9477 / 262144.0) + (2101713105 / 4294967296.0) * pow(u, 4) + (56281 / 196608) * pow(u, 2) + (184730261873 / 773094113280.0) * pow(u, 6)) * pow(a, -4);
    s += ( (-29273066033 / 96636764160.0) * pow(u, 3) - (488659 / 3932160.0) * u - (38212677741 / 214748364800.0) * pow(u, 5)) * pow(a, -5);
    s += ( (39817 / 491520.0) + (370339107271 / 2319282339840.0) * pow(u, 4) + (996334037 / 4026531840.0) * pow(u, 2)) * pow(a, -6);
    s += ( (16514308061 / 1352914698240.0) * pow(u, 3) - (3258170891 / 15032385536.0) * u) * pow(a, -7);
    s += ( (3354565639447 / 2705829396480.0) - (335149450411 / 721554505728.0) * pow(u, 2)) * pow(a, -8);
    s += ( 1230657354291011 / 48704929136640.0) * u * pow(a, -9);
    s += (-553063956480229 / 2576980377600.0) * pow(a, -10);
    */

    w = (2 * pow(v, 2) * sin(a)) / (Jsquared(k) * a * s);
    return w;
}

/* 0 次の第 1 種 Bessel 関数 J_0 における k 番目の零点を返す．*/
double zeroOfBessel(int k){
    /* TODO: 信頼できる数表を探し，数値を更新する．*/
    double zeros[10] = {2.4048, 5.5201, 8.6537, 11.792, 14.931, 18.071, 21.212, 24.352, 27.493, 30.635};

    if(k <= 10){
        return zeros[k - 1];
    }

    double pi = boost::math::constants::pi<double>();
    double a = pi * (k - 0.25);
    double b = 8 * a;

    double j = a + (1 / b) - 124 / (3 * pow(b, 3.0)) + 120928 / (15 * pow(b, 5)) - 401743168 / (105 * pow(b, 7)) + 1071187749376 / (315 * pow(b, 9));
    return j;
}

/* zeroOfBessel(k) における 1 次 Bessel 関数の 2 乗を返す． */
double Jsquared(int k){
    double pi = boost::math::constants::pi<double>();
    double a = pi * (k - 0.25);
    
    double J = (2 - (7 / (24 * pow(a, 4))) + (151 / (80 * pow(a, 6))) - (172913 / (8064 * pow(a, 8))) + (461797 / (1152 * pow(a, 10))) - (171497088497 / (15206400 * pow(a, 12))) ) / (pi * a);
    return J;
}
