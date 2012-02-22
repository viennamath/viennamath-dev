#ifndef VIENNAMATH_MANIPULATION_INTEGRATE_HPP
#define VIENNAMATH_MANIPULATION_INTEGRATE_HPP

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
#include "viennamath/compiletime/ct_interval.hpp"
#include "viennamath/manipulation/expand.hpp"
#include "viennamath/manipulation/optimize.hpp"
#include "viennamath/manipulation/substitute.hpp"

namespace viennamath
{
  //////////// compile time ///////////////////
  namespace result_of
  {
    //returns the power of ct_variable<id>
    template <typename VariableType, typename ExpressionType>
    struct polynomial_degree
    {
      enum { value = 0 }; 
    };
    
    template <typename VariableType>
    struct polynomial_degree <VariableType, VariableType>
    {
      enum { value = 1 }; 
    };
    
    template <typename VariableType,
              typename LHS, typename NumericT, typename RHS>
    struct polynomial_degree <VariableType, ct_binary_expr<LHS, op_mult<NumericT>, RHS> >
    {
      enum { value = polynomial_degree<VariableType, LHS>::value + polynomial_degree<VariableType, RHS>::value }; 
    };

    template <typename VariableType,
              typename LHS, typename NumericT, typename RHS>
    struct polynomial_degree <VariableType, ct_binary_expr<LHS, op_div<NumericT>, RHS> >
    {
      enum { value = polynomial_degree<VariableType, LHS>::value }; 
    };
    
    
    // compute power of an expression
    template <typename T, long exponent>
    struct pow 
    {
      // balance generated binary expression equally between LHS and RHS:
      typedef ct_binary_expr< typename pow<T, exponent / 2>::type,
                              op_mult<default_numeric_type>,
                              typename pow<T, exponent - exponent / 2>::type>  type;
    };
    
    template <typename T>
    struct pow <T, 0>
    {
      typedef ct_constant<1>  type;
    };

    template <typename T>
    struct pow <T, 1>
    {
      typedef T  type;
    };

    template <typename T>
    struct pow <T, 2>
    {
      typedef ct_binary_expr<T, op_mult<default_numeric_type>, T>  type;
    };

    
    
    //integrate monomial:
    template <typename SubstituteType,
              long exponent>
    struct integrate_monomial
    {
      typedef ct_binary_expr< typename pow<SubstituteType, exponent + 1>::type,
                              op_div<default_numeric_type>,
                              ct_constant<exponent + 1>
                            >         type;
    };

    template <typename SubstituteType>
    struct integrate_monomial < SubstituteType, 0>
    {
      typedef SubstituteType      type;
    };
    
    
    ///////
    template <typename LowerBound, typename UpperBound,
              typename IntegrandType,
              typename VariableType>
    struct integrate {}; //SFINAE for interface function viennamath::integrate()
    
    
    template <typename LowerBound, typename UpperBound,
              typename IntegrandType,
              typename VariableType>
    struct integrate_impl {};
    
    
    
    template <typename LowerBound, typename UpperBound,
              typename LHS, typename NumericT, typename RHS,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_binary_expr<LHS, op_plus<NumericT>, RHS>,
                           VariableType
                          >
    {
      typedef ct_binary_expr< typename integrate_impl<LowerBound, UpperBound, LHS, VariableType>::type,
                              op_plus<NumericT>,
                              typename integrate_impl<LowerBound, UpperBound, RHS, VariableType>::type
                            >                   integrated_type;
                            
      typedef typename viennamath::result_of::optimize<integrated_type>::type    type;
    };

    template <typename LowerBound, typename UpperBound,
              typename LHS, typename NumericT, typename RHS,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_binary_expr<LHS, op_minus<NumericT>, RHS>,
                           VariableType
                          >
    {
      typedef ct_binary_expr< typename integrate_impl<LowerBound, UpperBound, LHS, VariableType>::type,
                              op_minus<NumericT>,
                              typename integrate_impl<LowerBound, UpperBound, RHS, VariableType>::type
                            >                   integrated_type;
                            
      typedef typename viennamath::result_of::optimize<integrated_type>::type    type;
    };


    template <typename LowerBound, typename UpperBound,
              typename LHS, typename NumericT, typename RHS,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_binary_expr<LHS, op_mult<NumericT>, RHS>,
                           VariableType
                          >
    {
      //extract coefficient:
      typedef typename viennamath::result_of::substitute< VariableType,
                                                          ct_constant<1>,
                                                          ct_binary_expr<LHS, op_mult<NumericT>, RHS> >::type    coefficient_type;
                                                          
      typedef typename viennamath::result_of::optimize<coefficient_type>::type    optimized_coefficient_type;                                                    
      
      enum { exponent = polynomial_degree<VariableType, 
                                          ct_binary_expr<LHS, op_mult<NumericT>, RHS>
                                         >::value  };
      
      typedef ct_binary_expr< typename integrate_monomial<UpperBound, exponent>::type,
                              op_mult<NumericT>,
                              optimized_coefficient_type
                            >                    upper_contribution;    

      typedef ct_binary_expr< typename integrate_monomial<LowerBound, exponent>::type,
                              op_mult<NumericT>,
                              optimized_coefficient_type
                            >                    lower_contribution;    
                            
      typedef ct_binary_expr< typename optimize<upper_contribution>::type,
                              op_minus<NumericT>,
                              typename optimize<lower_contribution>::type
                            >            integrated_type;                      
      
      typedef typename viennamath::result_of::optimize<integrated_type>::type    type;
    };

