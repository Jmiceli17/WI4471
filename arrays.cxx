/**
 * \file arrays.cxx
 *
 * This file is part of the course wi4771tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// H02-arrays
// Joe Miceli 4642465

// Include header file for standard input/output stream library
#include <iostream>



int add_array(int n1, int n2)
{
    int array1 [n1];
    int array2 [n2];
    int array3 [n1];


    for (int i=0; i < n1; i++)    //user defines 2 arrays
    {
    std::cout << "enter data for array1" << std :: endl;
    std::cin >> array1[i];       
    }
    for (int i=0; i < n1; i++)
    {
    std::cout << "enter data for array2" << std :: endl;
    std::cin >> array2[i];
    }
    
    for (int i=0; i<n1; i++)  //for(initial, condition, increment)
    {
    array3[i]=array1[i]+array2[i];    //array values are added together to create third array
    }
    for (int i=0; i<n1; i++)
    {
    std::cout << array3[i] << " " << std::endl;
    }
}


// The global main function that is the designated start of the program
int main(){

    // Start here...
    int n1; 
    std::cin >> n1;
    int n2;
    std::cin >> n2;
    if (n1 == n2)
    {
    add_array(n1, n2);        
    }
    else
    {
    std::cout << "n1 and n2 must be equal" <<std::endl;
    }
    // Return code 0 to the operating system (=no error)
    return 0;
}







