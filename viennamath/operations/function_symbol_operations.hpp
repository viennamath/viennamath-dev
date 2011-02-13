/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_FUNCTION_SYMBOL_OPERATIONS_HPP
#define VIENNAMATH_FUNCTION_SYMBOL_OPERATIONS_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/promote_traits.hpp"
#include "viennamath/binary_operators.hpp"

namespace viennamath
{
  
      
    ////////////////// Operations //////////////////////////////
    
    ////// operator+
    
    ////// operator-

    ////// operator*
    template <typename NumericT, typename InterfaceType, typename T>
    binary_expr<InterfaceType> operator*(constant<NumericT, InterfaceType> const & lhs, function_symbol<T, InterfaceType> const & rhs)
    {
      return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
    }

    template <typename InterfaceType, typename T>
    binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs, function_symbol<T, InterfaceType> const & rhs)
    {
      return binary_expr<InterfaceType>(lhs.get()->clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
    }

    ////// operator/

  
}

#endif