#ifndef VIENNAMATH_MANIPULATION_EXPAND_HPP
#define VIENNAMATH_MANIPULATION_EXPAND_HPP

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
#include "viennamath/compiletime/unary_op_tags.hpp"
#include "viennamath/runtime/interval.hpp"
#include "viennamath/runtime/symbolic_interval.hpp"
#include "viennamath/runtime/integral.hpp"

namespace viennamath
{
  //////////// compile time ///////////////////
  
  namespace result_of
  {
    // interfacing metafunction
    template <typename T>
    struct expand {}; //Uses SFINAE for proper overloading of viennamath::expand()
    
    
    namespace detail
    {
      // checks for the occurance of plus or minus in an expression
      template <typename T>
      struct has_plus_or_minus 
      {
        enum { value = 0 };
      };
      
      template <typename LHS, typename NumericT, typename RHS>
      struct has_plus_or_minus< ct_binary_expr<LHS, op_plus<NumericT>, RHS> >
      {
        enum { value = 1 };
      };

      template <typename LHS, typename NumericT, typename RHS>
      struct has_plus_or_minus< ct_binary_expr<LHS, op_minus<NumericT>, RHS> >
      {
        enum { value = 1 };
      };

      template <typename LHS, typename NumericT, typename RHS>
      struct has_plus_or_minus< ct_binary_expr<LHS, op_mult<NumericT>, RHS> >
      {
        enum { value = has_plus_or_minus<LHS>::value + has_plus_or_minus<RHS>::value };
      };

      template <typename LHS, typename NumericT, typename RHS>
      struct has_plus_or_minus< ct_binary_expr<LHS, op_div<NumericT>, RHS> >
      {
        enum { value = has_plus_or_minus<LHS>::value};
      };
      
      
      //
      template <typename ExpressionType,
                typename FactorType,
                bool needs_expansion = (has_plus_or_minus<ExpressionType>::value != 0) >
      struct expand_with_factor
      {
        typedef ct_binary_expr< ExpressionType,
                                op_mult<default_numeric_type>,
                                FactorType
                                >                 type;
      };
      
      template <typename LHS, typename NumericT, typename RHS,
                typename FactorType>
      struct expand_with_factor < ct_binary_expr<LHS, op_plus<NumericT>, RHS>,
                                  FactorType,
                                  true>
      {
        typedef ct_binary_expr< typename expand_with_factor<LHS, FactorType>::type,
                                op_plus<NumericT>,
                                typename expand_with_factor<RHS, FactorType>::type
                              >                   type;
      };
      
      
      template <typename LHS, typename NumericT, typename RHS,
                typename FactorType>
      struct expand_with_factor < ct_binary_expr<LHS, op_minus<NumericT>, RHS>,
                                  FactorType,
                                  true>
      {
        typedef ct_binary_expr< typename expand_with_factor<LHS, FactorType>::type,
                                op_minus<NumericT>,
                                typename expand_with_factor<RHS, FactorType>::type
                              >                   type;
      };

      template <typename LHS, typename NumericT, typename RHS,
                typename FactorType>
      struct expand_with_factor < ct_binary_expr<LHS, op_mult<NumericT>, RHS>,
                                  FactorType,
                                  true>
      {
        typedef typename viennamath::result_of::expand< ct_binary_expr<LHS, op_mult<NumericT>, RHS> >::type     expanded_type;
        typedef typename expand_with_factor< expanded_type, FactorType >::type         type;
      };
      
      template <typename LHS, typename NumericT, typename RHS,
                typename FactorType>
      struct expand_with_factor < ct_binary_expr<LHS, op_div<NumericT>, RHS>,
                                  FactorType,
                                  true>
      {
        typedef ct_binary_expr< typename expand_with_factor<LHS, FactorType>::type,
                                op_div<NumericT>,
                                RHS
                              >                   type;
      };
      
      template <typename LHS,
                typename RHS,
                bool lhs_expandable = (has_plus_or_minus<LHS>::value != 0),
                bool rhs_expandable = (has_plus_or_minus<RHS>::value != 0)>
      struct expand_product
      {
         //default case: both factors not expandable:
         typedef ct_binary_expr<LHS,
                                op_mult<default_numeric_type>,
                                RHS >     type;
      };
      
      template <typename LHS,
                typename RHS>
      struct expand_product <LHS, RHS, true, false>
      {
         typedef typename expand_with_factor<LHS, RHS>::type   type;
      };

      template <typename LHS,
                typename RHS>
      struct expand_product <LHS, RHS, false, true>
      {
         typedef typename expand_with_factor<RHS, LHS>::type   type;
      };

      template <typename LHS,
                typename RHS>
      struct expand_product <LHS, RHS, true, true>
      {
         //First expand with factor RHS:
         typedef typename expand_with_factor<LHS, RHS>::type   intermediate_type;
         //then restart:
         typedef typename viennamath::result_of::expand<intermediate_type>::type      type;
      };
      
    }
    
    
    template <typename LHS, typename NumericT, typename RHS>
    struct expand< ct_binary_expr<LHS, op_plus<NumericT>, RHS> >
    {
      typedef ct_binary_expr<typename expand<LHS>::type,
                             op_plus<NumericT>,
                             typename expand<RHS>::type >     type;
    };

    template <typename LHS, typename NumericT, typename RHS>
    struct expand< ct_binary_expr<LHS, op_minus<NumericT>, RHS> >
    {
      typedef ct_binary_expr<typename expand<LHS>::type,
                             op_minus<NumericT>,
                             typename expand<RHS>::type >     type;
    };

    template <typename LHS, typename NumericT, typename RHS>
    struct expand< ct_binary_expr<LHS, op_mult<NumericT>, RHS> >
    {
      typedef typename detail::expand_product<LHS, RHS>::type    type;
    };

    // expand numerator and denominator of fractional expressions separately:
    template <typename LHS, typename NumericT, typename RHS>
    struct expand< ct_binary_expr<LHS, op_div<NumericT>, RHS> >
    {
      typedef ct_binary_expr<typename expand<LHS>::type,
                             op_div<NumericT>,
                             typename expand<RHS>::type >     type;
    };

    template <typename LHS, typename OP>
    struct expand< ct_unary_expr<LHS, OP> >
    {
      typedef ct_unary_expr<LHS, OP>      type;
    };
    
    template <typename TAG>
    struct expand< ct_function_symbol<TAG> >
    {
      typedef ct_function_symbol<TAG>      type;
    };

    template <long value>
    struct expand< ct_constant<value> >
    {
      typedef ct_constant<value>      type;
    };

    template <id_type id>
    struct expand< ct_variable<id> >
    {
      typedef ct_variable<id>      type;
    };
    
    
  }
  
  template <typename ExpressionType>
  typename result_of::expand<ExpressionType>::type
  expand(ExpressionType const & type)
  {
    return typename result_of::expand<ExpressionType>::type();
  }
  
  
  //////////// run time ////////////////
  
  //TODO
}

#endif
