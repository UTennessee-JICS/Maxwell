#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "Exception.h"
#include "SparseMatrix.h"
#include "Vector.h"
#include "FESpace.h"
#include "Mesh.h"

#include <fstream>
#include <string>

void SetDirichletBC( SparseMatrix &sp, Vector &rhs,
                     const unsigned i, const double val = 0. );

void plot( const Vector &x, FEP1 &fe, const std::string &filename );

#endif
