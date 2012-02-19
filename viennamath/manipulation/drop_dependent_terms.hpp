/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_DROP_DEPENDENT_TERMS_HPP
#define VIENNAMATH_DROP_DEPENDENT_TERMS_HPP

#include "viennamath/forwards.h"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/manipulation/optimize.hpp"

namespace viennamath
{
  
  ///////////////// compile time ////////////////////////////
  
  namespace result_of
  {
    
    /*
    //
    // Tokenizer: Extracts the factor from each token
    template <typename FactorType,
              typename ExpressionType>
    struct drop_dependent_terms_impl
    {
      typedef ExpressionType   type;
    };

    template <typename FactorType>
    struct drop_dependent_terms_impl<FactorType, FactorType>
    {
      typedef ct_constant<0>    type;
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct drop_dependent_terms_impl< FactorType, ct_binary_expr<LHS, op_plus<NumericT>, RHS> >
    {
      typedef ct_binary_expr< typename drop_dependent_terms_impl<FactorType, LHS>::type,
                              op_plus<NumericT>,
                              typename drop_dependent_terms_impl<FactorType, RHS>::type
                            >   type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct drop_dependent_terms_impl< FactorType, ct_binary_expr<LHS, op_minus<NumericT>, RHS> >
    {
      typedef ct_binary_expr< typename drop_dependent_terms_impl<FactorType, LHS>::type,
                              op_minus<NumericT>,
                              typename drop_dependent_terms_impl<FactorType, RHS>::type
                            >   type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct drop_dependent_terms_impl< FactorType, ct_binary_expr<LHS, op_mult<NumericT>, RHS> >
    {
      typedef ct_binary_expr< typename drop_dependent_terms_impl<FactorType, LHS>::type,
                              op_mult<NumericT>,
                              typename drop_dependent_terms_impl<FactorType, RHS>::type
                            >   type;
    };

    template <typename FactorType,
              typename NumericT, typename RHS>
    struct drop_dependent_terms_impl< FactorType, ct_binary_expr<FactorType, op_mult<NumericT>, RHS> >
    {
      typedef ct_constant<0>    type;
    };

    template <typename FactorType,
              typename LHS, typename NumericT>
    struct drop_dependent_terms_impl< FactorType, ct_binary_expr<LHS, op_mult<NumericT>, FactorType> >
    {
      typedef ct_constant<0>    type;
    };

    template <typename FactorType,
              typename NumericT>
    struct drop_dependent_terms_impl< FactorType, ct_binary_expr<FactorType, op_mult<NumericT>, FactorType> >
    {
      typedef ct_constant<0>    type;
    };
    
    template <typename FactorType,
              typename LHS, typename NumericT, typename RHS>
    struct drop_dependent_terms_impl< FactorType, ct_binary_expr<LHS, op_div<NumericT>, RHS> >
    {
      typedef ct_binary_expr< typename drop_dependent_terms_impl<FactorType, LHS>::type,
                              op_div<NumericT>,
                              RHS
                            >   type;
    }; */
    
    // Reuse existing functionality: Replace FactorType by ct_constant<0>, then optimize:

    //
    // Interface metafunction:
    template <typename FactorType,
              typename ExpressionType>
    struct drop_dependent_terms
    {
      typedef typename viennamath::result_of::expand<ExpressionType>::type    expanded_expression;

      typedef typename viennamath::result_of::substitute<FactorType, ct_constant<0>, expanded_expression>::type    substituted_expression;
      
      typedef typename viennamath::result_of::optimize<substituted_expression>::type    type;
    };
  }
  
  //interface function:
  template <typename FactorType,
            typename ExpressionType>
  typename result_of::drop_dependent_terms<FactorType, ExpressionType>::type
  drop_dependent_terms(FactorType const & f, ExpressionType const & e)
  {
    return typename result_of::drop_dependent_terms<FactorType, ExpressionType>::type();
  }
    
  //////////////// run time ///////////////////////////
  
  // Not yet available
}

#endif
