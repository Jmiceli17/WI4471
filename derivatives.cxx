/**
  *
  * ikarnik / 4650026
  * jmiceli / 4642465
  *
  * H06-derivatives
  *
  */


#include <iostream>
#include <functional>


class Derivative{
public:
    //Constructors

    Derivative() //default constructor, initializes an h if no h is passed
    : h(1e-8)
    {}

    Derivative(double h) //you can choose your own h if you'd like
    : h(h)
    {}
   
    virtual double differentiate( 
        std::function<double(double)> func, double x) = 0;  //makes the initalized func and x values 0

    //Destructor

    ~Derivative() //wipes everything at the end
    {
        h = 1e-8;
    }

    double h;

};


class CentralDifference : public Derivative //brings in everything public from Derivative
{
public:
    //Constructors

    using Derivative::Derivative; //brings it in again? 

    virtual double differentiate(std::function<double(double)> func, double x)
    {
        double cdx = (func(x+h) - func(x-h)) / (2*h); //central difference differentiation method
        return cdx;
    }
   
};


class ForwardDifference : public Derivative //brings in everything public from Derivative
{
public:
    //Constructors

    using Derivative::Derivative; 

    virtual double differentiate(std::function<double(double)> func, double x)
    {
        double fdx = (func(x+h) - func(x)) / h; //forward difference differentiaton method
        return fdx;
    }

};


const double myfunc1(const double x) { return x; } //makes an initial function x using first method
auto myfunc2 = [](double x) { return x; }; //same initial function x using second method


int main(){

    CentralDifference CD; //shortens the typing of CentralDifference
    std::cout << "Central Difference: " << CD.differentiate(myfunc1, 0.5) << std::endl;
    std::cout << "Central Difference: " << CD.differentiate(myfunc2, 0.5) << std::endl;

    ForwardDifference FD; //shortens the typing of ForwardDifference
    std::cout << "Forward Difference: " << FD.differentiate(myfunc1, 0.5) << std::endl;
    std::cout << "Forward Difference: " << FD.differentiate(myfunc2, 0.5) << std::endl;

    return 0;

}
