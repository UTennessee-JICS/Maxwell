#include <iostream>

#include "Laplace.h"

int main(){
  try{
    std::cout<<" Creating Problem..."<<std::endl;
    LaplaceProblem prb(64);
    std::cout<<" Assembling..."<<std::endl;
    prb.Assemble();
    std::cout<<" Solving..."<<std::endl;
    unsigned iterations = prb.Solve();
    std::cout<<" Solved!. Number of Iterations = "<<iterations<<std::endl;
    std::cout<<" Plotting..."<<std::endl;
    prb.Plot( "solution.gpl" );
    std::cout<<" Done!!!"<<std::endl;
  }catch( ExcBase &err ){
    std::cerr<<" An exception has occurred."<<std::endl
             <<" The available information is: "<<err.what()<<std::endl
             <<" :-("<<std::endl;
    return 1;
  }catch( ... ){
    std::cerr<<" An unknown exception has occurred!!!"<<std::endl
             <<" :-("<<std::endl;
    return 1;
  }
  std::cout<<" Everything went fine!"<<std::endl<<" :-)"<<std::endl;
  return 0;
}
