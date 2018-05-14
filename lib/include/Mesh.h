#ifndef _MESH_H_
#define _MESH_H_

/**
  Mesh.
  Since this is just going to be for illustration purposes, this object is quite simple.
  In the constructor we indicate the left and right endpoints of the interval and the number
  of refines (cells) we want to have.
  A more complete object would allow for local refinement, getting information on neighbors,
  etc.
  This, of course, would require that, while keeping the same interface (for compatibility),
  the internals be completely restructured. For instance, the structre used to describe
  elements should be expanded, the set of elements should be organized differently (binary
  tree?), etc.
**/

#include <vector>
#include <cmath>

#include "Exception.h"

class Mesh{
  public:
    // Constructor. the interval is (_xl,_xr) and we will have n_cells
    Mesh( const unsigned n_cells = 1, const double _xl = 0., const double _xr = 1. );
    ~Mesh();
    // Get the number of points
    unsigned n_points() const;
    // Get the number of cells: n_cells = n_points-1 (in 1d)
    unsigned n_cells() const;
    // This structure is used to give the real geometry of the cell
    struct cell{
      double points[2];
      unsigned index, indices[2];
      cell(): index(-1) {}
      double diameter() const{return points[1] - points[0];};
    };
    // Get cell with index i.
    void get_cell( const unsigned i, cell &res ) const;
  protected:
    // The interval is (xl,xr)
    const double xl, xr;
    // number of points and number of cells
    const unsigned np, nc;
    // The points
    std::vector<double> points;
    // We just store the indices of the points that make the elements
    struct elements{
      unsigned points[2];
    };
    // The elements
    std::vector<elements> elts;
  private:
    Mesh( const Mesh &mm );
    void operator=( const Mesh &m );
};

#endif