    template <typename LowerBound, typename UpperBound,
              typename LHS, typename NumericT, typename RHS,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_binary_expr<LHS, op_div<NumericT>, RHS>,
                           VariableType
                          >
    {
      //assume polynomial, thus integrate numerator only:
      typedef ct_binary_expr< typename integrate_impl<LowerBound, UpperBound,
                                                      LHS,
                                                      VariableType>::type,
                              op_div<NumericT>,
                              RHS>                     integrated_type;
                              
      typedef typename viennamath::result_of::optimize<integrated_type>::type    type;
    };
    
    template <typename LowerBound, typename UpperBound,
              typename LHS, typename OP,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_unary_expr<LHS, OP>,
                           VariableType
                          >
    {
      typedef typename ct_unary_expr<LHS, OP>::ERROR_INTEGRATION_OF_UNARY_EXPRESSION_NOT_SUPPORTED    type;
    };

    template <typename LowerBound, typename UpperBound,
              long value,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_constant<value>,
                           VariableType
                          >
    {
      typedef ct_binary_expr<UpperBound,
                             op_minus<default_numeric_type>,
                             LowerBound
                            >                    interval_length;
                            
      typedef ct_binary_expr< ct_constant<value>,
                              op_mult<default_numeric_type>,
                              interval_length
                            >    integrated_type;
                            
       typedef typename viennamath::result_of::optimize<integrated_type>::type   type;
    };

    template <typename LowerBound, typename UpperBound,
              typename TAG,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_function_symbol<TAG>,
                           VariableType
                          >
    {
      typedef typename ct_function_symbol<TAG>::ERROR_INTEGRATION_OF_FUNCTION_SYMBOL_NOT_SUPPORTED    type;
    };
    
    template <typename LowerBound, typename UpperBound,
              id_type id,
              typename VariableType>
    struct integrate_impl <LowerBound, UpperBound,
                           ct_variable<id>,
                           VariableType
                          >
    {
      typedef ct_binary_expr< ct_binary_expr<UpperBound,
                                             op_mult<default_numeric_type>,
                                             UpperBound
                                             >,
                              op_div<default_numeric_type>,
                              ct_constant<2>
                            >    upper_contribution;

      typedef ct_binary_expr< ct_binary_expr<LowerBound,
                                             op_mult<default_numeric_type>,
                                             LowerBound
                                             >,
                              op_div<default_numeric_type>,
                              ct_constant<2>
                            >    lower_contribution;
                            
      typedef ct_binary_expr<upper_contribution,
                             op_minus<default_numeric_type>,
                             lower_contribution>      integrated_type;                      
                            
      typedef typename viennamath::result_of::optimize<integrated_type>::type   type;
    };
    
    
    
    //
    // public metafunction overloads:
    template <typename LowerBound, typename UpperBound,
              typename LHS, typename OP, typename RHS,
              typename VariableType>
    struct integrate <LowerBound, UpperBound,
                      ct_binary_expr<LHS, OP, RHS>,
                      VariableType
                     >
    {
      //prepare 
      typedef ct_binary_expr<LHS, OP, RHS>                                        IntegrandType;
      typedef typename viennamath::result_of::expand<IntegrandType>::type         expanded_integrand;
      typedef typename viennamath::result_of::optimize<expanded_integrand>::type  optimized_integrand;
      
      typedef typename integrate_impl<LowerBound, UpperBound,
                                      optimized_integrand,
                                      VariableType>::type    type;
      
    };

    template <typename LowerBound, typename UpperBound,
              typename LHS, typename OP,
              typename VariableType>
    struct integrate <LowerBound, UpperBound,
                      ct_unary_expr<LHS, OP>,
                      VariableType
                     >
    {
      typedef typename ct_unary_expr<LHS, OP>::ERROR_INTEGRATION_OF_UNARY_EXPRESSION_NOT_SUPPORTED    type;
    };

    template <typename LowerBound, typename UpperBound,
              long value,
              typename VariableType>
    struct integrate <LowerBound, UpperBound,
                      ct_constant<value>,
                      VariableType
                     >
    {
      typedef typename integrate_impl<LowerBound, UpperBound, ct_constant<value>, VariableType >::type    type;
    };

    template <typename LowerBound, typename UpperBound,
              typename TAG,
              typename VariableType>
    struct integrate <LowerBound, UpperBound,
                      ct_function_symbol<TAG>,
                      VariableType
                     >
    {
      typedef typename ct_function_symbol<TAG>::ERROR_INTEGRATION_OF_FUNCTION_SYMBOL_NOT_SUPPORTED    type;
    };
    
    template <typename LowerBound, typename UpperBound,
              id_type id,
              typename VariableType>
    struct integrate <LowerBound, UpperBound,
                      ct_variable<id>,
                      VariableType
                     >
    {
      typedef typename integrate_impl<LowerBound, UpperBound, ct_variable<id>, VariableType >::type    type;
    };
    
    
  } // namespace result_of

  template <typename LowerBound, typename UpperBound,
            typename IntegrandType,
            typename VariableType>
  typename result_of::integrate<LowerBound, UpperBound,
                                IntegrandType,
                                VariableType>::type
  integrate( ct_interval<LowerBound, UpperBound> const & interv,
             IntegrandType const & integrand,
             VariableType const & var)
  {
    return typename result_of::integrate<LowerBound, UpperBound,
                                         IntegrandType,
                                         VariableType>::type();
  }

  
  //////////// run time ///////////////////
  
  //TODO
  
}

#endif
