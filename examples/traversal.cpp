
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "viennamath/expression.hpp"

//
// Testing functors on expression tree
//


struct cout_functor : public viennamath::rt_traversal_interface<>
{
  typedef viennamath::default_interface_type   InterfaceType;
  
  void operator()(InterfaceType const * e) const 
  {
    if (viennamath::callback_if_castable< viennamath::binary_expr >::apply(e, *this))
      return;

    if (viennamath::callback_if_castable< viennamath::variable >::apply(e, *this))
      return;

    if (viennamath::callback_if_castable< viennamath::constant >::apply(e, *this))
      return;

    if (viennamath::callback_if_castable< viennamath::unary_expr >::apply(e, *this))
      return;
    
    //unknown:
    std::cout << "non-dispatched type: " << e->shallow_str() << std::endl;
  }
  
  void operator()(viennamath::binary_expr const & x) const
  {
    std::cout << "binary_expr, dispatched!" << std::endl; 
  }

  void operator()(viennamath::variable const & x) const
  {
    std::cout << "variable, dispatched!" << std::endl; 
  }

  void operator()(viennamath::constant const & x) const
  {
    std::cout << "constant, dispatched!" << std::endl; 
  }

  void operator()(viennamath::unary_expr const & x) const
  {
    std::cout << "unary_expr, dispatched!" << std::endl; 
  }

};


int main()
{
  viennamath::variable x(0);
  viennamath::variable y(1);
  viennamath::variable z(2);
  viennamath::rt_constant<double> c4(4.0);
  viennamath::rt_constant<long> c6(6);

  
  viennamath::expr e1 = x + y - z;
  viennamath::expr e2 = viennamath::sin(x);
  
  
  viennamath::rt_traversal_wrapper<> fun(new cout_functor());
  
  std::cout << "---------------" << std::endl;
  e1.get()->recursive_traversal( fun );

  std::cout << "---------------" << std::endl;
  e2.get()->recursive_traversal( fun );
  
  std::cout << "****************************************************" << std::endl;
  std::cout << "*****     TUTORIAL COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "****************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}