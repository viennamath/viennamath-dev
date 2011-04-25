
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "viennamath/expression.hpp"

//
// Testing functors on expression tree
//


struct cout_functor : public viennamath::functor_interface<>
{
  typedef viennamath::default_interface_type   InterfaceType;
  
  InterfaceType * apply(InterfaceType const * e) const 
  {
    std::cout << e->shallow_str() << std::endl;
    return NULL;
  }
};


int main()
{
  viennamath::variable<> x(0);
  viennamath::variable<> y(1);
  viennamath::variable<> z(2);
  viennamath::constant<double> c4(4.0);
  viennamath::constant<long> c6(6);

  
  viennamath::expr<> e1 = x + y - z;
  viennamath::expr<> e2 = viennamath::sin(x);
  
  
  viennamath::functor_wrapper<> fun(new cout_functor());
  
  std::cout << "---------------" << std::endl;
  e1.get()->recursive_action( fun );

  std::cout << "---------------" << std::endl;
  e2.get()->recursive_action( fun );
  
  return EXIT_SUCCESS;
}