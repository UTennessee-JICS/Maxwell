#include "../include/FESpace.h"

FESpace::FESpace( const Mesh &_m, const unsigned ndpc, const unsigned nd ):
        n_dofs_per_cell( ndpc ), n_dofs( nd ),
        m( &_m ), quad(0), is_valid( false ), curr_cell(-1) {}

FESpace::~FESpace() {}

const Mesh *FESpace::get_mesh(){
  return m;
}

bool FESpace::init_cell_loop( const QuadratureBase &q ){
  quad = &q;
  curr_cell = 0;
  m->get_cell( curr_cell, c );
  is_valid = true;
  return ( quad );
}

void FESpace::end_cell_loop(){
  quad = 0;
  curr_cell = -1;
  is_valid = false;
}

void FESpace::set_cell( const unsigned index ){
  Assert( is_valid, ExcFE() );
  Assert( index < m->n_cells(), ExcIndexRange( 0, m->n_cells(), index ) );
  m->get_cell( index, c );
  curr_cell = index;
}

double FESpace::JxW(const unsigned q ) const{
  Assert( is_valid, ExcFE() );
  return 0.5*quad->get_weight(q)*c.diameter();
}

double FESpace::shape_value( const unsigned i, const unsigned q ) const{
  Assert( is_valid, ExcFE() );
  Assert( i<n_dofs_per_cell, ExcIndexRange( 0, n_dofs_per_cell, i ) );
  return basis( i, quad->get_point(q) );
}

double FESpace::shape_grad( const unsigned i, const unsigned q ) const{
  Assert( is_valid, ExcFE() );
  Assert( i<n_dofs_per_cell, ExcIndexRange( 0, n_dofs_per_cell, i) );
  return 2.*dbasis( i, quad->get_point(q) )/c.diameter();
}

void FESpace::quadrature_points( std::vector<double> &qp ) const{
  Assert( is_valid, ExcFE() );
  Assert( quad->size() == qp.size(), ExcLength( qp.size(), quad->size() ) );
  unsigned nqp = qp.size();
  for( unsigned i=0; i<nqp; ++i )
    qp[i] = map_from_reference( quad->get_point(i) );
}

double FESpace::map_from_reference( const double xi ) const{
  Assert( is_valid, ExcFE() );
  return 0.5*c.diameter()*( xi-1. ) + c.points[1];
}

FEP1::FEP1( const Mesh &_m ): FESpace( _m, 2, _m.n_points() ){}

FEP1::~FEP1(){}

void FEP1::get_boundary_dofs( unsigned &li, unsigned &ri ) const{
  li = 0;
  ri = m->n_points()-1;
}

void FEP1::get_ldi( std::vector<unsigned> &ldi ) const{
  Assert( is_valid, ExcFE() );
  for( unsigned i=0; i<2; ++i )
    ldi[i] = c.indices[i];
}

double FEP1::basis( const unsigned i, const double xi ) const{
  Assert( i<n_dofs_per_cell, ExcIndexRange( 0, n_dofs_per_cell, i ) );
  if( i==0 )
    return .5*( 1. - xi );
  else
    return .5*( 1. + xi );
}

double FEP1::dbasis( const unsigned i, const double xi ) const{
  Assert( i<n_dofs_per_cell, ExcIndexRange( 0, n_dofs_per_cell, i ) );
  if( i==0 )
    return -.5;
  else
    return .5;
}

void FEP1::get_function_vals( const Vector &x, std::vector<double> &vals ) const{
  Assert( is_valid, ExcFE() );
  unsigned nqp = quad->size();
  for( unsigned q=0; q<nqp; ++q ){
    vals[q] = 0.;
    for( unsigned i=0; i<n_dofs_per_cell; ++i )
      vals[q] += shape_value( i, q )*x( c.indices[i] );
  }
}

void FEP1::get_function_grads( const Vector &x, std::vector<double> &grads ) const{
  Assert( is_valid, ExcFE() );
  unsigned nqp = quad->size();
  for( unsigned q=0; q<nqp; ++q ){
    grads[q] = 0.;
    for( unsigned i=0; i<n_dofs_per_cell; ++i )
      grads[q] += shape_grad( i, q )*x( c.indices[i] );
  }
}
