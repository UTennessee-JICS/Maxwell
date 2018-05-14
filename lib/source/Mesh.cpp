#include "../include/Mesh.h"

Mesh::Mesh( const unsigned n_cells, const double _xl, const double _xr ):
      xl( _xl ), xr( _xr ), np( n_cells + 1 ), nc( n_cells ), points( np ), elts( nc ){
  const double h = ( xr - xl )/double( nc );
  for( unsigned i=0; i<nc; ++i ){
    points[i] = xl + double(i)*h;
    elts[i].points[0] = i;
    elts[i].points[1] = i+1;
  }
  points[nc] = xr;
}

Mesh::~Mesh(){}

unsigned Mesh::n_points() const{
  return np;
}

unsigned Mesh::n_cells() const{
  return nc;
}

void Mesh::get_cell( const unsigned i, cell &res ) const{
  Assert( i<nc, ExcIndexRange( 0, nc, i ) );
  for( unsigned k=0; k<2; ++k ){
    res.indices[k] = elts[i].points[k];
    res.points[k] = points[ elts[i].points[k] ];
  }
  res.index = i;
}