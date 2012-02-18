/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EQUATION_HPP
#define VIENNAMATH_EQUATION_HPP

#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  /** @brief A runtime rt_equation */
  template <typename InterfaceType>
  class rt_equation
  {

    public:
      typedef rt_expr<InterfaceType>     value_type;
      typedef InterfaceType           interface_type;
      
      rt_equation() {};
      
      
      rt_equation(const rt_expr<InterfaceType> & lhs,
                  const rt_expr<InterfaceType> & rhs) : lhs_(lhs.get()->clone()), rhs_(rhs.get()->clone()) {}
      
      rt_expr<InterfaceType> const & lhs() const { return lhs_; }
      rt_expr<InterfaceType> const & rhs() const { return rhs_; }
      
    private:
      rt_expr<InterfaceType> lhs_;
      rt_expr<InterfaceType> rhs_;
  };

  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, rt_equation<InterfaceType> const & e)
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
  rt_equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, rt_constant<NumericT, InterfaceType> const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }
  
  template <typename InterfaceType>
  rt_equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, rt_variable<InterfaceType> const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  template <id_type id>
  rt_equation<> make_equation(default_numeric_type lhs, ct_variable<id> const & rhs)
  {
    return rt_equation<>(lhs, rhs); 
  }

  template <typename InterfaceType>
  rt_equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, rt_unary_expr<InterfaceType> const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  rt_equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, rt_binary_expr<InterfaceType> const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  rt_equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, rt_expr<InterfaceType> const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  
  //constant:
  template <typename NumericT, typename InterfaceType, typename RHSType>
  rt_equation<InterfaceType> make_equation(rt_constant<NumericT, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  //variable:
  template <typename InterfaceType, typename RHSType>
  rt_equation<InterfaceType> make_equation(rt_variable<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  //function_symbol:
  template <typename InterfaceType, typename RHSType>
  rt_equation<InterfaceType> make_equation(rt_function_symbol<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  //unary:
  template <typename InterfaceType, typename RHSType>
  rt_equation<InterfaceType> make_equation(rt_unary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }


  //binary
  template <typename InterfaceType, typename RHSType>
  rt_equation<InterfaceType> make_equation(rt_binary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  //expr
  template <typename InterfaceType, typename RHSType>
  rt_equation<InterfaceType> make_equation(rt_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_equation<InterfaceType>(lhs, rhs); 
  }

  //compile time with run time stuff also possible:
  template <typename LHS, typename OP, typename RHS, typename RHSType>
  rt_equation<> make_equation(ct_binary_expr<LHS, OP, RHS> const & lhs, RHSType const & rhs)
  {
    return rt_equation<>(lhs, rhs); 
  }

  template <typename LHS, typename OP, typename RHSType>
  rt_equation<> make_equation(ct_unary_expr<LHS, OP> const & lhs, RHSType const & rhs)
  {
    return rt_equation<>(lhs, rhs); 
  }

  template <long val, typename RHSType>
  rt_equation<> make_equation(ct_constant<val> const & lhs, RHSType const & rhs)
  {
    return rt_equation<>(lhs, rhs); 
  }

  template <typename TAG, typename RHSType>
  rt_equation<> make_equation(ct_function_symbol<TAG> const & lhs, RHSType const & rhs)
  {
    return rt_equation<>(lhs, rhs); 
  }

  template <id_type id, typename RHSType>
  rt_equation<> make_equation(ct_variable<id> const & lhs, RHSType const & rhs)
  {
    return rt_equation<>(lhs, rhs); 
  }
  
}

#endif