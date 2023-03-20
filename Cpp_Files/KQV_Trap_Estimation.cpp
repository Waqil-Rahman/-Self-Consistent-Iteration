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

//We use the pre-defined function Hermit-2 as it uses the trapezium rule without having to alter the function F values
valarray<long double> H2(const long double &t1, const valarray<long double> &u1, const long double dt, valarray<long double> f(const long double&, const valarray<long double>&)){
    long double t2 = t1 + dt; //This increases the time by delta_t starting from t_initial
    unsigned int imax = 10; //This is the maximum number of self-consistent iterations (10) that will be used
    valarray<long double> u2 = u1; //This sets initial guess for the implicit ODE
    for(int i = 0; i<=imax; ++i) {
        //This 'for' loop carries out the self-consistent iterations
        u2 = u1 + 0.5 * dt * (f(t1, u1) + f(t2, u2));  //trapezium rule is now applied to the new values
    }
    return u2;
}


int main(){

    long double t_initial = 0.;
    long double t_final = 10.0;
    int n = 100000;
    long double t_delta = (t_final-t_initial)/static_cast<long double>(n);
    valarray<long double> T(n+2);   //[0],T[1],...,T[n],T[n+1]
    valarray<valarray<long double>> U(n+2);
    valarray<long double>E(n+2);
    valarray<long double> e(n+2);
    //Given from question

    // Write header
#define SP << setw(26) << setprecision(10) <<    // save some repetition when writing
    cout << "t" SP "q(t)" SP "p(t)" SP "E(t)" SP "e(t)" << endl;

    //set initial data such that U(0) = {q(0),p(0)} = {-0.5,0}
    U[0] = {-0.5, 0.};

    for(int j=0; j<=n; j++){
        T[j] = t_initial + static_cast<long double>(j)*t_delta;
        //given in question
        U[j+1] = H2(T[j], U[j], t_delta, F);
        //We use the +1 as we already have been given the initial conditions, we do not want to overwrite it - we also find the 0th value of each valarray without the need for 2 'for' loops
        E[j] = static_cast<long double>(0.5 * U[j][1]*U[j][1]) - static_cast<long double>(U[j][0]*U[j][0]*U[j][0]) - static_cast<long double>(0.5 *U[j][0]*U[j][0]);
        //E(t) = 0.5(p^2) + (V(q)) = 0.5(p*p) - (q*q*q) -(0.5*q*q)
        e[j] = U[j][0] - static_cast<long double>(-0.5/(cosh(0.5*T[j])*cosh(0.5*T[j])));
        //error = q(t) - (-0.5sech^2(0.5*t) = q(t) - (-0.5/cosh^2(0.5*t))
        //We have to use cosh identity instead of sech as only cosh is cmath library
    }

    int i = 0;
    while (i <= n){
        cout << T[i] SP U[i][0] SP U[i][1] SP E[i] SP e[i] << endl;
        i = i + 10000;
        //We use a while function and this equation to output the only relevant time intervals for i=0,i=1...i=10
    }
    return 0;
}


