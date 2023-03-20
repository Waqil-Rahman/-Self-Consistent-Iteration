#include <iostream>
#include <cmath>
#include <valarray>
#include <iomanip>
using namespace std;

long double normal_calculation(int m, valarray<long double>a){
    //We have turned the normal_cal function object into a function so it's easier to use to avoid longer calculation times and less re-defining of valarrays when the function is called several times
    long double norm = 0;
    for (int i = 0; i <= a.size(); ++i){
        norm += pow(abs(a[i]),m);
    }
    long double normal = pow(norm,1/static_cast<long double>(m));
    //This takes the normal formula from 2d in the form of a function instead of function object
    return normal;
}

void fanalytical(int N){
    valarray<long double> gridpoint(N+1);
    valarray<long double> fx(N+1);
    valarray<long double> fddx(N+1);
    //This initialises the valarray to the correct size for given N

    long double delta_x2 = pow(2.0 / static_cast <long double>(N),2.0);
    //We calculate the long double here which is required to calculate other doubles

    for (int i = 0; i < N+1; ++i) {
        gridpoint[i] = (2.0 * double(i) - (N)) / (N); //xi formula
        fx[i] = exp(-16.0 * (pow(gridpoint[i], 2.0))); //f(xi) formula
        fddx[i] = -32.0 * (-32.0 * fx[i] * pow(gridpoint[i], 2.0) + fx[i]);
    }//This series of for loops inputs the correct values into each respective valarray

    valarray <long double> f__(N+1);
    valarray <long double> ei(N+1);
    for (int i =0;i<N+1;++i){
        if (i == 0) {
            f__[0] = (fx[i + 2] - 2.0 * fx[i + 1] + fx[i]) /static_cast <long double>(delta_x2);
            ei[0] = fddx[0] - f__[0];
        } else if (i == N) {
            f__[N] = (fx[N] - 2.0 * fx[N - 1] + fx[N - 2]) /static_cast <long double>(delta_x2);
            ei[i] = fddx[N] - f__[N];
        } else {
            f__[i] = (fx[i + 1] - 2.0 * fx[i] + fx[i - 1]) / static_cast <long double>(delta_x2);
            ei[i] = fddx[i] - f__[i];
        }
    }

    // Write header,in week 9 lab code
    #define SP << setw(30) << setprecision(10) <<    // save some repetition when writing
    cout << " i:" SP "xi:" SP "f(xi):" SP "fddx(xi):" SP "ei:" << endl;
    for (int i =0;i<N+1;++i){
        cout << i SP gridpoint[i] SP fx[i] SP f__[i] SP ei[i] << endl;
    } //This generates the headers when tabulating the outputs
}

long double e(int N){
    valarray<long double> gridpoint(N+1);
    valarray<long double> fx(N+1);
    valarray<long double> fddx(N+1);

    long double delta_x2 = pow(2.0 / static_cast <long double>(N),2.0);
    //We calculate the long double here which is required to calculate other doubles

    for (int i = 0; i < N+1; ++i) {
        gridpoint[i] = (2.0 * double(i) - (N)) / (N); //xi formula
        fx[i] = exp(-16.0 * (pow(gridpoint[i], 2.0))); //f(xi) formula
        fddx[i] = -32.0 * (-32.0 * fx[i] * pow(gridpoint[i], 2.0) + fx[i]);
    }//This series of for loops inputs the correct values into each respective valarray

    cout << setprecision(10);
    valarray <long double> f__(N+1);
    valarray <long double> ei(N+1);
    for (int i =0;i<N+1;++i){
        if (i == 0) {
            f__[0] = (fx[i + 2] - 2.0 * fx[i + 1] + fx[i]) /(delta_x2);
            ei[0] = fddx[0] - f__[0];
        }  else if (i == N) {
            f__[N] = (fx[N] - 2.0 * fx[N - 1] + fx[N - 2]) /(delta_x2);
            ei[i] = fddx[N] - f__[N];
        } else {
            f__[i] = (fx[i + 1] - 2.0 * fx[i] + fx[i - 1]) /(delta_x2);
            ei[i] = fddx[i] - f__[i];
        }
    } //The above is already explained but we need the previous values to calculate the error
    cout << setprecision(15);
    long double error = (static_cast <long double>(N*N)/(static_cast<long double>(N)+1))*normal_calculation(1,ei);
    //This long double calculates the final value error from the value of n inputted
    cout << "The result of (N^2)<e>: " << error << " N = "<< N << endl;
    return error;
}


int main() {

    fanalytical(63);

    int i =15;
    while (i<2048){
        e(i);
        i = (i*2) + 1;
    }

    return 0;
}

