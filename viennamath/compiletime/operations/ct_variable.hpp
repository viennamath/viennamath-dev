#ifndef VIENNAMATH_COMPILETIME_OPERATIONS_CT_VARIABLE_HPP
#define VIENNAMATH_COMPILETIME_OPERATIONS_CT_VARIABLE_HPP

/* =======================================================================
   Copyright (c) 2012, Institute for Microelectronics,
                       Institute for Analysis and Scientific Computing,
                       TU Wien.
                             -----------------
               ViennaMath - Symbolic and Numerical Math in C++
                             -----------------

   Author:     Karl Rupp                          rupp@iue.tuwien.ac.at

   License:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */




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