#ifndef VIENNAMATH_COMPILETIME_CT_INTERVAL_HPP
#define VIENNAMATH_COMPILETIME_CT_INTERVAL_HPP

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




#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  /** @brief A compile time interval */
  template <typename LHS, typename RHS>
  class ct_interval {};
  
  template <typename LHS, typename RHS>
  std::ostream& operator<<(std::ostream & stream, ct_interval<LHS, RHS> const & u)
  {
    stream << "ct_interval(" << LHS() << ", " << RHS() << ")";
    return stream;
  }

  
  //
  // compile time 
  // [binary expression, unary expression, constant, function symbol, variable] for each argument -> 25 overloads
  //
  
  //
  //first argument: binary expression
  template <typename LHS1, typename OP1, typename RHS1,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
              ct_binary_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_binary_expr<LHS1, OP1, RHS1> const & lhs,
                ct_binary_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
                       ct_binary_expr<LHS2, OP2, RHS2> >(); 
  }
  
  template <typename LHS1, typename OP1, typename RHS1,
            typename LHS2, typename OP2>
  ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
              ct_unary_expr<LHS2, OP2> > 
  make_interval(ct_binary_expr<LHS1, OP1, RHS1> const & lhs,
                ct_unary_expr<LHS2, OP2> const & rhs)
  {
    return ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
                       ct_unary_expr<LHS2, OP2> >(); 
  }
  
  template <typename LHS1, typename OP1, typename RHS1,
            long value>
  ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
              ct_constant<value> > 
  make_interval(ct_binary_expr<LHS1, OP1, RHS1> const & lhs,
                ct_constant<value> const & rhs)
  {
    return ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
                       ct_constant<value> >(); 
  }

  template <typename LHS1, typename OP1, typename RHS1,
            typename TAG>
  ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
              ct_function_symbol<TAG> > 
  make_interval(ct_binary_expr<LHS1, OP1, RHS1> const & lhs,
                ct_function_symbol<TAG> const & rhs)
  {
    return ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
                       ct_function_symbol<TAG> >(); 
  }

  template <typename LHS1, typename OP1, typename RHS1,
            id_type id>
  ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
              ct_variable<id> > 
  make_interval(ct_binary_expr<LHS1, OP1, RHS1> const & lhs,
                ct_variable<id> const & rhs)
  {
    return ct_interval<ct_binary_expr<LHS1, OP1, RHS1>,
                       ct_variable<id> >(); 
  }


  //
  //first argument: unary expression
  template <typename LHS1, typename OP1,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_unary_expr<LHS1, OP1>,
              ct_binary_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_unary_expr<LHS1, OP1> const & lhs,
                ct_binary_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_unary_expr<LHS1, OP1>,
                       ct_binary_expr<LHS2, OP2, RHS2> >(); 
  }

  template <typename LHS1, typename OP1,
            typename LHS2, typename OP2>
  ct_interval<ct_unary_expr<LHS1, OP1>,
              ct_unary_expr<LHS2, OP2> > 
  make_interval(ct_unary_expr<LHS1, OP1> const & lhs,
                ct_unary_expr<LHS2, OP2> const & rhs)
  {
    return ct_interval<ct_unary_expr<LHS1, OP1>,
                       ct_unary_expr<LHS2, OP2> >(); 
  }

  template <typename LHS1, typename OP1,
            long value>
  ct_interval<ct_unary_expr<LHS1, OP1>,
              ct_constant<value> > 
  make_interval(ct_unary_expr<LHS1, OP1> const & lhs,
                ct_constant<value> const & rhs)
  {
    return ct_interval<ct_unary_expr<LHS1, OP1>,
                       ct_constant<value> >(); 
  }

  template <typename LHS1, typename OP1,
            typename TAG>
  ct_interval<ct_unary_expr<LHS1, OP1>,
              ct_function_symbol<TAG> >
  make_interval(ct_unary_expr<LHS1, OP1> const & lhs,
                ct_function_symbol<TAG> const & rhs)
  {
    return ct_interval<ct_unary_expr<LHS1, OP1>,
                       ct_function_symbol<TAG> >(); 
  }

  template <typename LHS1, typename OP1,
            id_type id>
  ct_interval<ct_unary_expr<LHS1, OP1>,
              ct_variable<id> > 
  make_interval(ct_unary_expr<LHS1, OP1> const & lhs,
                ct_variable<id> const & rhs)
  {
    return ct_interval<ct_unary_expr<LHS1, OP1>,
                       ct_variable<id> >(); 
  }


  //
  //first argument: ct_constant
  template <long value1,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_constant<value1>,
              ct_binary_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_binary_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_binary_expr<LHS2, OP2, RHS2> >(); 
  }

  template <long value1,
            typename LHS2, typename OP2>
  ct_interval<ct_constant<value1>,
              ct_unary_expr<LHS2, OP2> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_unary_expr<LHS2, OP2> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_unary_expr<LHS2, OP2> >(); 
  }
  
  template <long value1,
            long value2>
  ct_interval<ct_constant<value1>,
              ct_constant<value2> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_constant<value2> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_constant<value2> >(); 
  }

  template <long value1,
            typename TAG>
  ct_interval<ct_constant<value1>,
              ct_function_symbol<TAG> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_function_symbol<TAG> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_function_symbol<TAG> >(); 
  }


  template <long value1,
            id_type id>
  ct_interval<ct_constant<value1>,
              ct_variable<id> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_variable<id> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_variable<id> >(); 
  }


  //
  //first argument: function symbol
  template <typename TAG,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_function_symbol<TAG>,
              ct_binary_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_function_symbol<TAG> const & lhs,
                ct_binary_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_function_symbol<TAG>,
                       ct_binary_expr<LHS2, OP2, RHS2> >(); 
  }

  template <typename TAG,
            typename LHS2, typename OP2>
  ct_interval<ct_function_symbol<TAG>,
              ct_unary_expr<LHS2, OP2> > 
  make_interval(ct_function_symbol<TAG> const & lhs,
                ct_unary_expr<LHS2, OP2> const & rhs)
  {
    return ct_interval<ct_function_symbol<TAG>,
                       ct_unary_expr<LHS2, OP2> >(); 
  }

  template <typename TAG,
            long value>
  ct_interval<ct_function_symbol<TAG>,
              ct_constant<value> > 
  make_interval(ct_function_symbol<TAG> const & lhs,
                ct_constant<value> const & rhs)
  {
    return ct_interval<ct_function_symbol<TAG>,
                       ct_constant<value> >(); 
  }

  template <typename TAG1,
            typename TAG2>
  ct_interval<ct_function_symbol<TAG1>,
              ct_function_symbol<TAG2> >
  make_interval(ct_function_symbol<TAG1> const & lhs,
                ct_function_symbol<TAG2> const & rhs)
  {
    return ct_interval<ct_function_symbol<TAG1>,
                       ct_function_symbol<TAG2> >(); 
  }

  template <typename TAG,
            id_type id>
  ct_interval<ct_function_symbol<TAG>,
              ct_variable<id> > 
  make_interval(ct_function_symbol<TAG> const & lhs,
                ct_variable<id> const & rhs)
  {
    return ct_interval<ct_function_symbol<TAG>,
                       ct_variable<id> >(); 
  }


  //
  //first argument: variable
  template <id_type id1,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_variable<id1>,
              ct_binary_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_binary_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_binary_expr<LHS2, OP2, RHS2> >(); 
  }
  
  template <id_type id1,
            typename LHS2, typename OP2>
  ct_interval<ct_variable<id1>,
              ct_unary_expr<LHS2, OP2> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_unary_expr<LHS2, OP2> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_unary_expr<LHS2, OP2> >(); 
  }
  
  template <id_type id1,
            long value2>
  ct_interval<ct_variable<id1>,
              ct_constant<value2> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_constant<value2> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_constant<value2> >(); 
  }

  template <id_type id1,
            typename TAG>
  ct_interval<ct_variable<id1>,
              ct_function_symbol<TAG> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_function_symbol<TAG> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_function_symbol<TAG> >(); 
  }


  template <id_type id1,
            id_type id2>
  ct_interval<ct_variable<id1>,
              ct_variable<id2> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_variable<id2> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_variable<id2> >(); 
  }
  
}

#endif