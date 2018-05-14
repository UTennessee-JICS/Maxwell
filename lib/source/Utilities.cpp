#include "../include/Utilities.h"

#include <iostream>

void SetDirichletBC( SparseMatrix &sp, Vector &rhs,
                     const unsigned i, const double val ){
  sp.delete_row(i);
  sp.add( i, i, 1. );
  rhs(i) =val;
}

void plot( const Vector &x, FEP1 &fe, const std::string &filename ){
  std::ofstream file( filename.c_str() );
  if( !file )
    throw ExcFile( filename.c_str() );
  Mesh::cell c;
  std::vector<unsigned> ldi( fe.n_dofs_per_cell );
  fe.init_cell_loop();
  for( unsigned i=0; i<fe.get_mesh()->n_cells(); ++i ){
    fe.set_cell( i );
    fe.get_ldi( ldi );
    fe.get_mesh()->get_cell( i, c );
    file<<c.points[0]<<" "<<x( ldi[0] )<<std::endl
        <<c.points[1]<<" "<<x( ldi[1] )<<std::endl<<std::endl;
  }
  fe.end_cell_loop();
  file.close();
}
