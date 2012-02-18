/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_COMPILETIME_OPERATION_VARIABLE_HPP
#define VIENNAMATH_COMPILETIME_OPERATION_VARIABLE_HPP

#include "viennamath/compiletime/ct_constant.hpp"
#include "viennamath/compiletime/ct_variable.hpp"
#include "viennamath/compiletime/ct_binary_expr.hpp"

#include <assert.h>

namespace viennamath
{

  ////////////////// Operations //////////////////////////////
  
  ////////////// operator+

  template <id_type id>
  ct_binary_expr<ct_constant<2>,
                 op_mult<default_numeric_type>,
                 ct_variable<id> >
  operator+(ct_variable<id> const & lhs,
            ct_variable<id> const & other)
  {
    return ct_binary_expr<ct_constant<2>,
                          op_mult<default_numeric_type>,
                          ct_variable<id> >(ct_constant<2>(), lhs);
  }

  ////////// operator-

  template <id_type id>
  ct_constant<0>
  operator-(ct_variable<id> const & lhs,
            ct_variable<id> const & other)
  {
    return ct_constant<0>();
  }



  ////////////// operator*


  //////////// operator/

  template <id_type id>
  ct_constant<1>
  operator/(ct_variable<id> const & lhs,
            ct_variable<id> const & other)
  {
    return ct_constant<1>();
  }

}

#endif