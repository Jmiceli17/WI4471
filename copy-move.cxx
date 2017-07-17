/**
 *
 * This file is part of the course wi4771tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// H05-copy-move
// Joe Miceli 4246465


#include <iostream>
#include <initializer_list>
#include <memory>

using namespace std;

class Container
{
public:
    //constructors
    Container()		//no argument constructor
    : length(0),
      data(nullptr)
    {}
        
    Container(int length)	//length constructor
    : length(length),
      data(new double[length])
    {
        std::clog << "Constructor(int length) called" << std::endl;
    }

    Container(std::initializer_list<double> list)	//list constructor
    : Container((int)list.size())
    {
        std::uninitialized_copy(list.begin(), list.end(), data);
        std::clog << "Constructor(std::initializer_list<double> list) called" << std::endl;
    }

    Container(const Container& c)	//copy constructor
    : Container(c.length)
    {
        for (auto i=0; i<c.length; i++)
            data[i] = c.data[i];
        std::clog << "Copy constructor" << std::endl;
    }

    Container(Container&& c)		//move constructor
    : length(c.length), data(c.data)
    {
        c.length = 0;
        c.data = nullptr;
        std::clog << "Move constructor" << std::endl;
    }

    //Destructor
    ~Container()
    {
        delete[] data;
        length = 0;
        std::clog << "Destructor called" << std::endl;
    }

    //Operators
    Container& operator=(const Container& other)	//copy assignment operator
    {
        if (this != &other)
            {
                delete[] data;
                length = other.length;
                data   = new double(other.length);
                for (auto i=0; i<other.length; i++)
                    data[i] = other.data[i];
            }
        std::clog << "Copy assignment operator" << std::endl;
        return *this;
    }

    Container& operator=(Container&& other)		//move assignment operator
    {
        if (this != &other)
            {
                delete[] data;
                length = other.length;
                data   = other.data;
                other.length = 0;
                other.data   = nullptr;
            }
	else
	    {
	    std::cout << "Containers must be same length" << std::endl;
	    }
        std::clog << "Move assignment operator" << std::endl;
        return *this;
    }

    Container operator+(Container other)		// + operator
    {
       
	if (this->length == other.length)
	{
            for (auto i=0; i<other.length; i++)			//containers must be same length
	       (*this).data[i]=(*this).data[i]+other.data[i];
	return (*this);    
	}
	else
	{
	std::cout << "Containers must be of equal length" << std::endl;
	}
    }



private:		//attributes 
    double* data;
    int length;
};














int main()
{
    std::cout << "Container a({ 1, 2, 3 });" << std::endl;
    Container a({ 1, 2, 3 });	
    //makes container a with initializer list constructor

    
    std::cout << "  a has address " << &a << std::endl;
    std::cout << "Container b = { 4, 5, 6 };" << std::endl;
    Container b = { 4, 5, 6 };  
    //creates container b implicitly instead of explicitly with initializer list constructor
    
    std::cout << "  b has address " << &b << std::endl;
    std::cout << "Container c(a);" << std::endl;
    Container c(a);
    //creates container c using copy constructor

    std::cout << "  c has address " << &c << std::endl;
    std::cout << "Container d = a + b;" << std::endl;
    Container d = a + b;
    //creates container d by calling addition operator 

    std::cout << "  d has address " << &d << std::endl;
    std::cout << "Container e;" << std::endl;
    Container e;
    //initializes container e with default constructor

    std::cout << "  e has address " << &e << std::endl;
    std::cout << "e = a + b;" << std::endl;
    e = a + b;
    //makes e a copy of a and then adds container b to it

    std::cout << "Container f(std::move(a + b));" << std::endl;
    Container f(std::move(a + b));
    //moves sum of containers a and b into f

    std::cout << "  f has address " << &f << std::endl;
    std::cout << "Container g = a + b + c;" << std::endl;
    Container g = a + b + c;
    //creates container g using 2 successive addition operators
    //first sets g equal to a then adds b, then adds c to that container
    
    std::cout << "  g has address " << &g << std::endl;
    std::cout << "Container h;" << std::endl;
    Container h;
    //initializes h using default constructor

    std::cout << "  h has address " << &h << std::endl;
    std::cout << "h = a + b + c;" << std::endl;
    h = a + b + c;
    //same process as container g except h is intialized first, so this is changing the container h 

    std::cout << "Container i = { a + b + c };" << std::endl;
    Container i = { a + b + c };
    //i is implicitly passed the sum of a, b, and c 

    std::cout << "  i has address " << &i << std::endl;
    std::cout << "end" << std::endl;

    return 0;
}

