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
#include "viennamath/runtime/unary_expression.hpp"

namespace viennamath
{
  
  /////////////////// derivative of runtime expression /////////////////////

  template <typename InterfaceType>
  expr<InterfaceType> diff(binary_expr<InterfaceType> const & e,
                           variable<InterfaceType> const & var)
  {
    expr<InterfaceType> temp(e.diff(&var));
    while (temp.get()->optimizable())
    {
      //std::cout << "optimizing binary_expr..." << std::endl;
      temp = temp.get()->optimize();
    }
    return temp;
  }
  
  template <typename InterfaceType>
  expr<InterfaceType> diff(unary_expr<InterfaceType> const & e,
                           variable<InterfaceType> const & var)
  {
    expr<InterfaceType> temp(e.diff(&var));
    while (temp.get()->optimizable())
    {
      //std::cout << "optimizing unary_expr..." << std::endl;
      temp = temp.get()->optimize();
    }
    return temp;
  }

  template <typename InterfaceType>
  expr<InterfaceType> diff(expr<InterfaceType> const & e,
                           variable<InterfaceType> const & var)
  {
    expr<InterfaceType> temp(e.get()->diff(&var));
    while (temp.get()->optimizable())
    {
      //std::cout << "optimizing expr:" << temp << std::endl;      
      temp = temp.get()->optimize();
    }
    return temp;
  }

  //compile time variable:
  template <typename InterfaceType, id_type id>
  expr<InterfaceType> diff(binary_expr<InterfaceType> const & e,
                           ct_variable<id> const & var)
  {
    variable<InterfaceType> temp(id);
    return diff(e, temp);
  }

  template <typename InterfaceType, id_type id>
  expr<InterfaceType> diff(unary_expr<InterfaceType> const & e,
                           ct_variable<id> const & var)
  {
    variable<InterfaceType> temp(id);
    return diff(e, temp);
  }

  template <typename InterfaceType, id_type id>
  expr<InterfaceType> diff(expr<InterfaceType> const & e,
                           ct_variable<id> const & var)
  {
    variable<InterfaceType> temp(id);
    return diff(e, temp);
  }

  
  //
  // Symbolic differentiation:
  // TODO: Improve for compile time compatibility
  //
  template <typename Tag,
            typename InterfaceType>
  expr<InterfaceType> diff(function_symbol<Tag, InterfaceType> const & other,
                           variable<InterfaceType> const & var)
  {
    return expr<InterfaceType>(new unary_expr<InterfaceType>(other.clone(), 
                                                             new op_unary<op_partial_deriv<typename InterfaceType::numeric_type>, InterfaceType >()
                                                            )
                              );
  }
  



  /////////////////// derivative of compiletime expression /////////////////////
  
  //////////// derivative of a constant: /////////////////////////////////

  template <typename InterfaceType>
  constant<typename InterfaceType::numeric_type> diff(typename InterfaceType::numeric_type value,
                                                      variable<InterfaceType> const & var)
  {
    return constant<typename InterfaceType::numeric_type>(0);
  }
  
  template <typename OtherScalarType, typename InterfaceType>
  constant<typename InterfaceType::numeric_type> diff(constant<OtherScalarType, InterfaceType> const & c,
                                                      variable<InterfaceType> const & var)
  {
    return constant<typename InterfaceType::numeric_type>(0);
  }

  //////////// derivative of an variable: /////////////////////////////////

  template <unsigned long other_id, typename InterfaceType,
            unsigned long id>
  constant<typename InterfaceType::numeric_type> diff(variable<InterfaceType> const & c,
                                                      variable<InterfaceType> const & var)
  {
    if (c.id() == var.id())
      return constant<typename InterfaceType::numeric_type>(1);
      
    return constant<typename InterfaceType::numeric_type>(0);
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
  struct ct_diff<ct_expr<LHS, op_plus<default_numeric_type>, RHS>,
                 ct_variable<id> >
  {
    typedef ct_expr< typename ct_diff<LHS, ct_variable<id> >::result_type,
                     op_plus<default_numeric_type>,
                        typename ct_diff<RHS, ct_variable<id> >::result_type >     result_type;    
  };
  
  // (u - v)' = u' - v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<ct_expr<LHS, op_minus<default_numeric_type>, RHS>,
                 ct_variable<id> >
  {
    typedef ct_expr< typename ct_diff<LHS, ct_variable<id> >::result_type,
                        op_minus<default_numeric_type>,
                        typename ct_diff<RHS, ct_variable<id> >::result_type >     result_type;    
  };
  
  // (u * v)' = u'*v + u*v'
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<ct_expr<LHS, op_mult<default_numeric_type>, RHS>,
                 ct_variable<id> >
  {
    typedef ct_expr< ct_expr< typename ct_diff<LHS, ct_variable<id> >::result_type,
                                    op_mult<default_numeric_type>,
                                    RHS>,
                        op_plus<default_numeric_type>,            
                        ct_expr< LHS,
                                    op_mult<default_numeric_type>,
                                    typename ct_diff<RHS, ct_variable<id> >::result_type >
                      >                                                      result_type;    
  };

  // (u/v)' = (u'*v - u*v') / v^2
  template <typename LHS, typename RHS, unsigned long id>
  struct ct_diff<ct_expr<LHS, op_div<default_numeric_type>, RHS>,
                 ct_variable<id> >
  {
    typedef ct_expr< ct_expr< ct_expr< typename ct_diff<LHS, ct_variable<id> >::result_type,
                                                op_mult<default_numeric_type>,
                                                RHS>,
                                    op_minus<default_numeric_type>,            
                                    ct_expr< LHS,
                                                op_mult<default_numeric_type>,
                                                typename ct_diff<RHS, ct_variable<id> >::result_type >
                                   >,
                      op_div<default_numeric_type>,             
                      ct_expr< RHS,
                               op_mult<default_numeric_type>,
                               RHS >
                      >                    result_type;    
  };
  
  template <unsigned long other_id,
            unsigned long id>
  struct ct_diff< ct_variable<other_id>,
                  ct_variable<id> >
  {
    typedef ct_constant<0>    result_type;    
  };
  
  template <unsigned long id>
  struct ct_diff< ct_variable<id>,
                  ct_variable<id> >
  {
    typedef ct_constant<1>    result_type;    
  };
  
  template <long value, unsigned long id>
  struct ct_diff< ct_constant<value>,
                  ct_variable<id> >
  {
    typedef ct_constant<0>    result_type;    
  };
  
  
  
  //interface function
  template <typename LHS, typename OP, typename RHS,
            unsigned long id>
  typename ct_diff<ct_expr<LHS, OP, RHS>,
                   ct_variable<id> >::result_type
  diff(ct_expr<LHS, OP, RHS> const & c,
       ct_variable<id> const & var)
  {
    return typename ct_diff<ct_expr<LHS, OP, RHS>,
                            ct_variable<id> >::result_type();
  }
  
  
  
}

#endif