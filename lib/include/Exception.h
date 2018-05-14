#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_
/**
  Basic exceptions for common errors
**/

#include <sstream>
#include <string>

//The Assert macro
#ifdef DEBUG
  #define Assert(cond, exc){ \
    if( !(cond) ) \
      throw exc; \
  }
#else
  #define Assert(cond,exc){}
#endif

/// Base class, so that we have a common interface
class ExcBase{
  public:
    ExcBase();
    ExcBase( const ExcBase &e );
    ExcBase &operator=( const ExcBase &e );
    const char* what() const;
  protected:
    std::stringstream message;
};

/// Memory error. For instance allocation failed
class ExcMemory: public ExcBase{
  public:
    ExcMemory();
};

/// An index is out of limits.
class ExcIndexRange: public ExcBase{
  public:
    ExcIndexRange( const unsigned li, const unsigned ri, const unsigned i );
};

/// A parameter is out of limits
template<typename par> class ExcRange: public ExcBase{
  public:
    ExcRange( const par i );
};

/// Lengths do not coincide
class ExcLength: public ExcBase{
  public:
    ExcLength( const unsigned a, const unsigned b );
};

/// File not open
class ExcFile: public ExcBase{
  public:
    ExcFile( const std::string filename );
};

/// Internal error
class ExcInternal: public ExcBase{
  public:
    ExcInternal();
};

/// The iterative method did not converge
class ExcConvergence: public ExcBase{
  public:
    ExcConvergence();
};

/// The Finite Element space is not initialized
class ExcFE: public ExcBase{
  public:
    ExcFE();
};

#endif