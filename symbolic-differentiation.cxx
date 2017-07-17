/**
  *
  *H09-symbolic-differentiation
  *
  *jmiceli / 4642465
  */




#include <iostream>
#include <type_traits>
#include <cmath>


template<int value>
struct ConstInt             //for functions that are constant integers
{
static double eval(double x)
	{
	return value;
	}
typedef ConstInt<0> derivative;
};

template<typename f, typename g>
struct Add				//struct that takes two functions as arguments and returns their sum
{
public:
	static double eval ( double x )
  	{
  	return f::eval( x ) + g::eval( x );
  	} 

  	typedef Add<typename f::derivative, typename g::derivative>  derivative;	//returns the derivative of the sum
};


template<typename f, typename g>
struct Mul				//struct that takes two frunctions as arguments and returns their product
{
public:
	static double eval (double x)
	{
	   return f::eval(x) * g::eval(x);
	}

	typedef Add< Mul<typename f::derivative, g>, Mul<f, typename g::derivative> > derivative;	//using product rule, returns the derivative of the product
};


template<int exponent> 
struct Monomial				//struct for functions of x to a power
{
	static double eval (double x)
	{
	return pow(x,exponent);
	}
	
	typedef Mul<ConstInt<exponent> ,Monomial<exponent-1>> derivative;
};







template<typename T>		//struct that returns negative of function used as parameter
struct Neg
{
public:
    static double eval(double x)
    {
        return -1*T::eval(x);
    }
    
    typedef Neg<typename T::derivative> derivative;
};


struct Cos; // Initial declaration of cosine

struct Sin // Sine function
{
public:
    static double eval(double x)
    {
        return sin(x);
    }

    typedef Cos derivative;
};

struct Cos // Cosine function
{
public:
    static double eval(double x)
    {
        return cos(x);
    }

    typedef Neg<Sin> derivative;
};




int main()
{
  std::cout << ConstInt<9>::eval ( 2.0 ) << std::endl;
  std::cout << ConstInt<9>::derivative::eval ( 2.0 ) << std::endl ;
  
  std::cout << Monomial<5>::eval (2) << std::endl;	//25==25
  std::cout << Monomial<5>::derivative::eval(2) << std::endl;
  
  std::cout << Add<Sin, Cos>::eval(3.14) << std::endl;
  std::cout << Mul<Sin, Cos>::eval(3.14) << std::endl;

  std::cout << Sin::eval(1.5708) << std::endl;
  std::cout << Neg<Sin>::eval(1.5708) << std::endl; 

  std::cout << Cos::eval(0) << std::endl;
  std::cout << Neg<Cos>::eval(0) << std::endl;

  std::cout << Sin::derivative::eval(0) << std::endl;
  std::cout << Cos::derivative::eval(0) << std::endl;

  std::cout << Mul< Monomial<3>, ConstInt<3> >::eval(1) << std::endl; 
 


  return 0;
}

