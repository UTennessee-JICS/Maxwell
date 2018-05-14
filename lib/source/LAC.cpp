#include "../include/LAC.h"

PreconditionBase::PreconditionBase( const SparseMatrix &sp ):
                  matr( &sp ) {}
PreconditionBase::~PreconditionBase(){}
void PreconditionBase::reinit( const SparseMatrix &sp ){
  matr = &sp;
}

PreconditionJacobi::PreconditionJacobi( const SparseMatrix &sp ):
                  PreconditionBase( sp ){}
PreconditionJacobi::~PreconditionJacobi(){}
void PreconditionJacobi::vmult( const Vector &src, Vector &dst ) const{
  Assert( src.size() == dst.size(), ExcLength( src.size(), dst.size() ) );
  Assert( src.size() == matr->n_rows(), ExcLength( src.size(), matr->n_rows() ) );
  const unsigned n = src.size();
  for( unsigned i=0; i<n; ++i )
    dst(i) = src(i)/matr->diag(i);
}


SolverBase::SolverBase( const unsigned mi, const double e ):
            max_its( mi ), error( e ) {}
SolverBase::~SolverBase() {}

/// This is the basic two-level stationary iterative solver.
/// The solution of Ax=f is approximated by the scheme
/// x^{k+1} = x^k + \tau B ( f - Ax^k )
Solver::Solver( const unsigned mi, const double e, const double t ):
        SolverBase( mi, e ), tau(t) {}
Solver::~Solver() {}
unsigned Solver::solve( const SparseMatrix &A, Vector &x, const Vector &f,
                    const PreconditionBase *B ) const{
  Assert( f.size() == x.size(), ExcLength( x.size(), f.size() ) );
  Assert( A.n_rows() == x.size(), ExcLength( A.n_rows(), x.size() ) );
  res.reinit( x.size() );
  tmp.reinit( x.size() );
  unsigned its = 0;
  double curr_err;
  for( its=0; its<max_its; ++its ){
    A.residual( x, f, res );
    B->vmult( res, tmp );
    x.add( tau, tmp );
    curr_err = tau*tmp.l2norm();///x.l2norm();
    if( curr_err <= error )
      break;
  }
  if( its >= max_its )
    throw ExcConvergence();
  return its;
}
