#ifndef _LAPLACE_PROBLEM_H_
#define _LAPLACE_PROBLEM_H_

#include "lib/include/Problem.h"

class LaplaceProblem: public Problem{
  public:
    LaplaceProblem( const unsigned n_cells );
    ~LaplaceProblem();
  protected:
    virtual void cell_integrator( const cell_integration_info &ci,
                                  cell_integration_data &cd ) const;
    virtual void Apply_BCs();
  private:
    double RHS( const double x ) const;
};

#endif
