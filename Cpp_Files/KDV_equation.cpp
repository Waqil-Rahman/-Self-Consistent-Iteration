#include <iostream>
#include <iomanip>
#include <cmath>
#include <valarray>
using namespace std;

valarray<long double> F(const long double &t, const valarray<long double> &u){
    /* du/dt = f(t,u) = {  u0
                         3(u1)^2 + (u1)
     since a =0,c=1(given) we get the above
    */
    valarray<long double> f(u.size());
    // u[0] = dq/dt, u[1] = dp/dt
    //Insert the relevant equations into the f valarray
    f[0] = u[1];
    f[1] = 3.0*pow(static_cast <long double>(u[0]),2.0) + u[0];
    return f;
} //This function will return the correct values of dp/dt and dq/dt by using a valarray<valarray<... in main()

valarray<long double> RK2(const long double &t, const valarray<long double> &u, const long double dt, valarray<long double> f(const long double&, const valarray<long double>&)){
    unsigned long long m = u.size();
    //This allows for us to get the value of the size of the valarray we are using to stay consistent
    valarray<long double> k1(m), k2(m);
    //This initialises valarrays of the correct size
    k1 = dt * f(t, u);
    //Since we call on function f and don't declare any specific valarray we are able to manipulate the function to our use different valarrays
    k2 = dt * f(t + 0.5 * dt, u + 0.5 * k1);
    return u + k2;
} //The above formula is used the lecture notes - Page 5 of ODEs

int main() {
    
    long double t_initial = 0.;
    long double t_final = 10.0;
    int n = 100000;
    long double t_delta = (t_final-t_initial)/static_cast<long double>(n);
    valarray<long double> T(n+2);   //[0],T[1],...,T[n],T[n+1]
    //Given from question

    valarray<valarray<long double>> U(n+2);
    valarray<long double> E(n+2);
    valarray<long double> e(n+2);

    //set initial data such that U(0) = {q(0),p(0)} = {-0.5,0}
    U[0] = {-0.5, 0.};

    for(int j=0; j<=n; j++){
        T[j] = t_initial + static_cast<long double>(j)*t_delta;
        //given in question
        U[j+1] = RK2(T[j], U[j], t_delta, F);
        //We use the +1 as we already have been given the initial conditions, we do not want to overwrite it - we also find the 0th value of each valarray without the need for 2 'for' loops
        E[j] = static_cast<long double>(0.5 * U[j][1]*U[j][1]) - static_cast<long double>(U[j][0]*U[j][0]*U[j][0]) - static_cast<long double>(0.5 *U[j][0]*U[j][0]);
        //E(t) = 0.5(p^2) + (V(q)) = 0.5(p*p) - (q*q*q) -(0.5*q*q)
        e[j] = U[j][0] - static_cast<long double>(-0.5/(cosh(0.5*T[j])*cosh(0.5*T[j])));
        //error = q(t) - (-0.5sech^2(0.5*t) = q(t) - (-0.5/cosh^2(0.5*t))
        //We have to use cosh identity instead of sech as only cosh is cmath library
    }

    // Write header
#define SP << setw(26) << setprecision(10) <<    // save some repetition when writing
    cout << "t" SP "q(t)" SP "p(t)" SP "E(t)" SP "e(t)" << endl;

    int i = 0;
    while (i <= n){
        cout << T[i] SP U[i][0] SP U[i][1] SP E[i] SP e[i] << endl;
        i = i + 10000;
        //We use a while function and this equation to output the only relevant time intervals for i=0,i=1...i=10
    }
    return 0;

}

