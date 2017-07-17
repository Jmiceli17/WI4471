/*
    Final project for WI4771.tu - 2017
    
    Exercise:       Heat equation

    By:             Ishan Karnik    4650026
                    Joe Miceli      4642465
                    Joris den Uijl  4296591

    Handed in on:   01-05-2017

*/

// Including the header files
#include <iostream>
#include <initializer_list>
#include <memory>
#include <map>
#include <cmath>


// Implementation vector and matrix classes
// This is the vector class
template<typename T>
class Vector
{ public:

    // Constructors
    // Constructor, used when no elements are given
    Vector()
    : length(0),
      array(nullptr)
    { }
    
    // Constructor, constructs an empty array with length = length
    Vector(T length)
    : length(length),
      array(new double[length])
    { }

    // Constructor (with initialiser list and delegate constructor)
    Vector(std::initializer_list<double> list)
    : Vector((T)list.size())
    {
        std::uninitialized_copy(list.begin(), list.end(), array);
    }
    

    // Destructor
    ~Vector()
    {
        delete[] array;
        length = 0;
    }
    

    // Attributes
    double* array;
    int length = 0;

    
    // Operators
    // Pointwise sum
    Vector& operator+(const Vector& b)
    {
        // Throw exception if the vectors have different length
        if (length != b.length) throw "Vectors have different size!";

        // Add the two vectors
        for (auto i = 0; i < length; i++)
            array[i] += b.array[i];
        
        return *this;
    }

    // Pointwise difference
    Vector& operator-(const Vector& b)
    {
        // Throw exception if the vectors have different length
        if (length != b.length) throw "Vectors have different size!";

        // Take the difference of the two vectors
        for (auto i = 0; i < length; i++)
            array[i] -= b.array[i];
        
        return *this;
    }

    // Multiplication with scalar
    Vector& operator*(unsigned char b)
    {
        // Add two vectors
        for (auto i = 0; i < length; i++)
            array[i] = array[i] * b;
        
        return *this;
    }

    // Multiplication with vector
    Vector& operator*(const Vector& b)
    {
        // Throw exception if the vectors have different length
        if (length != b.length) throw "Vectors have different size!";

        double sum = 0;
        for (auto i = 0; i < length; i++)
            sum += array[i] * b.array[i];
        
        return sum;
    }

    // Division by vector
    Vector& operator/(const Vector& b)
    {
        // Throw exception if the vectors have different length
        if (length != b.length) throw "Vectors have different size!";

        double sum = 0;
        for (auto i = 0; i < length; i++)
            sum += array[i] / b.array[i];
        
        return sum;
    }
    
    // Operator to get value at location of index
    const double operator[](int index) const
    {
        if (length<index) throw "Index exceeds vector length";
        
        return array[index];
    }

    // Operator to inherit all values of another vector
    Vector& operator=(const Vector& b)
    {
        // Throw exception if the vectors have different length
        if (length != b.length) throw "Vectors have different size!";

        // Take the difference of the two vectors
        for (auto i = 0; i < length; i++)
            array[i] = b.array[i];
        
        return *this;
    }


    // Member functions
    // Set value x on location index
    void set(int index, double x)
    {
        array[index] = x;
        return;
    }

    // Print the array
    void printVector()
    {
        std::cout << "The vector contains the following values" << std::endl;

        for (auto i = 0; i < length; i++)
            std::cout << array[i] << " ";

        std::cout << "" << std::endl;
        return;
    }

};

// This is the matrix class
template<typename T>
class Matrix
{ public:
    typedef std::map<int, std::map<int , T>> row_t;
    typedef typename row_t::iterator row_iter;
    typedef std::map<size_t, T> col_t;
    typedef typename col_t::iterator col_iter;

    
    // Constructors
    // Construct an empty matrix with a rows and b columns
    Matrix(int a, int b)
    { 
        rows = a; 
        columns = b; 
    }

    
    // Destructor
    ~Matrix()
    {
        rows = 0;
        columns = 0;
    }

    
    // Attributes
    row_t mat;
    int rows;
    int columns;

    
    // Operators
    // Operator to find a value at location a,b
    T& operator()(int a, int b)
    {
        if (a >= rows || b >= columns) throw "Does not work because vectors and matrix are of different size!";
        
        return mat[a][b];
    }


    // Member functions
    // Changing a value at locatio a,b
    void set(int a, int b, double x)
    {
        mat[a][b] = x;
        return;
    }

