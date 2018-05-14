#include "../include/Vector.h"

Vector::Vector(): vals(0), n(0) {}

Vector::Vector( const Vector &v ): vals( new double[v.size()] ), n( v.size() ){
  if( !vals )
    throw ExcMemory();
  for( unsigned i=0; i<n; ++i )
    vals[i] = v(i);
}

Vector::Vector( const unsigned _n ): vals( new double[_n] ), n(_n ){
  for( unsigned i=0; i<n; ++i )
    vals[i] = 0.;
}

Vector::~Vector(){
  delete[] vals;
}

void Vector::operator=( const double s ){
  for( unsigned i=0; i<n; ++i )
    vals[i] = s;
}

Vector& Vector::operator=( const Vector &v ){
  if( v.vals == vals )
    return *this;
  if( n != v.size() )
    reinit(v);
  else{
    for( unsigned i=0; i<n; ++i )
      vals[i] = v(i);
  }
  return *this;
}

void Vector::add( const Vector &v ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] += v(i);
}

void Vector::add( const double s, const Vector &v ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] += s*v(i);
}

void Vector::add( const double a, const Vector &v, const double b, const Vector &w ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  Assert( n == w.size(), ExcLength( n, w.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] += a*v(i) + b*w(i);
}

void Vector::sadd( const double s, const Vector &v ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] = s*vals[i] + v(i);
}

void Vector::sadd( const double s, const double a, const Vector &v ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] = s*vals[i] + a*v(i);
}
void Vector::sadd( const double s, const double a, const Vector &v, const double b,
                   const Vector &w ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  Assert( n == w.size(), ExcLength( n, w.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] = s*vals[i] + a*v(i) + b*w(i);
}

void Vector::equ( const double a, const Vector &v ){
  if( n != v.size() )
    reinit( v.size(), false );
  for( unsigned i=0; i<n; ++i )
    vals[i] = a*v(i);
}

void Vector::equ( const double a, const Vector &v, const double b, const Vector &w ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  if( n != v.size() )
    reinit( v.size(), false );
  for( unsigned i=0; i<n; ++i )
    vals[i] = a*v(i)+b*w(i);
}

void Vector::equ( const double s, const double a, const Vector &v ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] = s*vals[i] + a*v(i);
}

void Vector::equ( const double s, const double a, const Vector &v, const double b,
                  const Vector &w ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  Assert( n == w.size(), ExcLength( n, w.size() ) );
  for( unsigned i=0; i<n; ++i )
    vals[i] = s*vals[i] + a*v(i)+b*w(i);
}


double Vector::operator()( const unsigned i ) const{
  Assert( i < n, ExcIndexRange( 0, n, i ) );
  return vals[i];
}

double& Vector::operator()(const unsigned i ){
  Assert( i < n, ExcIndexRange( 0, n, i ) );
  return vals[i];
}

double Vector::l1norm() const{
  double ret_val = 0.;
  for( unsigned i=0; i<n; ++i )
    ret_val += std::fabs( vals[i] );
  return ret_val;
}

double Vector::l2norm() const{
  double ret_val = 0.;
  for( unsigned i=0; i<n; ++i )
    ret_val += vals[i]*vals[i];
  return std::sqrt( ret_val );
}

double Vector::linftynorm() const{
  double ret_val = 0.;
  for( unsigned i=0; i<n; ++i )
    ret_val = std::max( vals[i], ret_val );
  return ret_val;
}

double Vector::lpnorm( const double p ) const{
  Assert( p>0., ExcRange<double>(p) );
  double ret_val = 0.;
  for( unsigned i=0; i<n; ++i )
    ret_val += std::pow( vals[i], p );
  return std::pow( ret_val, 1./p );
}

double Vector::mean_value() const{
  if( n==0 )
    return 0.;
  double ret_val = 0.;
  for( unsigned i=0; i<n; ++i )
    ret_val += vals[i];
  return ret_val/double(n);
}

double Vector::norm_sqr() const{
  double ret_val = 0.;
  for( unsigned i=0; i<n; ++i )
    ret_val += vals[i]*vals[i];
  return ret_val;
}

void Vector::reinit( const unsigned _n, const bool set_values, const double v ){
  n = _n;
  delete[] vals;
  vals = new double[n];
  if( set_values )
    for( unsigned i=0; i<n; ++i )
      vals[i] = v;
}

unsigned Vector::size() const{
  return n;
}

void Vector::swap( Vector &v ){
  Assert( n == v.size(), ExcLength( n, v.size() ) );
  double tmp;
  for( unsigned i=0; i<n; ++i ){
    tmp = vals[i];
    vals[i] = v(i);
    v(i) = tmp;
  }
}

void Vector::reinit( const Vector &v ){
  n = v.size();
  delete[] vals;
  vals = new double[n];
  if( !vals )
    throw ExcMemory();
  for( unsigned i=0; i<n; ++i )
    vals[i] = v(i);
}

double Vector::operator*( const Vector &v ) const{
  Assert( v.size() == n, ExcLength( v.size(), n ) );
  double ret_val = 0.;
  for( unsigned i=0; i<n; ++i )
    ret_val += vals[i]*v(i);
  return ret_val;
}

void Vector::print( std::ostream &op ) const{
  for( unsigned i=0; i<n; ++i )
    op<<vals[i]<<" ";
  op<<std::endl;
}