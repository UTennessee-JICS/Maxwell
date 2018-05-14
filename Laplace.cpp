#include "Laplace.h"

LaplaceProblem::LaplaceProblem( const unsigned n_cells ): Problem( n_cells ) {}

LaplaceProblem::~LaplaceProblem() {}

void LaplaceProblem::cell_integrator( const cell_integration_info &ci,
                                      cell_integration_data &cd ) const{
  // Get quadrature points
  fe.quadrature_points( cd.q_points );
  // Loop over the quadrature points
  for( unsigned q = 0; q<ci.number_of_quadrature_points; ++q )
    //Loop over degrees of freedom
    for( unsigned i=0; i<ci.dofs_per_cell; ++i ){
      cd.loc_f[i] += fe.JxW(q)*fe.shape_value( i, q )*RHS( cd.q_points[q] );
      for( unsigned j=0; j<ci.dofs_per_cell; ++j )
        cd.loc_m[j][i] += fe.JxW(q)*fe.shape_grad( i, q )*fe.shape_grad( j, q );
    }
}

void LaplaceProblem::Apply_BCs(){
  // Set Boundary conditions
  unsigned li, ri;
  fe.get_boundary_dofs( li, ri );
  SetDirichletBC( A, f, li );
  SetDirichletBC( A, f, ri );
}

double LaplaceProblem::RHS( const double x ) const{
  return 4.*M_PI*M_PI*std::sin( 2.*M_PI*x );
}
