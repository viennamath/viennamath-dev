#ifndef VIENNAMATH_MANIPULATION_DIFF_HPP
#define VIENNAMATH_MANIPULATION_DIFF_HPP

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




#include "viennamath/forwards.h"
#include "viennamath/runtime/unary_expression.hpp"

namespace viennamath
{
  
  /////////////////// Derivative of runtime expression /////////////////////

  template <typename InterfaceType>
  rt_expr<InterfaceType> diff(rt_binary_expr<InterfaceType> const & e,
                           rt_variable<InterfaceType> const & var)
  {
    rt_expr<InterfaceType> temp(e.diff(&var));
    while (temp.get()->optimizable())
    {
      //std::cout << "optimizing binary_expr..." << std::endl;
      temp = temp.get()->optimize();
    }
    return temp;
  }
  
  template <typename InterfaceType>
  rt_expr<InterfaceType> diff(rt_unary_expr<InterfaceType> const & e,
                           rt_variable<InterfaceType> const & var)
  {
    rt_expr<InterfaceType> temp(e.diff(&var));
    while (temp.get()->optimizable())
    {
      //std::cout << "optimizing unary_expr..." << std::endl;
      temp = temp.get()->optimize();
    }
    return temp;
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> diff(rt_expr<InterfaceType> const & e,
                           rt_variable<InterfaceType> const & var)
  {
    rt_expr<InterfaceType> temp(e.get()->diff(&var));
    while (temp.get()->optimizable())
    {
      //std::cout << "optimizing expr:" << temp << std::endl;      
      temp = temp.get()->optimize();
    }
    return temp;
  }

  //compile time variable:
  template <typename InterfaceType, id_type id>
  rt_expr<InterfaceType> diff(rt_binary_expr<InterfaceType> const & e,
                           ct_variable<id> const & var)
  {
    rt_variable<InterfaceType> temp(id);
    return diff(e, temp);
  }

  template <typename InterfaceType, id_type id>
  rt_expr<InterfaceType> diff(rt_unary_expr<InterfaceType> const & e,
                           ct_variable<id> const & var)
  {
    rt_variable<InterfaceType> temp(id);
    return diff(e, temp);
  }

  template <typename InterfaceType, id_type id>
  rt_expr<InterfaceType> diff(rt_expr<InterfaceType> const & e,
                           ct_variable<id> const & var)
  {
    rt_variable<InterfaceType> temp(id);
    return diff(e, temp);
  }

  
  //
  // Symbolic differentiation:
  // TODO: Improve for compile time compatibility
  //
  template <typename InterfaceType>
  rt_expr<InterfaceType> diff(rt_function_symbol<InterfaceType> const & other,
                           rt_variable<InterfaceType> const & var)
  {
    typedef op_partial_deriv<typename InterfaceType::numeric_type> d_dx_type;
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(other.clone(), 
                                                                   new op_unary<d_dx_type, InterfaceType>(d_dx_type(var.id()))
                                                                  )
                                 );
  }
  


  //
  /////////////////// Derivative of compiletime expressions /////////////////////
  //
  
  //////////// Derivative of a constant: /////////////////////////////////

  template <typename InterfaceType>
  rt_constant<typename InterfaceType::numeric_type> diff(typename InterfaceType::numeric_type value,
                                                         rt_variable<InterfaceType> const & var)
  {
    return rt_constant<typename InterfaceType::numeric_type>(0);
  }
  
  template <typename OtherScalarType, typename InterfaceType>
  rt_constant<typename InterfaceType::numeric_type> diff(rt_constant<OtherScalarType, InterfaceType> const & c,
                                                         rt_variable<InterfaceType> const & var)
  {
    return rt_constant<typename InterfaceType::numeric_type>(0);
  }

  //////////// derivative of an variable: /////////////////////////////////

