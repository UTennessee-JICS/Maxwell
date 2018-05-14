#ifndef _FESPACE_H_
#define _FESPACE_H_

#include "Exception.h"
#include "Quad.h"
#include "Mesh.h"
#include "Vector.h"

#include <vector>

/**
  Implementation of the space of finite element functions.
  It is used to give:
  * the values of the basis functions,
  * the values of the derivatives of the basis functions
  * the values of the quadrature points at the real cell
  * the value of the Jacobian times the quadrature weight
  * the local dof indices

  Note that, as always, to avoid having to deal with SmartPointers we
  assume that the quadrature and mesh objects are always valid...
  Also, the current cell is always assumed to be valid
**/

// Interface class
class FESpace{
  public:
    // Constructor.
    FESpace( const Mesh &_m, const unsigned ndpc, const unsigned nd );
    virtual ~FESpace();
    bool init_cell_loop( const QuadratureBase &q = QuadratureBase() );
    void end_cell_loop();
    const Mesh *get_mesh();
    // Things that are constant to the Finite Element Space
    // The degrees of freedom per cell and the global number of degrees of freedom
    const unsigned n_dofs_per_cell, n_dofs;
    // We set on which cell we are working
    void set_cell( const unsigned index );
    // The value of the Jacobian times the derivative for the current cell index
    double JxW( const unsigned q ) const;
    // The value of the shape function with local index i at the
    // quadrature point with index q
    double shape_value( const unsigned i, const unsigned q ) const;
    // The value of the derivative of the shape function with local index i at the
    // quadrature point with index q
    double shape_grad( const unsigned i, const unsigned q ) const;
    // The list of quadrature points on the real cell
    void quadrature_points( std::vector<double> &qp ) const;
    // The local dof indices
    virtual void get_ldi( std::vector<unsigned> &ldi ) const = 0;
    // Get the indices of the boundary dofs
    virtual void get_boundary_dofs( unsigned &li, unsigned &ri ) const = 0;
    virtual void get_function_vals( const Vector &x, std::vector<double> &vals ) const = 0;
    virtual void get_function_grads( const Vector &x, std::vector<double> &grads ) const = 0;
  protected:
    const Mesh* const m;
    const QuadratureBase *quad;
    bool is_valid;
    Mesh::cell c;
    unsigned curr_cell;
    // the map from the reference cell
    double map_from_reference( const double xi ) const;
    // The value of the basis function (on the reference cell )at a point
    virtual double basis( const unsigned i, const double xi ) const = 0;
    // The value of the derivative of the basis function (on the reference cell )at a point
    virtual double dbasis( const unsigned i, const double xi ) const = 0;
  private:
    FESpace( const FESpace &fe );
    void operator=( const FESpace &fe );
};


// P1 Lagrangian finite element space. We just instantiate the pure virtual functions
class FEP1: public FESpace{
  public:
    FEP1( const Mesh &_m );
    virtual ~FEP1();
    virtual void get_boundary_dofs( unsigned &li, unsigned &ri ) const;
    virtual void get_ldi( std::vector<unsigned> &ldi ) const;
    virtual void get_function_vals( const Vector &x, std::vector<double> &vals ) const;
    virtual void get_function_grads( const Vector &x, std::vector<double> &grads ) const;
  protected:
    virtual double basis( const unsigned i, const double xi ) const;
    virtual double dbasis( const unsigned i, const double xi ) const;
};

#endif
