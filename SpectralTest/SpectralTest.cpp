#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#define lld boost::multiprecision::cpp_int
#define llf boost::multiprecision::cpp_dec_float_50
#define T 4
using namespace std;

int main(void){
    lld m, a;
    m = (lld) pow(2, 31);
    a = 1103515245;
    lld h, hd, p, pd, r, s, q, qd, u, v, su, sv1, sv2;
    int t, k, j;
    lld U[T + 1][T + 1] = {0};
    lld V[T + 1][T + 1] = {0};
    lld X[T + 1] = {0};
    lld Y[T + 1] = {0};
    lld z[T + 1] = {0};

    t = 2;
    h = a;
    hd = m;
    p = 1;
    pd = 0;
    r = a;
    s = 1 + a * a;

    q = hd / h;
    u = hd - q * h;
    v = pd - q * p;

    while(u * u + v * v < s){
        s = u * u + v * v;
        hd = h;
        h = u;
        pd = p;
        p = v;

        q = hd / h;
        u = hd - q * h;
        v = pd - q * p;
    }

    u = u - h;
    v = v - p;

    if(u * u + v * v < s){
        s = u * u + v * v;
        hd = u;
        pd = v;
    }

    llf sf(s.str());
    cout << "2 " << sqrt(sf) << endl;

    U[1][1] = -h;
    U[1][2] = p;
    U[2][1] = -hd;
    U[2][2] = pd;

    int sgn = pd < 0 ? 1 : -1;
    V[1][1] = sgn * pd;
    V[1][2] = sgn * hd;
    V[2][1] = sgn * (-p);
    V[2][2] = sgn * (-h);

    while(t < T){
        // ステップ 4.
        ++t;
        r = (a * r) % m;

        U[t][1] = -r;
        for(int l = 2; l < t; ++l){
            U[t][l] = 0;
        }
        U[t][t] = 1;
        for(int l = 1; l < t; ++l){
            U[l][t] = 0;
            V[l][t] = 0;
        }

        for(int l = 1; l < t; ++l){
            V[t][l] = 0;
        }
        V[t][t] = m;

        for(int i = 1; i < t; ++i){
            /* cpp_int と cpp_dec_float50 を相互にキャストすることは標準では不可能．*/
            // q = (lld) round((llf) V[i][1] * r / m);
            llf tmp1(V[i][1]);
            llf tmp2(r);
            llf tmp3(m);
            llf tmpf = tmp1 * tmp2 / tmp3;
            tmpf = round(tmpf);
            lld tmpq(tmpf.str());
            q = tmpq;
            V[i][t] = V[i][1] * r - q * m;
            for(int l = 1; l <= t; ++l){
                U[t][l] += q * U[i][l];
            }
        }

        su = 0;
        for(int l = 1; l <= t; ++l){
            su += U[t][l] * U[t][l];
        }
        s = min(s, su);
        k = t;
        j = 1;

        // ステップ 5 / 6.
        do{
            for(int i = 1; i <= t; ++i){
                sv1 = 0;
                sv2 = 0;
                for(int l = 1; l <= t; ++l){
                    sv1 += V[i][l] * V[j][l];
                    sv2 += V[j][l] * V[j][l];
                }
                if(i != j && 2 * abs(sv1) > sv2){
                    //q = (lld) round((llf) sv1 / sv2);
                    llf tmp1(sv1.str());
                    llf tmp2(sv2.str());
                    llf tmpf = tmp1 / tmp2;
                    tmpf = round(tmpf);
                    lld tmpq(tmpf.str());
                    q = tmpq;
                    su = 0;
                    for(int l = 1; l <= t; ++l){
                        V[i][l] -= q * V[j][l];
                        U[j][l] += q * U[i][l];
                        su += U[j][l] * U[j][l];
                    }
                    k = j;
                }
            }

            // ステップ 6.
            if(j == t){
                j = 1;
            }else{
                ++j;
            }

            if(j == k){
                break;
            }
        }while(true);

        //ステップ 7.
        for(int l = 1; l <= t; ++l){
            X[l] = 0;
            Y[l] = 0;
        }

        k = t;
        for(int j = 1; j <= t; ++j){
            sv1 = 0;
            for(int l = 1; l <= t; ++l){
                sv1 += V[j][l] * V[j][l];
            }
            //z[j] = (lld) floor( sqrt( floor( ((llf) sv1 / (m * m)) * s) ) );
            llf tmp1(sv1);
            llf tmp2(s);
            llf tmp3(m);
            llf tmpr = tmp1 * tmp2 / (tmp3 * tmp3);
            llf tmpfl = floor(tmpr);
            llf tmpf = sqrt(tmpfl);
            tmpf = floor(tmpf);
            lld tmp(tmpf.str());
            z[j] = tmp;
        }

        do{
            if(X[k] != z[k]){
                ++X[k];
                for(int l = 1; l <= t; ++l){
                    Y[l] += U[k][l];
                }

                while(true){
                    ++k;
                    if(k <= t){
                        X[k] = -z[k];
                        for(int l = 1; l <= t; ++l){
                            Y[l] -= 2 * z[k] * U[k][l];
                        }
                        continue;
                    }else{
                        sv1 = 0;
                        for(int l = 1; l <= t; ++l){
                            sv1 += Y[l] * Y[l];
                        }
                        s = min(s, sv1);
                        break;
                    }
                }
            }

            --k;
        }while(k >= 1);

        llf sf(s.str());
        cout << t << " " << sqrt(sf) << endl;
    }

    return 0;
}
