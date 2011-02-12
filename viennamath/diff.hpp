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
#include "viennamath/unary_expression.hpp"

namespace viennamath
{
  
  /////////////////// derivative of runtime expression /////////////////////

  template <unsigned long id>
  expr diff(binary_expr const & e,
            variable<id> const & var)
  {
    expr temp(e.diff(var));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    return temp;
  }
  
  template <unsigned long id>
  expr diff(unary_expr const & e,
            variable<id> const & var)
  {
    expr temp(e.diff(var));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    return temp;
  }

  template <unsigned long id>
  expr diff(expr const & e,
            variable<id> const & var)
  {
    expr temp(e.get()->diff(var));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    return temp;
  }

  
  
  //
  // Symbolic differentiation:
  // TODO: Improve for compile time compatibility
  //
  template <typename Tag,
            unsigned long id_variable>
  expr diff(function_symbol<Tag> const & other,
            variable<id_variable> const & var)
  {
    return expr(new unary_expr(other.clone(), 
                               new op_unary<op_partial_deriv<id_variable> >()
                              )
               );
  }
  



  /////////////////// derivative of compiletime expression /////////////////////
  
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

  
  //metafunctions
  
  //differentiates ARG with respect to VAR
  template <typename ARG, typename VAR>
  struct ct_diff
  {
    typedef typename ARG::ERROR_INVALID_ARGUMENT_PROVIDED_TO_COMPILE_TIME_DIFFERENTIATION  error_type; 
  };
  
  // (u + v)' = u' + v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<ct_expr<LHS, op_plus, RHS>,
                 variable<id> >
  {
    typedef ct_expr< typename ct_diff<LHS, variable<id> >::result_type,
                        op_plus,
                        typename ct_diff<RHS, variable<id> >::result_type >     result_type;    
  };
  
  // (u - v)' = u' - v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<ct_expr<LHS, op_minus, RHS>,
                 variable<id> >
  {
    typedef ct_expr< typename ct_diff<LHS, variable<id> >::result_type,
                        op_minus,
                        typename ct_diff<RHS, variable<id> >::result_type >     result_type;    
  };
  
  // (u * v)' = u'*v + u*v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<ct_expr<LHS, op_mult, RHS>,
                 variable<id> >
  {
    typedef ct_expr< ct_expr< typename ct_diff<LHS, variable<id> >::result_type,
                                    op_mult,
                                    RHS>,
                        op_plus,            
                        ct_expr< LHS,
                                    op_mult,
                                    typename ct_diff<RHS, variable<id> >::result_type >
                      >                                                      result_type;    
  };

  // (u/v)' = (u'*v - u*v') / v^2
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<ct_expr<LHS, op_div, RHS>,
                 variable<id> >
  {
    typedef ct_expr< ct_expr< ct_expr< typename ct_diff<LHS, variable<id> >::result_type,
                                                op_mult,
                                                RHS>,
                                    op_minus,            
                                    ct_expr< LHS,
                                                op_mult,
                                                typename ct_diff<RHS, variable<id> >::result_type >
                                   >,
                      op_div,             
                      ct_expr< RHS,
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
  typename ct_diff<ct_expr<LHS, OP, RHS>,
                   variable<id> >::result_type
  diff(ct_expr<LHS, OP, RHS> const & c,
       variable<id> const & var)
  {
    return typename ct_diff<ct_expr<LHS, OP, RHS>,
                            variable<id> >::result_type();
  }
  
  
  
}

#endif