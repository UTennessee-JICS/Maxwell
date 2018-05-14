#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_

/**
  An implementation of square Sparse Matrices using a hash table.
**/

#include "Vector.h"

#include <iostream>

class SparseMatrix{
  public:
    friend class PreconditionBase;
    friend void SetDirichletBC( SparseMatrix &sp, Vector &rhs,
                     const unsigned i, const double val );
    // Empty constructor
    SparseMatrix();
    // Constructor with a specified size
    SparseMatrix( const unsigned n );
    // Copy Constructor
    SparseMatrix( const SparseMatrix &matr );
    ~SparseMatrix();
    // Set the matrix to zero
    void zero();
    // Reinitialize size and set to zero
    void reinit( const unsigned n );
    // add val to the entry ij, if this does not exist create it
    void add( const unsigned i, const unsigned j, const double val );
    // a_{ij}. This operation is O(bandwidth) so it should NOT be used often
    double operator()( const unsigned i, const unsigned j ) const;
    // diagonal element
    double diag( const unsigned i ) const;
    // dst = this*src
    void vmult( const Vector &src, Vector &dst ) const;
    // dst += this*src
    void vmult_add( const Vector &src, Vector &dst ) const;
    // dst = f-this*src
    void residual( const Vector &src, const Vector &f, Vector &dst ) const;
    // number of rows
    unsigned n_rows() const;
    // copy operator
    void copy_from( const SparseMatrix &b );
    void print( std::ostream &op ) const;
  protected:
    /*
      This structure implements the entries of the hash table.
      The table is indexed by the row index and collisions are handled with the column index
    */
    struct MatrEntry{
      // The value of the matrix entry
      double value;
      // The column
      unsigned col;
      // The next element in the list
      MatrEntry *next;
    };
    // The actual hash table
    MatrEntry *matrix;
    // The size
    unsigned size;
    // Delete a row
    void delete_row( const unsigned row );
  private:
    void operator=( const SparseMatrix &matr ) {};
};

#endif