  template <id_type other_id, typename InterfaceType,
            id_type id>
  rt_constant<typename InterfaceType::numeric_type> diff(rt_variable<InterfaceType> const & c,
                                                         rt_variable<InterfaceType> const & var)
  {
    if (c.id() == var.id())
      return rt_constant<typename InterfaceType::numeric_type>(1);
      
    return rt_constant<typename InterfaceType::numeric_type>(0);
  }
  
  //metafunctions
  namespace result_of
  {
    //differentiates ARG with respect to VAR
    template <typename ARG, typename VAR>
    struct diff {}; //default case: used for SFINAE with respect to the viennamath::diff() function
    //{
    //  typedef typename ARG::ERROR_INVALID_ARGUMENT_PROVIDED_TO_COMPILE_TIME_DIFFERENTIATION  error_type; 
    //};
    
    // (u + v)' = u' + v'
    template <typename LHS, typename RHS, id_type id>
    struct diff<ct_binary_expr<LHS, op_plus<default_numeric_type>, RHS>,
                ct_variable<id> >
    {
      typedef ct_binary_expr< typename diff<LHS, ct_variable<id> >::result_type,
                              op_plus<default_numeric_type>,
                              typename diff<RHS, ct_variable<id> >::result_type >     result_type;    
    };
    
    // (u - v)' = u' - v'
    template <typename LHS, typename RHS, id_type id>
    struct diff<ct_binary_expr<LHS, op_minus<default_numeric_type>, RHS>,
                ct_variable<id> >
    {
      typedef ct_binary_expr< typename diff<LHS, ct_variable<id> >::result_type,
                              op_minus<default_numeric_type>,
                              typename diff<RHS, ct_variable<id> >::result_type >     result_type;    
    };
    
    // (u * v)' = u'*v + u*v'
    template <typename LHS, typename RHS, id_type id>
    struct diff<ct_binary_expr<LHS, op_mult<default_numeric_type>, RHS>,
                ct_variable<id> >
    {
      typedef ct_binary_expr< ct_binary_expr< typename diff<LHS, ct_variable<id> >::result_type,
                                              op_mult<default_numeric_type>,
                                              RHS>,
                              op_plus<default_numeric_type>,            
                              ct_binary_expr< LHS,
                                              op_mult<default_numeric_type>,
                                              typename diff<RHS, ct_variable<id> >::result_type >
                            >                                                      result_type;    
    };

    // (u/v)' = (u'*v - u*v') / v^2
    template <typename LHS, typename RHS, id_type id>
    struct diff<ct_binary_expr<LHS, op_div<default_numeric_type>, RHS>,
                ct_variable<id> >
    {
      typedef ct_binary_expr< ct_binary_expr< ct_binary_expr< typename diff<LHS, ct_variable<id> >::result_type,
                                                              op_mult<default_numeric_type>,
                                                              RHS>,
                                              op_minus<default_numeric_type>,            
                                              ct_binary_expr< LHS,
                                                              op_mult<default_numeric_type>,
                                                              typename diff<RHS, ct_variable<id> >::result_type >
                                            >,
                              op_div<default_numeric_type>,             
                              ct_binary_expr< RHS,
                                              op_mult<default_numeric_type>,
                                              RHS >
                            >                 result_type;    
    };
    
    template <id_type other_id,
              id_type id>
    struct diff< ct_variable<other_id>,
                 ct_variable<id> >
    {
      typedef ct_constant<0>    result_type;    
    };
    
    template <id_type id>
    struct diff< ct_variable<id>,
                 ct_variable<id> >
    {
      typedef ct_constant<1>    result_type;    
    };
    
    template <long value, id_type id>
    struct diff< ct_constant<value>,
                 ct_variable<id> >
    {
      typedef ct_constant<0>    result_type;    
    };
    
  } // namespace result_of
  
  
  //
  // interface functions
  //
  template <typename ExpressionType,
            id_type id>
  typename result_of::diff<ExpressionType,
                           ct_variable<id> >::result_type
  diff(ExpressionType const & c,
       ct_variable<id> const & var)
  {
    return typename result_of::diff<ExpressionType,
                                    ct_variable<id> >::result_type();
  }
  
  
  
}

#endif