/**
 *
 * This file is part of the course wi4771tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// H10-add-vectors
// Joe Miceli 4246465


#ifdef _MSC_VER
#  define NOINLINE __declspec(noinline)
#else
#  define NOINLINE __attribute__((noinline))
#endif

#include <vector>
#include <algorithm>
#include <functional>

// Adding two vectors, function for when all vectors are added and only 1 vector remains
template <typename V>
std::vector<V> add_vectors(const std::vector<V>& a)
{
    return a;
}

// Adding two vectors, basic function for when two vectors are added
template <typename V, typename... T>
std::vector<V> add_vectors(const std::vector<V>& a, const std::vector<T>&... b)
{
    std::vector<V> result;
    result.reserve(a.size());

    std::transform(a.begin(), a.end(), add_vectors(b...).begin(), std::back_inserter(result), std::plus<V>());
    return result;
}

// Adding the elements of vectors, function for when all vectors are added and only 1 vectors remains
template <typename V>
std::vector<V> add_elem(const std::vector<V>& a)
{
    return a;
}

// Adding the elements of vectors, basic function to add the elements
template <typename V, typename... T>
std::vector<V> add_elem(const std::vector<V>& a, const std::vector<T>&... b)
{
    std::vector<V> result;
    result.reserve(a.size());

    int n = a.size();

    for (auto i = 0; i < n; i++)
        result[i] = result[i] + add_elem(b...)[i];

    return result;
}


// Find the length of arguments
template<typename... T>
static int length(T ... args)
{
    return sizeof...(args);
}

// TODO: Replace the following function template.  You may change the template
// arguments and function arguments if necessary.
template<typename V, typename... T>
std::vector<V> add_vectors_singleloop(const std::vector<V>& head, const std::vector<T>&... tail)
{
    std::vector<V> result(head.size());

    result = add_vectors(head, tail...);

    return result;
}

// TODO: Replace the following function template.  You may change the template
// arguments and function arguments if necessary.
template<typename V, typename... T>
std::vector<V> add_vectors_simple(const std::vector<V>& head, const std::vector<T>&... tail)
{
    std::vector<V> result(head.size());
    
    result = add_elem(head, tail...);

    return result;
}


/*

    Nothing is required to do with the code below.

*/

NOINLINE std::vector<double> test_add_vectors_singleloop(
    const std::vector<double>& a, const std::vector<double>& b,
    const std::vector<double>& c, const std::vector<double>& d)
{
    return add_vectors_singleloop(a, b, c, d);
}

NOINLINE std::vector<double> test_add_vectors_simple(
    const std::vector<double>& a, const std::vector<double>& b,
    const std::vector<double>& c, const std::vector<double>& d)
{
    return add_vectors_simple(a, b, c, d);
}

#include <iostream>
#include <cstring>

int main(int argc, char **argv)
{
    // ./H10-add-vectors/add-vectors

    //  time ./add-vectors single       TAKES 0m 00.032s
    //  time ./add-vectors singleloop   takes 0m 13.963s

    int n = 1000000;
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(n);
    std::vector<double> d(n);
    if (argc == 2)
    {
        if (strcmp(argv[1], "simple") == 0)
        {
            std::cout << "testing simple" << std::endl;
            for (int i = 0; i < 100; i++)
                test_add_vectors_simple(a, b, c, d);
            return 0;
        }
        else if (strcmp(argv[1], "singleloop") == 0)
        {
            std::cout << "testing singleloop" << std::endl;
            for (int i = 0; i < 100; i++)
                test_add_vectors_singleloop(a, b, c, d);
            return 0;
        }
    }
    std::cout << "USAGE: " << argv[0] << " simple|singleloop" << std::endl;
}
