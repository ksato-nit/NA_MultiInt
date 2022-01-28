#include <bits/stdc++.h>
#include <boost/math/constants/constants.hpp>

using namespace std;

double zeroOfBessel(int);

int main(void){
    cout << Jsquared(1) << endl;
    return 0;
}

/* 0 次の第 1 種 Bessel 関数 J_0 における k 番目の零点を返す．*/
double zeroOfBessel(int k){
    double pi = boost::math::constants::pi<double>();
    double a = pi * (k - 0.25);
    double b = 8 * a;

    double j = a + 1 / b - 124 / (3 * pow(b, 3.0)) + 120928 / (15 * pow(b, 5)) - 401743168 / (105 * pow(b, 7));
    return j;
}

/* zeroOfBessel(k) における 1 次 Bessel 関数の 2 乗を返す． */
double Jsquared(int k){
    double pi = boost::math::constants::pi<double>();
    double a = pi * (k - 0.25);
    
    double J = (2 - (7 / (24 * pow(a, 4))) + (151 / (80 * pow(a, 6))) - (172913 / (8064 * pow(a, 8)))) / (pi * a);
    return J;
}