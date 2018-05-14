#include "../include/SparseMatrix.h"

SparseMatrix::SparseMatrix(): matrix(0), size(0) {}

SparseMatrix::SparseMatrix( const unsigned n ): matrix( new MatrEntry[n] ), size(n){
  if( !matrix )
    throw ExcMemory();
  zero();
}

SparseMatrix::SparseMatrix( const SparseMatrix &matr ){
  copy_from( matr );
}

SparseMatrix::~SparseMatrix(){
  for( unsigned i=0; i<size; ++i )
    delete_row(i);
  delete[] matrix;
}

void SparseMatrix::zero(){
  for( unsigned i=0; i<size; ++i ){
    delete_row(i);
    matrix[i].value = 0.;
    matrix[i].col = i;
    matrix[i].next = 0;
  }
}

void SparseMatrix::reinit( const unsigned n ){
  for( unsigned i=0; i<size; ++i )
    delete_row(i);
  delete[] matrix;
  size = n;
  matrix = new MatrEntry[size];
  if( !matrix )
    throw ExcMemory();
  zero();
}

void SparseMatrix::add( const unsigned i, const unsigned j, const double val ){
  Assert( i<size, ExcIndexRange( 0, size, i ) );
  Assert( j<size, ExcIndexRange( 0, size, j ) );
  MatrEntry *selected_row = &matrix[i];
  while( selected_row ){
    if( selected_row->col == j )
      break;
    selected_row = selected_row->next;
  }
  if( selected_row )
    selected_row->value += val;
  else{
    selected_row = matrix[i].next;
    MatrEntry *nuevo = new MatrEntry;
    if( !nuevo )
      throw ExcMemory();
    nuevo->value = val;
    nuevo->col = j;
    nuevo->next = selected_row;
    matrix[i].next = nuevo;
  }
}

double SparseMatrix::operator()( const unsigned i, const unsigned j ) const{
  Assert( i<size, ExcIndexRange( 0, size, i ) );
  Assert( j<size, ExcIndexRange( 0, size, j ) );
  MatrEntry *selected_row = &matrix[i];
  while( selected_row ){
    if( selected_row->col == j )
      break;
    selected_row = selected_row->next;
  }
  if( selected_row )
    return selected_row->value;
  else
    return 0.;
}

double SparseMatrix::diag( const unsigned i ) const{
  Assert( i< size, ExcIndexRange( 0, size, i ) );
  return matrix[i].value;
}

void SparseMatrix::vmult( const Vector &src, Vector &dst ) const{
  Assert( src.size() == dst.size(), ExcLength( src.size(), dst.size() ) );
  Assert( src.size() == size, ExcLength( src.size(), size ) );
  MatrEntry *row;
  for( unsigned i=0; i<size; ++i ){
    row = &matrix[i];
    dst(i) = 0.;
    while( row ){
      dst(i) += src( row->col )*row->value;
      row = row->next;
    }
  }
}

void SparseMatrix::vmult_add( const Vector &src, Vector &dst ) const{
  Assert( src.size() == dst.size(), ExcLength( src.size(), dst.size() ) );
  Assert( src.size() == size, ExcLength( src.size(), size ) );
  MatrEntry *row;
  for( unsigned i=0; i<size; ++i ){
    row = &matrix[i];
    while( row ){
      dst(i) += src( row->col )*row->value;
      row = row->next;
    }
  }
}

void SparseMatrix::residual( const Vector &src, const Vector &f, Vector &dst ) const{
  Assert( src.size() == dst.size(), ExcLength( src.size(), dst.size() ) );
  Assert( src.size() == size, ExcLength( src.size(), size ) );
  Assert( src.size() == f.size(), ExcLength( src.size(), f.size() ) );
  MatrEntry *row;
  for( unsigned i=0; i<size; ++i ){
    row = &matrix[i];
    dst(i) = f(i);
    while( row ){
      dst(i) -= src( row->col )*row->value;
      row = row->next;
    }
  }
}

unsigned SparseMatrix::n_rows() const{
  return size;
}

void SparseMatrix::copy_from( const SparseMatrix &b ){
  if( matrix == b.matrix )
    return;
  if( size != b.n_rows() )
    reinit( b.n_rows() );
  MatrEntry *pb, *pa, *ppa;
  for( unsigned i=0; i<size; ++i ){
    matrix[i].value = b.matrix[i].value;
    matrix[i].col = b.matrix[i].col;
    matrix[i].next = 0;
    ppa = &matrix[i];
    pb = b.matrix[i].next;
    while( pb ){
      pa = new MatrEntry;
      if( !pa )
        throw ExcMemory();
      pa->next = ppa->next;
      ppa->next = pa;
      pa->value = pb->value;
      pa->col = pb->col;
      ppa = pa;
      pb = pb->next;
    }
  }
}

void SparseMatrix::delete_row( const unsigned row ){
  Assert( row < size, ExcIndexRange( 0, size, row ) );
  MatrEntry *p = matrix[row].next, *q;
  while(p){
    q = p->next;
    delete p;
    p = q;
  }
  matrix[row].next = 0;
  matrix[row].value = 0.;
  matrix[row].col = row;
}

void SparseMatrix::print( std::ostream &op ) const{
  for( unsigned i=0; i<size; ++i ){
    op<<i<<": ";
    MatrEntry *m = &matrix[i];
    while( m ){
      op<<"("<<m->value<<","<<m->col<<") ";
      m = m->next;
    }
    op<<std::endl;
  }
}