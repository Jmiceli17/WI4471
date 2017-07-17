/**
 *
 * This file is part of the course wi4771tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// H04-points-triangles
// Joe Miceli 4246465

#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
class Point
{
public:
    // constructors
	Point()		//creates default constructor, initializes attributes x and y with zero
	: x(0.0),
	  y(0.0)
	{}
	Point(double x, double y)	//creates constructor that takes two doubles and initializes x and y
	: x(x),
	  y(y)
	{}


    // operators
	Point operator+(Point other){
	  Point P; 
	  P.x = (*this).x + other.x ; 	
	  P.y = (*this).y + other.y ; 	
          return P;
	}
	Point operator-(Point other){
	  Point P;
	  P.x = (*this).x - other.x ;
	  P.y = (*this).y - other.y ;
	  return P;
	}
	Point &operator+=(Point& other){		//& allows for the original object to be
							//returned
	  this->x += other.x ;
	  this->y += other.y ;
  
	  return (*this);
	}
	Point &operator-=(Point& other){
	  this->x -= other.x ;
	  this->y -= other.y ;
  
	  return (*this);
	}



    // methods
	double distance()		//if no arguments given, computes distance between this
					//instance and the origin
	{
	double d = sqrt((x*x)+(y*y)) ;
	//cout << "The distance from the origin is " << d << endl;
	return d ;
	}

	


	double distance(Point other)		//computes the distance between this instance and 
						//another point
	{
	double xdif , ydif ;
	xdif = x - other.x ;			//computes distance between x and y values
	ydif = y - other.y ;
	double d = sqrt((xdif*xdif)+(ydif*ydif)) ;
	//cout << "The distance between the two points is " << d << endl ;
	return d ;
	}


	Point rotated(double angle)	//finds new point after being rotated about origin by this angle
	{
	Point P;
	P.x = x*cos(angle) - y*sin(angle) ;
	P.y = x*sin(angle) + y*cos(angle) ;
	//cout << "The new point is " << P.x  << " " << P.y << endl;
	return P; 			
	}

	Point rotated(double angle, Point other)		//finds new point after being rotated 
								//about other point
	{
	Point P;
	P.x = x*cos(angle) - y*sin(angle) + other.x ;
	P.y = x*sin(angle) + y*cos(angle) + other.y ;
	//cout << "The new point is " << P.x  << " " << P.y << endl;
	return P;
	}
	

	Point &rotate(double angle)			//rotation about origin, moves original 
							//instance
	{
	this->x = x*cos(angle) - y*sin(angle) ;
	this->y = x*sin(angle) + y*cos(angle) ;
	//cout << "The point is now " << "(" << this->x << "," <<  this->y << ")" << endl ;
	return (*this) ;
	}

	
	Point &rotate(double angle, Point other)	//rotation about another point, moves original 
							//instance
	{
	this->x = x*cos(angle) - y*sin(angle) + other.x ;
	this->y = x*sin(angle) + y*cos(angle) + other.y ;
	//cout << "The point is now " << "(" << this->x << "," <<  this->y << ")" << endl ;
	return (*this) ;
	}
	
	

    double x;
    double y;
};













class Triangle
{
public:

    // constructors
	Triangle()		//constructor that takes no argument, initializes a,b,c to zero
	: a(0.0,0.0),
	  b(0.0,0.0),
	  c(0.0,0.0)
	{}
	

	Triangle(Point a, Point b, Point c)	//constructor that takes 3 points as arguments and 
						//assigns them to a,b,c
	: a(a),
	  b(b),
	  c(c)
	{}
    
    // methods
	Triangle translated(Point t)	//creates a new triangle from translation of instance
	{
	Triangle A;

	A.a.x = a.x + t.x;
	A.a.y = a.y + t.y;
	A.b.x = b.x + t.x;
	A.b.y = b.y + t.y;
	A.c.x = c.x + t.x;
	A.c.y = c.y + t.y;
	
	return A;
	}
	
	Triangle &translate(Point t)	//moves original instance
	{
	this-> a.x += t.x;
	this-> a.y += t.y;
	this-> b.x += t.x;
	this-> b.y += t.y;
	this-> c.x += t.x;
	this-> c.y += t.y;
	
	return (*this);
	}
	
	Triangle rotated(double angle)		//creates new traingle rotated about origin
	{
	Triangle A;
	A.a.x = a.x*cos(angle) - a.y*sin(angle);
	A.a.y = a.x*sin(angle) + a.y*cos(angle);
	A.b.x = b.x*cos(angle) - b.y*sin(angle);
	A.b.y = b.x*sin(angle) + b.y*cos(angle);
	A.c.x = c.x*cos(angle) - c.y*sin(angle);
	A.c.y = c.x*sin(angle) + c.y*cos(angle);
	return A;
	}
	
	Triangle rotated(double angle, Point other)	//creates new trianlge rotated about point other
	{
	Triangle A;
	A.a.x = a.x*cos(angle) - a.y*sin(angle) + other.x;
	A.a.y = a.x*sin(angle) + a.y*cos(angle) + other.y;
	A.b.x = b.x*cos(angle) - b.y*sin(angle) + other.x;
	A.b.y = b.x*sin(angle) + b.y*cos(angle) + other.y;
	A.c.x = c.x*cos(angle) - c.y*sin(angle) + other.x;
	A.c.y = c.x*sin(angle) + c.y*cos(angle) + other.y;
	return A;
	}
	
	Triangle &rotate(double angle)		//rotates original triangle about origin
	{
	this->a.x = a.x*cos(angle) - a.y*sin(angle);
	this->a.y = a.x*sin(angle) + a.y*cos(angle);
	this->b.x = b.x*cos(angle) - b.y*sin(angle);
	this->b.y = b.x*sin(angle) + b.y*cos(angle);
	this->c.x = c.x*cos(angle) - c.y*sin(angle);
	this->c.y = c.x*sin(angle) + c.y*cos(angle);
	return (*this);
	}
	
	Triangle &rotate(double angle, Point other)	//rotates original triangle about point other
	{
	this->a.x = a.x*cos(angle) - a.y*sin(angle) + other.x;
	this->a.y = a.x*sin(angle) + a.y*cos(angle) + other.y;
	this->b.x = b.x*cos(angle) - b.y*sin(angle) + other.x;
	this->b.y = b.x*sin(angle) + b.y*cos(angle) + other.y;
	this->c.x = c.x*cos(angle) - c.y*sin(angle) + other.x;
	this->c.y = c.x*sin(angle) + c.y*cos(angle) + other.y;
	return (*this);	
	}

	double area()		//computes the area using Heron's formula
	{
	double AB = a.distance(b);
	double AC = a.distance(c);
	double BC = b.distance(c);
	double s = (AB + AC + BC)/2;
	cout << "semiperimeter is " << s << endl;
	double a = sqrt(s*(s-AB)*(s-AC)*(s-BC));
	return a;
	}


    Point a, b, c;
};

// ostream operator for `Point`s
std::ostream &operator<<(std::ostream &os, const Point &p)
{
    // remember current flags, precision
    auto flags = os.flags();
    auto current_precision = os.precision();
    // output numers with fixed point and three decimal precision
    os.setf(std::ios::fixed, std::ios::floatfield);
    os.precision(3);
    // output point `p`
    os << "(" << std::setw(6) << std::setfill(' ') << p.x
        << "," << std::setw(6) << std::setfill(' ') << p.y << ")";
    // restore current flags, precision
    os.flags(flags);
    os.precision(current_precision);
    return os;
}

// ostream operator for `Triangle`s
std::ostream &operator<<(std::ostream &os, const Triangle &t)
{
    return os << "Triangle< " << t.a << ", " << t.b << ", " << t.c <<  " >";
}



#include <iostream>
using namespace std;

int main()
{

    Point p;
    Triangle t;

    // set point `p` to (1, 2)
    p.x = 1;
    p.y = 2;

    // set triangle `t` to (1, 2), (3, 4), (5, 6)
   
    t.a.x = 1;
    t.a.y = 2;
    t.b.x = 3;
    t.b.y = 4;
    t.c.x = 5;
    t.c.y = 6;


   

    Triangle f;

    f.a.x = 6;
    f.a.y = 4;
    f.b.x = 1;
    f.b.y = 6;
    f.c.x = 7;
    f.c.y = 0;

 // print point `p` and triangle `t`
    cout << p << endl;
    cout << t << endl;
    std::cout << t.area() <<std::endl;  //the area of this triangle is zero because the points are colinear
    std::cout << f.area() <<std::endl;
    return 0;
}
