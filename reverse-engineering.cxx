/**
 * \file reverse=engineering.cxx
 *
 * This file is part of the course wi4771tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// H03-reverse-engineering
// Joe Miceli 4246465

// Include header file for standard input/output stream library
#include <iostream>

// The global main function that is the designated start of the program
int main(){

    int a = 1;    
    int b = 2;
    int c = 3;
    const int d = 42;  //d cannot be changed

    {
        auto b = ++a + c++;    //b= a(+1) + c(original) (c is incremented after this operation) a =2
                               //b=2+3 , b is now 4  WITHIN THIS SCOPE ONLY
        auto e = b;            //e=5
        c += ++b;              //c= c+ b(+1), c = 4 + (5+1) = 10
    }

    int *p = &a;     //p = 2
    int *q = &b;     //q = 5

    ++(*q);    //increments *q and b by 1, b is 2 in this scope
    *p += a++ + (*p)++;   //while a is 2, it is doubled by *p += a, so *p is now 4 which is then added to 4 so both a and *p, then a and *p are both incremented 1, but because they are the same thing and in the same line, it only gets incremented 1 time so a and *p are 9 

    int A[] = {1, 2, 3, 4, 5};
    int *r = A;      //*r=1, *(r+1)=2, *(r+2)= 3..... 

    int e(*(r+3));  //e=4, this overides previous e

    double f = 0;
    int g;
    for (g = 0; g < 5; g++)  //g advances to 5 and for loop does not continue
        f += A[g] / 5;    // ((((((((1/5+2)/5)+3)/5)+4)/5)+5)/5) = 1.18752 = 1(as an int)
   
    std::cout << "a = " << a << std::endl;    //a = 9 but a should = 8
    std::cout << "b = " << b << std::endl;    //b = 3
    std::cout << "c = " << c << std::endl;    //c = 10
    std::cout << "d = " << d << std::endl;    //d = 42
    std::cout << "e = " << e << std::endl;    //e = 4
    std::cout << "f = " << f << std::endl;    //f = 1
    std::cout << "g = " << g << std::endl;    //g = 5
    
    // Return code 0 to the operating system (=no error)
    return 0;
}
