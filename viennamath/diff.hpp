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

  template <typename ScalarType, unsigned long id>
  constant<numeric_type> diff(numeric_type value,
                              unknown<ScalarType, id> const & var)
  {
    return constant<numeric_type>(0);
  }
  
  template <typename OtherScalarType,
            typename ScalarType, unsigned long id>
  constant<numeric_type> diff(constant<OtherScalarType> const & c,
                              unknown<ScalarType, id> const & var)
  {
    return constant<numeric_type>(0);
  }

  //////////// derivative of an unknown: /////////////////////////////////

  template <typename OtherScalarType, unsigned long other_id,
            typename ScalarType, unsigned long id>
  constant<numeric_type> diff(unknown<OtherScalarType, other_id> const & c,
                              unknown<ScalarType, id> const & var)
  {
    return constant<numeric_type>(0);
  }

  template <long other_id,
            typename ScalarType, unsigned long id>
  constant<numeric_type> diff(unknown<ScalarType, other_id> const & c,
                              unknown<ScalarType, id> const & var)
  {
    return constant<numeric_type>(0);
  }

  template <typename OtherScalarType,
            typename ScalarType, unsigned long id>
  constant<numeric_type> diff(unknown<OtherScalarType, id> const & c,
                              unknown<ScalarType, id> const & var)
  {
    return constant<numeric_type>(1);
  }

  template <typename ScalarType, unsigned long id>
  constant<numeric_type> diff(unknown<ScalarType, id> const & c,
                              unknown<ScalarType, id> const & var)
  {
    return constant<numeric_type>(1);
  }

  /////////////////// derivative of runtime expression /////////////////////

  template <typename ScalarType, unsigned long id>
  unary_expr diff(binary_expr const & e,
                   unknown<ScalarType, id> const & var)
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
  template <typename LHS, typename RHS, typename ScalarType, unsigned long id>
  struct ct_diff<expression<LHS, op_plus, RHS>,
                 unknown<ScalarType, id> >
  {
    typedef expression< typename ct_diff<LHS, unknown<ScalarType, id> >::result_type,
                        op_plus,
                        typename ct_diff<RHS, unknown<ScalarType, id> >::result_type >     result_type;    
  };
  
  // (u - v)' = u' - v'
  template <typename LHS, typename RHS, typename ScalarType, unsigned long id>
  struct ct_diff<expression<LHS, op_minus, RHS>,
                 unknown<ScalarType, id> >
  {
    typedef expression< typename ct_diff<LHS, unknown<ScalarType, id> >::result_type,
                        op_minus,
                        typename ct_diff<RHS, unknown<ScalarType, id> >::result_type >     result_type;    
  };
  
  // (u * v)' = u'*v + u*v'
  template <typename LHS, typename RHS, typename ScalarType, unsigned long id>
  struct ct_diff<expression<LHS, op_mult, RHS>,
                 unknown<ScalarType, id> >
  {
    typedef expression< expression< typename ct_diff<LHS, unknown<ScalarType, id> >::result_type,
                                    op_mult,
                                    RHS>,
                        op_plus,            
                        expression< LHS,
                                    op_mult,
                                    typename ct_diff<RHS, unknown<ScalarType, id> >::result_type >
                      >                                                      result_type;    
  };

  // (u/v)' = (u'*v - u*v') / v^2
  template <typename LHS, typename RHS, typename ScalarType, unsigned long id>
  struct ct_diff<expression<LHS, op_div, RHS>,
                 unknown<ScalarType, id> >
  {
    typedef expression< expression< expression< typename ct_diff<LHS, unknown<ScalarType, id> >::result_type,
                                                op_mult,
                                                RHS>,
                                    op_minus,            
                                    expression< LHS,
                                                op_mult,
                                                typename ct_diff<RHS, unknown<ScalarType, id> >::result_type >
                                   >,
                      op_div,             
                      expression< RHS,
                                  op_mult,
                                  RHS >
                      >                    result_type;    
  };
  
  template <typename OtherScalarType, unsigned long other_id,
            typename ScalarType, unsigned long id>
  struct ct_diff< unknown<OtherScalarType, other_id>,
                  unknown<ScalarType, id> >
  {
    typedef ct_constant<0>    result_type;    
  };

  template <unsigned long other_id,
            typename ScalarType, unsigned long id>
  struct ct_diff< unknown<ScalarType, other_id>,
                  unknown<ScalarType, id> >
  {
    typedef ct_constant<0>    result_type;    
  };
  
  template <typename OtherScalarType,
            typename ScalarType, unsigned long id>
  struct ct_diff< unknown<OtherScalarType, id>,
                  unknown<ScalarType, id> >
  {
    typedef ct_constant<1>    result_type;    
  };
  
  template <typename ScalarType, unsigned long id>
  struct ct_diff< unknown<ScalarType, id>,
                  unknown<ScalarType, id> >
  {
    typedef ct_constant<1>    result_type;    
  };
  
  template <long value, typename ScalarType, unsigned long id>
  struct ct_diff< ct_constant<value>,
                  unknown<ScalarType, id> >
  {
    typedef ct_constant<0>    result_type;    
  };
  
  
  
  //interface function
  template <typename LHS, typename OP, typename RHS,
            typename ScalarType, unsigned long id>
  typename ct_diff<expression<LHS, OP, RHS>,
                   unknown<ScalarType, id> >::result_type
  diff(expression<LHS, OP, RHS> const & c,
       unknown<ScalarType, id> const & var)
  {
    return typename ct_diff<expression<LHS, OP, RHS>,
                            unknown<ScalarType, id> >::result_type();
  }
}

#endif