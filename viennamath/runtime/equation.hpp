/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EQUATION_CPP
#define VIENNAMATH_EQUATION_CPP

#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  /** @brief A runtime equation */
  template <typename InterfaceType>
  class equation
  {

    public:
      equation() {};
      
      
      equation(const expr<InterfaceType> & lhs,
               const expr<InterfaceType> & rhs) : lhs_(lhs.get()->clone()), rhs_(rhs.get()->clone()) {}
      
      expr<InterfaceType> const & lhs() const { return lhs_; }
      expr<InterfaceType> const & rhs() const { return rhs_; }
      
    private:
      expr<InterfaceType> lhs_;
      expr<InterfaceType> rhs_;
  };

  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, equation<InterfaceType> const & e)
  {
    stream << "equation(" << e.lhs() << " = " << e.rhs() << ")";
    return stream;
  }
  
  
  
  
  //////// helper functions for creating equations (uniform interface for compile time and run time: ///////////
  
  
  //
  // run time
  //
  
  ////// scalar is first argument:
  template <typename NumericT, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, constant<NumericT, InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }
  
  template <unsigned long id, typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, variable<id, InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }
  
  template <typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, unary_expr<InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, binary_expr<InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, expr<InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  
  //constant:
  template <typename NumericT, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(constant<NumericT, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //variable:
  template <unsigned long id, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(variable<id, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //function_symbol:
  template <typename T, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(function_symbol<T, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //unary:
  template <typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(unary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }


  //binary
  template <typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(binary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //expr
  template <typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //compile time with run time stuff also possible:
  template <typename LHS, typename OP, typename RHS, typename RHSType>
  equation<> make_equation(ct_expr<LHS, OP, RHS> const & lhs, RHSType const & rhs)
  {
    return equation<>(lhs, rhs); 
  }

  
}

#endif