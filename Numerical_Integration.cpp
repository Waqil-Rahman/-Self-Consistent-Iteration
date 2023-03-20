#include <iostream>
#include <valarray>
#include <cmath>
#include <iomanip>
#include <random>
using namespace std;

long double dot(const valarray<long double> a,const valarray<long double> b){
    return (a*b).sum();
} //This function is recalled from question 2a

long double monteCarloEstimate(long double lowBound,long double upBound,long double iterations){
//Function to execute Monte Carlo integration on predefined function
    long double totalSum = 0.0;
    const int s = 31;
    //seed value
    mt19937_64 mtrand(s);
    //We are generating a seed with a real random value
    uniform_real_distribution<long double>unif(lowBound,upBound);
    //This generates random values unifromally between the lower and upper bound

    for (int i=0;i<=iterations;++i){
        //Select a random number within the limits of integration
        long double xi_randNum = unif(mtrand);
        //Add the f(x) value to the running sum using the correct function
        totalSum += pow(((4.0-(xi_randNum))*(xi_randNum)),0.5);

    }
    long double estimate = ((upBound-lowBound)*(totalSum))/static_cast<long double>(iterations);
    //This calculates the final value of the Integration estimate using this method
    return estimate;
}

int main() {

    long double n = 63.0;
    //This is the value of n defined in the question
    long double x_delta = static_cast<long double>(4/n);
    //We calculate delta x using the formula given, we use static_cast as this a fraction to avoid accuracy loss

    valarray<long double> gridpoint(n+1);
    for (int i = 0; i <gridpoint.size(); ++i) {
        gridpoint[i] = (double(i)*4.0)/n;
    } //This calculates the gridpoints for 4a/4b and inputs them into a valarray

    valarray<long double> fi(n+1);
    for (int i =0; i < fi.size(); ++i){
        fi[i] = pow(((4.0-gridpoint[i])*gridpoint[i]),0.5);
    } //This calculates the f(i) points for 4a/4b and inputs them into a valarray

    valarray <long double>w_trapezium(n+1);
    for (int i = 0; i<w_trapezium.size(); ++i){
        long double multi = static_cast<long double>(x_delta/2.0);
        if (i == 0){
            w_trapezium[i] = (multi);
            //This inputs the values into the valarray for when i is 0
        }
        else if (i == n){
            w_trapezium[i] = (multi);
            //This inputs the values into the valarray for when i is 63
        }
        else {
            w_trapezium[i] = 2.0 * (multi);
            //This inputs the values into the valarray
        }
    } //This for loop inputs in the correct values for the weights creates the values inputted into the valarray

    valarray<long double>w_simpson(n+1);
    for (int i = 0; i<w_simpson.size(); ++i){
        long double multi = static_cast<long double>(x_delta/48.0);
        if (i == 0) {
            w_simpson[i] = 17.0 *(multi);
            //This inputs the values into the valarray for when i is 0
        }
        else if (i == 1) {
            w_simpson[i] = 59.0 * (multi);
            //This inputs the values into the valarray for when i is 1
        }
        else if (i == 2) {
            w_simpson[i] = 43.0 * (multi);
            //This inputs the values into the valarray for when i is 2
        }
        else if (i == 3) {
            w_simpson[i] = 49.0 * (multi);
            //This inputs the values into the valarray for when i is 3
        }
        else if (i == (n-3)) {
            w_simpson[i] = 49.0 * (multi);
            //This inputs the values into the valarray for when i is 60
        }
        else if (i == (n-2)) {
            w_simpson[i] = 43.0 * (multi);
            //This inputs the values into the valarray for when i is 61
        }
        else if (i == (n-1)) {
            w_simpson[i] = 59.0 * (multi);
            //This inputs the values into the valarray for when i is 62
        }
        else if (i == n){
            w_simpson[i] = 17.0 *(multi);
            //This inputs the values into the valarray for when i is 63
        }
        else {
            w_simpson[i] = 48.0 * (multi);
            //This inputs the values into the valarray
        }
    }//This for loop inputs in the correct values for the weights creates the values inputted into the valarray

    long double pi = 3.1415926535897932385;

    valarray <long double> theta(n+1);
    for (int i = 0; i<theta.size(); ++i){
        theta[i] = i*static_cast<long double>(pi/n);
    } //This calculates the theta values for 4c and inputs them into a valarray

    valarray<long double> gridpoint_CC(n+1);
    for (int i = 0; i <gridpoint_CC.size(); ++i) {
        gridpoint_CC[i] = ((4.0+(static_cast <double>(-4)*cos(theta[i])))/2.0);
    } //This calculates the gridpoints for 4c and inputs them into a valarray

    valarray<long double> fi_CC(n+1);
    for (int i =0; i < fi_CC.size(); ++i){
        fi_CC[i] = pow(((4.0-gridpoint_CC[i])*gridpoint_CC[i]),0.5);
    } //This calculates the f(i) for 4c and inputs them into a valarray


    valarray<long double>w_CC(n+1);
    for (int i = 0; i<w_CC.size(); ++i){
        if(i==0){
            w_CC[i] = static_cast<double>(2.0)/pow(n,2.0);
            //This inputs the values into the valarray for when i is 0
        }
        else if(i==n){
            w_CC[i] = static_cast<double>(2.0)/pow(n,2.0);
            //This inputs the values into the valarray for when i is 63
        }
        else {
            long double summation = 0;
            for (double k = 1.0; k <32;++k){
                summation += (static_cast<double>(2.0)*cos(2.0*k*theta[i]))/(4.0*pow(k,2.0)-1.0);
                //This generates the summation part of the CC equation
            }
            w_CC[i] = 2.0 * ((static_cast<double>(2.0)*(1.0 - summation))/n);
            //This inputs the values for the valarray for the correct values of i
        }
    } //This for loop inputs in the correct values for the weights creates the values inputted into the valarray

    long double i_real = 2.0*pi;
    long double i_trapezium = dot(w_trapezium,fi);
    long double i_simpson = dot(w_simpson,fi);
    long double i_CC = dot(w_CC,fi_CC);
    //We use the function from 2a to calculate the porduct of two valarrays
    long double i_MC = monteCarloEstimate(0.0, 4.0, 10000.0);
    //This calls the function defined to calculate the MC estimate for 4d

    //The below outputs all the results for question 4
    cout << setprecision(10);
    cout << "i_real: " << i_real << endl << endl;
    cout << "i_trapezium: " << i_trapezium << endl;
    cout << "i_trapezium - i_real = " << i_trapezium - i_real << endl << endl;
    cout << "i_simpson: " << i_simpson << endl;
    cout << "i_simpson - i_real = " << i_simpson - i_real << endl << endl;
    cout << "i_CC: " << i_CC << endl;
    cout << "i_trapezium - i_real = " << i_CC - i_real << endl << endl;
    cout << "i_MC: " <<  i_MC << endl;
    cout << "i_MC - i_real = " << i_MC - i_real << endl;

    return 0;
}

