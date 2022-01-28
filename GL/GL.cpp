#include <bits/stdc++.h>
#include <boost/math/constants/constants.hpp>

using namespace std;

double zero(int, int);
double weight(int, int);
double zeroOfBessel(int);
double Jsquared(int);

int main(void){
    return 0;
}

/* n 次 Legendre 多項式における k 番目の零点を返す．*/
double zero(int n, int k){
    double x, s, v, a, u;
    v = 1 / (n + 0.5);
    a = v * zeroOfBessel(k);
    u = cos(a) / sin(a);

    s = a;
    s += (u * a - 1) / (8 * a);
    s += (6 * pow(a, 2) * (1 + pow(u, 2)) + 25 - u * (31 * pow(u, 2) + 33) * pow(a, 3)) / (384 * pow(a, 3));

    s += (u * (2595 + 6350 * pow(u, 2) + 3779 * pow(u, 4))) / 15360;
    s += (-1073 / 5120.0) * pow(a, -5);
    s += (1 + pow(u, 2)) * ( -((31 * pow(u, 2) + 11) / 1024.0) * pow(a, -1) + (u / 512) * pow(a, -2) - (25 / 3072.0) * pow(a, -3) );

    //s += - (6277237 * pow(u, 6) + 14682157 * pow(u, 4) + 10808595 * pow(u, 2) + 2407755) * u / 3440640.0;
    //s += (375733 / 229376.0) * pow(a, -7);
    //s += (1 + pow(u, 2)) * ( (3799 * pow(u, 4) + 3810 * pow(u, 2) + 519 / 24576) * pow(a, -1) - ((21 + 31 * pow(u, 2)) * u / 4096) * pow(a, -2) + ((787 * pow(u, 2) + 279) / 49152) * pow(a, -3) - (25 * u / 12288) * pow(a, -4) + (1073 / 40960.0) * pow(a, -5) );

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
    s += (u * a + pow(a, 2) - 1) / (8 * pow(a, 2));
    s += (81 - 31 * u * a - (3 - 6 * pow(u, 2)) * pow(a, 2) + 6 * u * pow(a, 3) - (27 + 84 * pow(u, 2) + 56 * pow(u, 4)) * pow(a, 4)) / (384 * pow(a, 4));

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

    double j = a + (1 / b) - 124 / (3 * pow(b, 3.0)) + 120928 / (15 * pow(b, 5)) - 401743168 / (105 * pow(b, 7));
    return j;
}

/* zeroOfBessel(k) における 1 次 Bessel 関数の 2 乗を返す． */
double Jsquared(int k){
    double pi = boost::math::constants::pi<double>();
    double a = pi * (k - 0.25);
    
    double J = (2 - (7 / (24 * pow(a, 4))) + (151 / (80 * pow(a, 6))) - (172913 / (8064 * pow(a, 8))) + (461797 / (1152 * pow(a, 10)))) / (pi * a);
    return J;
}
