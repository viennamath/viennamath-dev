/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_COEFFICIENT_HPP
#define VIENNAMATH_COEFFICIENT_HPP

#include "viennamath/forwards.h"
#include "viennamath/manipulation/expand.hpp"

namespace viennamath
{
  ///////////////// compile time ////////////////////////////
  namespace result_of
  {
    // forward declaration
    template <typename FactorType,
              typename ExpressionType>
    struct coefficient_impl;

    
    
    //
    // Helper metafunction: Returns the number of factors FactorType found in ExpressionType
    template <typename FactorType,
              typename ExpressionType>
    struct has_factor
    {
      enum { value = 0 };
    };
    
    template <typename FactorType>
    struct has_factor<FactorType, FactorType>
    {
      enum { value = 1 };
    };

    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct has_factor< FactorType, ct_binary_expr<LHS, op_plus<NumericT>, RHS> >
    {
      typedef typename ct_binary_expr<LHS, op_plus<NumericT>, RHS>::ERROR_EXPRESSION_NOT_FULLY_EXPANDED    error_type;
      enum { value = 0 };
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct has_factor< FactorType, ct_binary_expr<LHS, op_minus<NumericT>, RHS> >
    {
      typedef typename ct_binary_expr<LHS, op_minus<NumericT>, RHS>::ERROR_EXPRESSION_NOT_FULLY_EXPANDED    error_type;
      enum { value = 0 };
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct has_factor< FactorType, ct_binary_expr<LHS, op_mult<NumericT>, RHS> >
    {
      enum { value = has_factor<FactorType, LHS>::value + has_factor<FactorType, RHS>::value };
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct has_factor< FactorType, ct_binary_expr<LHS, op_div<NumericT>, RHS> >
    {
      enum { value = has_factor<FactorType, LHS>::value };
    };
    
    
    //
    // Extracts the factor from an expression free of plus and minus operations
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS,
              bool lhs_has_factor = (has_factor<FactorType, LHS>::value != 0),
              bool rhs_has_factor = (has_factor<FactorType, RHS>::value != 0)
              >
    struct extract_factor_from_product
    {
      // default case: neither LHS nor RHS have the factor
      typedef ct_constant<0>     type;
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct extract_factor_from_product<FactorType, LHS, NumericT, RHS, true, false>
    {
      // get the factor from LHS:
      typedef ct_binary_expr< typename coefficient_impl<FactorType, LHS>::type,
                              op_mult<NumericT>,
                              RHS
                            >                    type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct extract_factor_from_product<FactorType, LHS, NumericT, RHS, false, true>
    {
      // get the factor from RHS:
      typedef ct_binary_expr< LHS,
                              op_mult<NumericT>,
                              typename coefficient_impl<FactorType, RHS>::type
                            >                    type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct extract_factor_from_product<FactorType, LHS, NumericT, RHS, true, true>
    {
      // if both LHS and RHS contain the factor, we extract the coefficient from the LHS and multiply with RHS
      typedef ct_binary_expr< typename coefficient_impl<FactorType, LHS>::type,
                              op_mult<NumericT>,
                              RHS
                            >                    type;
    };
    

    //
    // Tokenizer: Extracts the factor from each token
    template <typename FactorType,
              typename ExpressionType>
    struct coefficient_impl
    {
      typedef ct_constant<0>   type;
    };

    template <typename FactorType>
    struct coefficient_impl<FactorType, FactorType>
    {
      typedef ct_constant<1>    type;
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct coefficient_impl< FactorType, ct_binary_expr<LHS, op_plus<NumericT>, RHS> >
    {
      typedef ct_binary_expr< typename coefficient_impl<FactorType, LHS>::type,
                              op_plus<NumericT>,
                              typename coefficient_impl<FactorType, RHS>::type
                            >   type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct coefficient_impl< FactorType, ct_binary_expr<LHS, op_minus<NumericT>, RHS> >
    {
      typedef ct_binary_expr< typename coefficient_impl<FactorType, LHS>::type,
                              op_minus<NumericT>,
                              typename coefficient_impl<FactorType, RHS>::type
                            >   type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct coefficient_impl< FactorType, ct_binary_expr<LHS, op_mult<NumericT>, RHS> >
    {
      typedef typename extract_factor_from_product<FactorType, LHS, NumericT, RHS>::type    type;
    };

    template <typename FactorType,
              typename NumericT, typename RHS>
    struct coefficient_impl< FactorType, ct_binary_expr<FactorType, op_mult<NumericT>, RHS> >
    {
      typedef RHS    type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT>
    struct coefficient_impl< FactorType, ct_binary_expr<LHS, op_mult<NumericT>, FactorType> >
    {
      typedef LHS    type;
    };

    template <typename FactorType,
              typename NumericT>
    struct coefficient_impl< FactorType, ct_binary_expr<FactorType, op_mult<NumericT>, FactorType> >
    {
      typedef FactorType    type;
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct coefficient_impl< FactorType, ct_binary_expr<LHS, op_div<NumericT>, RHS> >
    {
      typedef ct_binary_expr< typename coefficient_impl<FactorType, LHS>::type,
                              op_div<NumericT>,
                              RHS
                            >   type;
    };
    
    
    
    //
    // Interface metafunction:
    template <typename FactorType,
              typename ExpressionType>
    struct coefficient
    {
      typedef typename viennamath::result_of::expand<ExpressionType>::type    expanded_expression;
      
      typedef typename coefficient_impl<FactorType, expanded_expression>::type    type;
    };
  }
  
  
  //public interface:
  template <typename FactorType,
            typename ExpressionType>
  typename viennamath::result_of::coefficient<FactorType, ExpressionType>::type
  coefficient(FactorType const & f, ExpressionType const & e)
  {
    return typename viennamath::result_of::coefficient<FactorType, ExpressionType>::type();
  }
  
  
  
  
  
  //////////////// run time ///////////////////////////
  
  // Not yet available
  
}

#endif