    // Matrix - Vector product
    template<typename V>
    Vector<V> matvec(const Vector<V>& a)
    {  //Computes y=A*x
        if ((this -> rows) != a.length) throw "Does not work because vectors and matrix are of different size!";

        Vector<V> y(this -> rows);
        T sum;

        for (auto i = 0; i < rows; i++)
        {
            sum = 0;

            for (auto j = 0; j < columns; j++)
                sum += mat[i][j] * a[j];

            y.set(i, sum);
        }

        return y;
    }


    // Print the matrix
    void printMatrix()
    {
        std::cout << "The matrix contains the following values" << std::endl;

        for (auto i = 0; i < rows; i++)
        {
            for (auto j = 0; j < columns; j++)
                std::cout << mat[i][j] << " ";
            
            std::cout << " " << std::endl;
        }

        return;
    }
};


// This is the classes that solve the heat equations
// This is the 1D case
class Heat1D
{ public:
    //Constructor
    Heat1D(double a, int b, double c)
    {
        alpha = a;
        m = b;
        dt = c;
        Matrix<double> M(m,m);

        double dx = 1.0 / (m+1);
        

        for (auto i = 0; i * dt <= final; i++)
        {
            for (auto j = 0; j * dt <= final; j++)
            {
                double diag = 1 - ((alpha * dt) / (dx * dx) * -2);
                double diag_plus1 = 0 - ((alpha * dt) / (dx * dx) * 1);
                double diag_minus1 = 0 - ((alpha * dt) / (dx * dx) * 1);

                if (i == j)
                    M.set(i, j, diag);

                if (i == j + 1)
                    M.set(i, j, diag_plus1);

                if (i == j - 1)
                    M.set(i, j, diag_minus1);
            }
        }

        M.printMatrix();
    }
    
    // Attributes
    double final = 1;
    double alpha;
    int m = 0;
    double dt;

    // Member functions
    // The function below returns the exact solution at time t for all gridpoints
    Vector<double> exact(double t) const
    {
    
    //n = 1
    Vector<double> u = exp(0.0-(M_PI*M_PI)*alpha)
    }

    // The function below solves the boundary value problem using function cg
    Vector<double> solve(double t_end) const
    {
    
    }

};

// This is the 2D case
// class Heat2D


// Functions
// Dot product
template<typename T>
T dot(const Vector<T>& l, const Vector<T>& r)
{
    // Throw exception if the vectors have different length
    if (l.length != r.length) throw "Vectors have different size!";
    
    // Calculate the dot product
    double d = 0;
    for (auto i = 0; i < l.length; i++)
        d += l.array[i] * r.array[i];
    return d;
}

// Initialize the initial conditions
template<typename T>
void initialize(int m, Vector<T>& V)
{
    for (auto i = 0; i <= m; i++)
        V.set(i + 1, sin((i + 1) * (1.0 / (m + 1)) * M_PI));

    return;
}

// Conjugent gradient method
// Matrix A and vector b are known, we are looking for vector x
template<typename T>
int cg(const Matrix<T>& A, const Vector<T>& b, Vector<T>& x, T tol, int maxiter)
{
    Vector<T> temp = A.matvec(x);
    Vector<T> p(b.length);
    Vector<T> r(b.length);
    Vector<T> r_new(r.length);
    Vector<T> p_new(p.length);
    Vector<T> x_new(x.length);


    p = r = b - temp;

    int iterations;

    for (auto i = 0; i < maxiter - 1; i++)
    {
        iterations = i;

        r_new = r;
        r = r_new;
        
        p_new = p;
        p = p_new;

        x_new = x;
        x = x_new;

        double alpha = dot(r, r) / (A.matvec(p), p);
        x_new = x + alpha * p;
        r_new = r - alpha * A.matvec(p);

        if (pow(dot(r_new, r_new), 0.5) < tol * tol)
            break;

        double beta = dot(r_new, r_new) / dot(r, r);
        p_new = r_new + beta * p;
    }

    if (pow(dot(r_new, r_new), 0.5) < tol * tol)
        iterations = iterations;

    else
        iterations = -1;

    return iterations;
}

    


// Main function
int main()
{
    //./Final-project/final-project

    // Initial conditions
    // m stands for the number of inner nodes
    int m = 3;
    Vector<int> w_0(m+2);
    initialize<int>(m, w_0);

    
    // Heat1D
    Heat1D(0.3125, 3, 0.1);

    return 0;
}
