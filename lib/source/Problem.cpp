#include "../include/Problem.h"

Problem::Problem( const unsigned n_cells ): msh( n_cells ), fe( msh ), A( fe.n_dofs ),
        x( fe.n_dofs ), f( fe.n_dofs ), is_assembled( false ){}

Problem::~Problem(){}

Problem::cell_integration_info::cell_integration_info( const unsigned nqp,
                                                       const unsigned dpc ):
          number_of_quadrature_points( nqp ), dofs_per_cell( dpc ) {}

Problem::cell_integration_data::cell_integration_data( const unsigned nqp,
                                                       const unsigned dpc ):
          n( dpc ), loc_m( new double*[n] ), loc_f( new double[n] ), q_points( nqp ){
  if( !loc_f )
    throw ExcMemory();
  if( !loc_m )
    throw ExcMemory();
  for( unsigned i=0; i<n; ++i )
    if( !( loc_m[i] = new double[n] ) )
      throw ExcMemory();
}

Problem::cell_integration_data::~cell_integration_data(){
  for( unsigned i=0; i<n; ++i )
    delete[] loc_m[i];
  delete[] loc_m;
}

void Problem::Assemble( const QuadratureBase &quad ){
  cell_integration_info ci( quad.size(), fe.n_dofs_per_cell );
  cell_integration_data cd( quad.size(), fe.n_dofs_per_cell );
  std::vector<unsigned> ldi( fe.n_dofs_per_cell );
  // clean the global matrix & rhs
  f = 0.;
  A.zero();
  fe.init_cell_loop( quad );
  for( unsigned cell = 0; cell < msh.n_cells(); ++cell ){
    fe.set_cell( cell );
    // Clean the local contributions
    for( unsigned i=0; i<fe.n_dofs_per_cell; ++i ){
      cd.loc_f[i] = 0.;
      for( unsigned j=0; j<fe.n_dofs_per_cell; ++j )
        cd.loc_m[i][j] = 0.;
    }
    cell_integrator( ci, cd );
    // Add the contributions to the global matrix and rhs
    fe.get_ldi( ldi );
    for( unsigned i=0; i<fe.n_dofs_per_cell; ++i ){
      f( ldi[i] ) += cd.loc_f[i];
      for( unsigned j=0; j<fe.n_dofs_per_cell; ++j )
        A.add( ldi[i], ldi[j], cd.loc_m[i][j] );
    }
  }
  fe.end_cell_loop();
  Apply_BCs();
  is_assembled = true;
}

unsigned Problem::Solve( const unsigned n_max_its, const double eps, const double tau ){
  if( !is_assembled )
    throw ExcInternal();
  Solver s( n_max_its, eps*f.l2norm(), tau );
  PreconditionJacobi D(A);
  return s.solve( A, x, f, &D );
}

void Problem::Plot( const std::string &filename ){
   plot( x, fe, filename );
}
