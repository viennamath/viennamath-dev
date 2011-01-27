/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_DIFF_HPP
#define VIENNAMATH_DIFF_HPP

#include "viennamath/forwards.h"
#include "viennamath/binary_expression_operations.hpp"
#include "viennamath/unary_expression.hpp"

namespace viennamath
{
  
  //////////// derivative of a constant: /////////////////////////////////

  template <unsigned long id>
  constant<numeric_type> diff(numeric_type value,
                              variable<id> const & var)
  {
    return constant<numeric_type>(0);
  }
  
  template <typename OtherScalarType,
            unsigned long id>
  constant<numeric_type> diff(constant<OtherScalarType> const & c,
                              variable<id> const & var)
  {
    return constant<numeric_type>(0);
  }

  //////////// derivative of an variable: /////////////////////////////////

  template <unsigned long other_id,
            unsigned long id>
  constant<numeric_type> diff(variable<other_id> const & c,
                              variable<id> const & var)
  {
    return constant<numeric_type>(0);
  }

  template <unsigned long id>
  constant<numeric_type> diff(variable<id> const & c,
                              variable<id> const & var)
  {
    return constant<numeric_type>(1);
  }

  /////////////////// derivative of runtime expression /////////////////////

  template <unsigned long id>
  unary_expr diff(binary_expr const & e,
                  variable<id> const & var)
  {
    //generic approach: use operator() and hope the best:
    return unary_expr(e.diff(var));
  }
  




  /////////////////// derivative of compiletime expression /////////////////////
  
  //metafunctions
  
  //differentiates ARG with respect to VAR
  template <typename ARG, typename VAR>
  struct ct_diff
  {
    typedef typename ARG::ERROR_INVALID_ARGUMENT_PROVIDED_TO_COMPILE_TIME_DIFFERENTIATION  error_type; 
  };
  
  // (u + v)' = u' + v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<expression<LHS, op_plus, RHS>,
                 variable<id> >
  {
    typedef expression< typename ct_diff<LHS, variable<id> >::result_type,
                        op_plus,
                        typename ct_diff<RHS, variable<id> >::result_type >     result_type;    
  };
  
  // (u - v)' = u' - v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<expression<LHS, op_minus, RHS>,
                 variable<id> >
  {
    typedef expression< typename ct_diff<LHS, variable<id> >::result_type,
                        op_minus,
                        typename ct_diff<RHS, variable<id> >::result_type >     result_type;    
  };
  
  // (u * v)' = u'*v + u*v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<expression<LHS, op_mult, RHS>,
                 variable<id> >
  {
    typedef expression< expression< typename ct_diff<LHS, variable<id> >::result_type,
                                    op_mult,
                                    RHS>,
                        op_plus,            
                        expression< LHS,
                                    op_mult,
                                    typename ct_diff<RHS, variable<id> >::result_type >
                      >                                                      result_type;    
  };

  // (u/v)' = (u'*v - u*v') / v^2
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<expression<LHS, op_div, RHS>,
                 variable<id> >
  {
    typedef expression< expression< expression< typename ct_diff<LHS, variable<id> >::result_type,
                                                op_mult,
                                                RHS>,
                                    op_minus,            
                                    expression< LHS,
                                                op_mult,
                                                typename ct_diff<RHS, variable<id> >::result_type >
                                   >,
                      op_div,             
                      expression< RHS,
                                  op_mult,
                                  RHS >
                      >                    result_type;    
  };
  
  template <unsigned long other_id,
            unsigned long id>
  struct ct_diff< variable<other_id>,
                  variable<id> >
  {
    typedef ct_constant<0>    result_type;    
  };
  
  template <unsigned long id>
  struct ct_diff< variable<id>,
                  variable<id> >
  {
    typedef ct_constant<1>    result_type;    
  };
  
  template <long value, unsigned long id>
  struct ct_diff< ct_constant<value>,
                  variable<id> >
  {
    typedef ct_constant<0>    result_type;    
  };
  
  
  
  //interface function
  template <typename LHS, typename OP, typename RHS,
            unsigned long id>
  typename ct_diff<expression<LHS, OP, RHS>,
                   variable<id> >::result_type
  diff(expression<LHS, OP, RHS> const & c,
       variable<id> const & var)
  {
    return typename ct_diff<expression<LHS, OP, RHS>,
                            variable<id> >::result_type();
  }
}

#endif