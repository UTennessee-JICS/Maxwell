#include "../include/Quad.h"

QuadratureBase::QuadratureBase( const unsigned _np ):
                nqp( _np ), value( new double[nqp] ), weight( new double[nqp] ){
  if( !value )
    throw ExcMemory();
  if( !weight )
    throw ExcMemory();
}
QuadratureBase::~QuadratureBase(){
  delete[] value;
  delete[] weight;
}

double QuadratureBase::get_point( const unsigned q ) const{
  Assert( q<nqp, ExcIndexRange( 0, nqp, q ) );
  return value[q];
}

double QuadratureBase::get_weight( const unsigned q ) const{
  Assert( q<nqp, ExcIndexRange( 0, nqp, q ) );
  return weight[q];
}

unsigned QuadratureBase::size() const{
  return nqp;
}

QMidPoint::QMidPoint(): QuadratureBase(1){
  value[0] = 1.;
  weight[0] = 2.;
}

QMidPoint::~QMidPoint(){}

QVertices::QVertices(): QuadratureBase(2){
  value[0] = -1.;
  value[1] = 1.;
  weight[0] = weight[1] = 1.;
}

QVertices::~QVertices(){}

