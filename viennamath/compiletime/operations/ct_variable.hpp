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
#include "viennamath/compiletime/ct_expr.hpp"

#include <assert.h>

namespace viennamath
{

  ////////////////// Operations //////////////////////////////
  
  ////////////// operator+
  template <id_type id, typename LHS, typename OP, typename RHS>
  ct_expr<ct_variable<id>,
          op_plus<default_numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator+(ct_variable<id> const & lhs, 
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_plus<default_numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <id_type id1, id_type id2>
  ct_expr<ct_variable<id1>,
          op_plus<default_numeric_type>,
          ct_variable<id2> >
  operator+(ct_variable<id1> const & lhs,
            ct_variable<id2> const & other)
  {
    return ct_expr<ct_variable<id1>,
                   op_plus<default_numeric_type>,
                   ct_variable<id2> >(lhs, other);
  }

  template <id_type id>
  ct_expr<ct_constant<2>,
          op_mult<default_numeric_type>,
          ct_variable<id> >
  operator+(ct_variable<id> const & lhs,
            ct_variable<id> const & other)
  {
    return ct_expr<ct_constant<2>,
                   op_mult<default_numeric_type>,
                   ct_variable<id> >(ct_constant<2>(), lhs);
  }

  template <id_type id, long value>
  ct_expr<ct_variable<id>,
          op_plus<default_numeric_type>,
          ct_constant<value> >
  operator+(ct_variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_plus<default_numeric_type>,
                   ct_constant<value> >(lhs, other);
  }



  ////////// operator-
  template <id_type id, typename LHS, typename OP, typename RHS>
  ct_expr<ct_variable<id>,
          op_minus<default_numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator-(ct_variable<id> const & lhs, 
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_minus<default_numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <id_type id1, id_type id2>
  ct_expr<ct_variable<id1>,
          op_minus<default_numeric_type>,
          ct_variable<id2> >
  operator-(ct_variable<id1> const & lhs,
            ct_variable<id2> const & other)
  {
    return ct_expr<ct_variable<id1>,
                   op_minus<default_numeric_type>,
                   ct_variable<id2> >(lhs, other);
  }

  template <id_type id>
  ct_constant<0>
  operator-(ct_variable<id> const & lhs,
            ct_variable<id> const & other)
  {
    return ct_constant<0>();
  }

  template <id_type id, long value>
  ct_expr<ct_variable<id>,
          op_minus<default_numeric_type>,
          ct_constant<value> >
  operator-(ct_variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_minus<default_numeric_type>,
                   ct_constant<value> >(lhs, other);
  }


  ////////////// operator*
  template <id_type id, typename LHS, typename OP, typename RHS>
  ct_expr<ct_variable<id>,
          op_mult<default_numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator*(ct_variable<id> const & lhs, 
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_mult<default_numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <id_type id1, id_type id2>
  ct_expr<ct_variable<id1>,
          op_mult<default_numeric_type>,
          ct_variable<id2> >
  operator*(ct_variable<id1> const & lhs,
            ct_variable<id2> const & other)
  {
    return ct_expr<ct_variable<id1>,
                   op_mult<default_numeric_type>,
                   ct_variable<id2> >(lhs, other);
  }
  
  template <id_type id>
  ct_expr<ct_variable<id>,
          op_mult<default_numeric_type>,
          ct_variable<id> >
  operator*(ct_variable<id> const & lhs,
            ct_variable<id> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_mult<default_numeric_type>,
                   ct_variable<id> >(lhs, other);
  }

  template <id_type id, long value>
  ct_expr<ct_variable<id>,
          op_mult<default_numeric_type>,
          ct_constant<value> >
  operator*(ct_variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_mult<default_numeric_type>,
                   ct_constant<value> >(lhs, other);
  }


  //////////// operator/
  template <id_type id, typename LHS, typename OP, typename RHS>
  ct_expr<ct_variable<id>,
          op_div<default_numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator/(ct_variable<id> const & lhs, 
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_div<default_numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <id_type id1, id_type id2>
  ct_expr<ct_variable<id1>,
          op_div<default_numeric_type>,
          ct_variable<id2> >
  operator/(ct_variable<id1> const & lhs,
            ct_variable<id2> const & other)
  {
    return ct_expr<ct_variable<id1>,
                   op_div<default_numeric_type>,
                   ct_variable<id2> >(lhs, other);
  }

  template <id_type id>
  ct_constant<1>
  operator/(ct_variable<id> const & lhs,
            ct_variable<id> const & other)
  {
    return ct_constant<1>();
  }

  template <id_type id, long value>
  ct_expr<ct_variable<id>,
          op_div<default_numeric_type>,
          ct_constant<value> >
  operator/(ct_variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<ct_variable<id>,
                   op_div<default_numeric_type>,
                   ct_constant<value> >(lhs, other);
  }

}

#endif