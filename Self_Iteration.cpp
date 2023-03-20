//
//  main.cpp
//  Self_Iteration
//
//  Created by Waqil Rahman on 08/04/2022.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#define EP 1E-15
//this defines the epsolion
using namespace std;

int main() {
   
    long double x0 = 1.0;
    //intial guess is defined
    
    for (int i = 0; x0 < 2.0; ++i) {
    //for loop will continue unti the value of x is more than 2(this wont occur due to the nature of the function
        long double x1 = exp(-x0);
        //This outputs the result of the function
        long double iterations = i + 1.0 ;
        //This long double stores number of iterations until the end of the loop or if the loop breaks
        
        if (abs(x1-x0) <= EP){
        //This if statement sets the conditions for the final value of x
            cout << setprecision(18) << "The final value of x: " << x0 << endl;
            //This outputs to 18 digits the final value of x
            cout << "The number of iterations: " << iterations << endl;
            //This outputs the number iterations occurred stored from the double
            long double final_value = x0 - exp(-x0);
            //This calculates the error
            cout << "The error in the transcendental equation is: " << final_value << endl;
            break;
            //This breaks the entire for loop
        }
        x0 = x1;
        //This re-assignment of doubles allows for the recursive iteration to loop with the new value
    }
    
    return 0;
}
