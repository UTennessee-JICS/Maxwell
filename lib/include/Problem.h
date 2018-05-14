#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include "Vector.h"
#include "SparseMatrix.h"
#include "Mesh.h"
#include "LAC.h"
#include "Quad.h"
#include "FESpace.h"
#include "Utilities.h"

class Problem{
  public:
    Problem( const unsigned n_cells );
    ~Problem();
    void Assemble( const QuadratureBase &quad = QMidPoint() );
    virtual unsigned Solve( const unsigned n_max_its =10000, const double eps = 1e-6,
                            const double tau = 0.4 );
    void Plot( const std::string &filename );
  protected:
    struct cell_integration_info{
      unsigned number_of_quadrature_points, dofs_per_cell;
      cell_integration_info( const unsigned nqp, const unsigned dpc );
    };
    struct cell_integration_data{
      unsigned n;
      double **loc_m, *loc_f;
      std::vector<double> q_points;
      cell_integration_data( const unsigned nqp, const unsigned dpc );
      ~cell_integration_data();
    };
    virtual void cell_integrator( const cell_integration_info &ci,
                                  cell_integration_data &cd ) const = 0 ;
    virtual void Apply_BCs() = 0;
    Mesh msh;
    FEP1 fe;
    SparseMatrix A;
    Vector x, f;
    bool is_assembled;
  private:
    Problem( const Problem &prb );
    void operator=( const Problem &prb );
};
#endif
