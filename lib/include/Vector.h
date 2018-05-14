#ifndef _VECTOR_H_
#define _VECTOR_H_

/**
  A class for vectors
**/

#include <cmath>
#include <algorithm>
#include <iostream>

#include "Exception.h"

class Vector{
  public:
    // Empty constructor
    Vector();
    // Copy constructor
    Vector( const Vector &v );
    // Constructor with specified size. The values are initialized to zero
    Vector( const unsigned _n );
    ~Vector();
    // Set all the coordinates of the vector equal to s
    void operator=( const double s );
    // Copy operator. The vector gets resized if needed
    Vector& operator=( const Vector &v );
    // this += v
    void add( const Vector &v );
    // this += s*v
    void add( const double s, const Vector &v );
    // this += a*v + b*w
    void add( const double a, const Vector &v, const double b, const Vector &w );
    // this = s*this + v
    void sadd( const double s, const Vector &v );
    // this = s*this + a*v
    void sadd( const double s, const double a, const Vector &v );
    // this = s*this + a*v + b*w
    void sadd( const double s, const double a, const Vector &v, const double b,
                const Vector &w );
    // this = a*v
    void equ( const double a, const Vector &v );
    // this = a*v + b*w
    void equ( const double a, const Vector &v, const double b, const Vector &w );
    // this = s*this + a*v
    void equ( const double s, const double a, const Vector &v );
    // this = s*this + a*v + b*w
    void equ( const double s, const double a, const Vector &v, const double b,
              const Vector &w );
    // r-value accessing operator
    double operator()( const unsigned i ) const;
    // l-value accessing operator
    double& operator()(const unsigned i );
    // l1 norm of the vector
    double l1norm() const;
    // l2 norm of the vector
    double l2norm() const;
    // l{\infty} norm of the vector
    double linftynorm() const;
    // lp norm of the vector.
    double lpnorm( const double p ) const;
    // mean value of the vector
    double mean_value() const;
    // this*this
    double norm_sqr() const;
    // resizing of the vector
    void reinit( const unsigned _n, const bool set_values = true, const double v = 0. );
    // resizing with the size of v and copy
    void reinit( const Vector &v );
    // get the size of the vector
    unsigned size() const;
    // swap this <-> v
    void swap( Vector &v );
    // scalar product this*v
    double operator*( const Vector &v ) const;
    void print( std::ostream &op ) const;
  private:
    double *vals;
    unsigned n;
};

#endif
