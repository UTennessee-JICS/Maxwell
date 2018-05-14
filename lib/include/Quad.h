#ifndef _QUAD_H_
#define _QUAD_H_

#include "Exception.h"

/**
  Quadrature formulas over the reference element, i.e. the interval [-1,1]
**/


/// Interface for Quadrature formulas
class QuadratureBase{
  public:
    // Constructor. The argument is the number of points the
    QuadratureBase( const unsigned _np = 0 );
    virtual ~QuadratureBase();
    // Get the node with index q
    double get_point( const unsigned q ) const;
    // Get the weight with index q
    double get_weight( const unsigned q ) const;
    // Number of quadrature points
    unsigned size() const;
  protected:
    // Number of quadrature points
    const unsigned nqp;
    // The nodes and weights
    double *value, *weight;
  private:
    void operator=( const QuadratureBase &quad ) {};
};

/// Midpoint Quadrature rule
class QMidPoint: public QuadratureBase{
  public:
    QMidPoint();
    virtual ~QMidPoint();
};

/// Interpolatory quadrature rule. The nodes are the vertices
class QVertices: public QuadratureBase{
  public:
    QVertices();
    virtual ~QVertices();
};

#endif