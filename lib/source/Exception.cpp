#include "../include/Exception.h"

ExcBase::ExcBase(){}
ExcBase::ExcBase( const ExcBase &e ){
  message<<e.what();
}
const char* ExcBase::what() const{
  return message.str().c_str();
}
ExcBase &ExcBase::operator=( const ExcBase &e ){
  message.flush();
  message<<e.what();
  return *this;
}

ExcMemory::ExcMemory(){
  message<<" Not enough memory ";
}

ExcIndexRange::ExcIndexRange( const unsigned li, const unsigned ri, const unsigned i ){
  message<<"Index "<<i<<" out of range ["<<li<<","<<ri<<")";
}

/// A parameter is out of limits
template<typename par> ExcRange<par>::ExcRange( const par i ){
  message<<" The parameter "<<i<<" is out range";
}

template class ExcRange<double>;


ExcLength::ExcLength( const unsigned a, const unsigned b ){
  message<<" The lengths do not coincide: "<<a<<"<>"<<b;
}

ExcFile::ExcFile( const std::string filename ){
  message<<" File error: "<<filename;
}

ExcInternal::ExcInternal(){
  message<<" Internal Error";
}

ExcConvergence::ExcConvergence(){
  message<<" The iterative method did not converge";
}


ExcFE::ExcFE(){
  message<<" The finite element space is not initialized";
}
