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
#include "viennamath/runtime/binary_operators.hpp"

namespace viennamath
{
  
      
    ////////////////// Operations //////////////////////////////
    
    ////// operator+
    
    ////// operator-

    ////// operator*
    template <typename NumericT, typename InterfaceType>
    rt_binary_expr<InterfaceType> operator*(rt_constant<NumericT, InterfaceType> const & lhs, rt_function_symbol<InterfaceType> const & rhs)
    {
      return rt_binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
    }

    template <typename InterfaceType>
    rt_binary_expr<InterfaceType> operator*(rt_expr<InterfaceType> const & lhs, rt_function_symbol<InterfaceType> const & rhs)
    {
      return rt_binary_expr<InterfaceType>(lhs.get()->clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
    }

    ////// operator/

  
}

#endif