#ifndef _LINEAR_ALGEBRA_H_
#define _LINEAR_ALGEBRA_H_

/**
  Linear Algebra stuff.
  Preconditioners and Solvers
**/

#include "SparseMatrix.h"

/**
  Interface of a Preconditioner
  This has a MAJOR flaw. We do not check for the validity of the pointer to
  the matrix that we are preconditioning. I don't wanna use BooST or something
  like that for SmartPointers so we will hope this does not
  lead to bad things....
**/
class PreconditionBase{
  public:
    // Constructor. We pass the matrix that we want to precondition
    PreconditionBase( const SparseMatrix &sp );
    virtual ~PreconditionBase();
    // Application of the preconditioner dst = B*src
    virtual void vmult( const Vector &src, Vector &dst ) const = 0;
    // Change the matrix we are preconditioning
    virtual void reinit( const SparseMatrix &sp );
  protected:
    SparseMatrix const *matr;
  private:
    PreconditionBase( const PreconditionBase &pc );
    void operator=( const PreconditionBase &pc );
};

/// Jacobi Preconditioner
class PreconditionJacobi: public PreconditionBase{
  public:
    PreconditionJacobi( const SparseMatrix &sp );
    virtual ~PreconditionJacobi();
    virtual void vmult( const Vector &src, Vector &dst ) const;
};

/// Interface of a Solver
class SolverBase{
  public:
    // Constructor. We pass the maximal number of iterarions and accuracy
    SolverBase( const unsigned mi, const double e );
    virtual ~SolverBase();
    // The actual solving procedure. The arguments are clear
    virtual unsigned solve( const SparseMatrix &A, Vector &x, const Vector &f,
                    const PreconditionBase *B ) const = 0;
  protected:
    // Number of iterations
    const unsigned max_its;
    // Accuracy
    const double error;

};

/// This is the basic two-level stationary iterative solver.
/// The solution of Ax=f is approximated by the scheme
/// x^{k+1} = x^k + \tau B ( f - Ax^k )
class Solver: public SolverBase{
  public:
    Solver( const unsigned mi, const double e, const double t );
    ~Solver();
    virtual unsigned solve( const SparseMatrix &A, Vector &x, const Vector &f,
                    const PreconditionBase *B ) const ;
  protected:
    // The relaxation parameter
    const double tau;
  private:
    // Temporary vectors
    mutable Vector res, tmp;
};

#endif