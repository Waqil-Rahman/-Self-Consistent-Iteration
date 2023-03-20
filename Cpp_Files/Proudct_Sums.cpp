//
//  main.cpp
//  Question 2
//
//  Created by Waqil Rahman on 13/04/2022.
//

#include <iostream>
#include <cmath>
#include <valarray>
#include <iomanip>
using namespace std;

long double dot(const valarray<long double> a,const valarray<long double> b){
    return (a*b).sum();
    //This valarray calculation returns the sum of A*B
}
//This answers q2a

//The function cdot is defined in week10 notes - compensated summation.cpp - KahanSum function
long double cdot(const valarray<long double> v){
    long double sum = 0.;
    long double c = 0.;
    long double y;
    long double t;
    for(int i = 0; i < v.size(); ++i){
            y = v[i] - c;
            t = sum + y;
            c = (t - sum) - y;
            sum = t;
    }
    return sum;
}

class normal_cal{
//using class allows to extract different components out the function
    int m;
public:
    normal_cal(int M) : m(M){ }
    double operator()(const valarray<long double> a) const {
    //This initialises the valarray into the class and uses function object to call on the valarray
        long double normal = 0.;
        //We let normal be zero as we are going to add to it
        for (int i = 0; i <= a.size(); ++i){
        //the for loop will go through the entirity of the valarray
            normal += pow(abs(a[i]),m);
            //This double computes summation part of the normal
        }return pow(static_cast<long double>(normal),0.5);
        //The function will now return the final value of the normal
    }
};

int main(){
    
    cout<< setprecision(20);
    //We use the setprecision function to see the accuracy of the programme outputs
    
    long double n = pow(10.0,6.0);
    //Defined from question to 10^6 from library cmath
    valarray<long double>a(n);
    //We initialise valarray a with size n
    for (double i = 1; i < a.size(); ++i){
        //This creates the valarray of the Euclidean n-valarray
        a[i] = 1 /static_cast<long double>(i);
    }
    
    cout << "Product of dot: " << dot(a,a)<<endl;
    //Using the dot function we sum A and A together
    long double pi = 3.1415926535897932385;
    cout << "Difference in dot and the actual answer: " << dot(a,a) - (pow(pi,2.0)/6.0) << endl;
    //This answers q2b
    
    valarray<long double>x(0.1,n);
    //This is the constant Euclidean constant n-valarray for the dot function
    valarray<long double>x_new(0.01,n);
    //This is the constant Euclidean constant n-valarray for the dot function
    //We have to use 0.01 as that is c^2
    long double nc2 = 10000.0;
    // 10000 = (0.1^2)*(10^6)
    // We use the numerical exact value instead to avoid accuracy loss when the programme calculates the large number
    
    cout << endl;
    cout << "Product of dot: " << dot(x,x) << endl;
    //Using the dot function we sum x and x together to find the sum of nc^2 using the dot function
    cout << "Product of cdot: " << cdot(x_new) << endl;
    //Using the dot function we sum x_new to find the sum of nc^2 using the KahanSum method
    cout << "Difference in cdot and the actual answer: " << cdot(x_new) - nc2 << endl;
    //This answers q2c
    
    normal_cal norm(2);
    //This uses the function object and defines the int m = 2
    long double normal = norm(a);
    //This uses the function object and defines the valarray object valarray a
    cout << endl << "The result of norm l2('valarray'a) is: " << normal << endl;
    //This answers q2d
    
    return 0;
}
