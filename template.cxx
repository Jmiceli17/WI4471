/**
 *
 * This file is part of the course wi4771tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// H07-templates
// Joe Miceli 4246465


#include <iostream>
#include <typeinfo>
using namespace std;
#define PRINT_EXPRESSION(expr) std::cout << #expr << ": " << (expr) \
    << " (type: " << typeid(expr).name() << ")" << std::endl 



template<typename R>
R add_simple (R a, R b)		//template that takes two objects of same type
{
return a + b;
};



template<typename A, typename B>
auto add(A a, B b) -> decltype(a+b)    //tells the compiler what output type comes from 
{
return a + b;
}; 					//this template takes two objects that can be dif types



template<typename C>
bool is_int (C c)
{
return typeid(c) == typeid(int);	//checks if c is an int, returns 0 as false and 1 as true
}; 



template<typename T>
class Number
//creating operators to use for class Number
{

public: 
    T* value;
    Number(T value)
    : value(value)
    {}
    
    template<typename U>
    Number<T>& operator+ (const Number<U>& other)
    {
    value+=other.value;
    return *this;
    }
    template<typename U>
    Number<T>& operator- (const Number<U>& other)
    {
    value-=other.value;
    return *this;
    }
    template<typename U>
    Number<T>& operator* (Number<U>& other)
    {
    value = (*this).value*other.value;
    return *this;
    }
    template<typename U>
    Number<T>& operator/ (Number<U>& other)
    {
    value = (*this).value / other.value;
    return *this;
    }
};


template<int n>
struct fibonacci
{
    static const int value = fibonacci<n-1>::value + fibonacci<n-2>::value;
};

template<>
struct fibonacci<0>
{
    static const int value = 0;
};

template<>
struct fibonacci<1>
{
    static const int value = 1;
};	
    

int main()
{

    PRINT_EXPRESSION(add_simple(1, 2));
    PRINT_EXPRESSION(add_simple(1.5, 2.2));
    PRINT_EXPRESSION(add(1,2.334));
    std::cout << "is_int(9) = " << is_int(9) << std::endl;
    std::cout<<"The 17th fibonacci number is " << fibonacci<17>::value << std::endl;
    return 0;


}
