/**
 *
 * This file is part of the course wi4771tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// H08-unit-converter
// Joe Miceli 4246465


#include <iostream>
#include <type_traits>

enum class Unit {km = 2, m = 1, cm = 0};	//class Unit can be one of these three things

template<int v, Unit u>	
struct Measure			//trait that stores a value and its unit
{
    public:
        static const int value = v;
        static const Unit unit = u;

};


//the compiler will select which Convert class to use based on units being analized
template <Unit a, Unit b>	//an empty template class Convert
class Convert
{};

template <Unit a>		//Converting between the same units, factor = 1
class Convert<a,a>
{
public:
    static const int factor = 1;
    static const Unit unit = a;		//the unit is unchanged
};

template <>
class Convert<Unit::km,Unit::m>		//Converting between km and m
{
public:
    static const int factor = 1000;
    static const Unit unit = Unit::m;	//Both units are now m
};

template <>
class Convert<Unit::km,Unit::cm>	//Converting between km and cm
{
public:
    static const int factor = 100000;
    static const Unit unit = Unit::cm;	//Both units are now cm
};

template <>
class Convert<Unit::m,Unit::cm>		//COnverting between m and cm
{
public:
    static const int factor = 100;
    static const Unit unit = Unit::cm;	//Both units are now cm
};

//These empty classes are for the case where the booleans are not true, keeps program from crashing
template <typename M1, typename M2, bool yesno>		//An empty class sum_convert
class sum_convert
{};

template <typename M1, typename M2, bool yesno>		//An empty class sum_convert2
class sum_convert2
{};



template <typename M1, typename M2>	//Uses class Convert to add two values after converting them to 
					//Proper units in the case that unit M1 > M2
class sum_convert<M1,M2,true>
{
public:
    static const int value = M1::value * Convert<M1::unit, M2::unit>::factor + M2::value;
};

template <typename M1, typename M2>	//Uses defers action to sum_convert2 in the case that M1 >! M2
class sum_convert<M1,M2,false>
{
public:
    static const int value = sum_convert2<M1,M2,M1::unit == M2::unit>::value;	//Asks if units M1 and 
										//M2 are equal
};



template <typename M1, typename M2>	//Class sum_convert2 adds the two values without making 
					//conversions in the case that the units are equal

class sum_convert2<M1,M2,true>
{
public:
    static const int value = M2::value + M1::value;
};


template <typename M1, typename M2>	//Class sum_convert2 adds the values after making necessary 
					//conversions in the case that M1<M2
class sum_convert2<M1,M2,false>
{
public:
    static const int value = M2::value * Convert<M2::unit, M1::unit>::factor + M1::value;
};


template<typename a, typename b>
struct Measure_add			//trait that adds two adds two objects of type Measure and 
					//makes any necessary unit conversions
{
    private:
        static const int sum = sum_convert<a,b,(a::unit > b::unit)>::value;

    public:
        static const int value = sum;
};

int main()
{
    

    std::cout << Measure_add< Measure<10,Unit::km>, Measure<20,Unit::km> >::value  << std::endl;
    std::cout << Measure_add< Measure<10,Unit::km>, Measure<20,Unit::m> >::value  << std::endl;
    std::cout << Measure_add< Measure<10,Unit::km>, Measure<20,Unit::cm> >::value << std::endl;

    return 0;
}

