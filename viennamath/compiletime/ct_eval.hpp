/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_EVAL_HPP
#define VIENNAMATH_CT_EVAL_HPP

#include "viennamath/forwards.h"
#include "viennamath/runtime/variable.hpp"

namespace viennamath
{
  //////////////// reduce a rational expression consistnig of ct_constants to its simplest form ///////////////////////
  template <typename ExpressionType>
  struct rational_evaluation
  {
    typedef typename ExpressionType::ERROR_INVALID_TYPE_SUPPLIED   result_type;
  };
  

  template <typename LHS, typename OP, typename RHS>
  struct rational_evaluation < ct_expr<LHS, OP, RHS> >
  {
    typedef ct_expr< typename rational_evaluation<LHS>::result_type,
                        OP,
                        typename rational_evaluation<RHS>::result_type>  result_type;
  };
  
  //////////////////  compound expressions (with fractions) ////////////////////////////
  
  // A + B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                              op_div<default_numeric_type>,
                                              ct_constant<denominator_1> >,
                                      op_plus<default_numeric_type>,
                                      ct_expr<ct_constant<numerator_2>,
                                              op_div<default_numeric_type>,
                                              ct_constant<denominator_2> >
                                      >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1 * denominator_2 + numerator_2 * denominator_1>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1 * denominator_2> >        result_type;
  };

  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_plus<default_numeric_type>,
                                         ct_expr<ct_constant<numerator_2>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef ct_expr< ct_constant<value_1 * denominator_2 + numerator_2>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_1> >,
                                         op_plus<default_numeric_type>,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1 + value_2 * denominator_1>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1> >        result_type;
  };
  
  
  
  // A - B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_1> >,
                                         op_minus<default_numeric_type>,
                                         ct_expr<ct_constant<numerator_2>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1 * denominator_2 - numerator_2 * denominator_1>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1 * denominator_2> >        result_type;
  };
  
  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_minus<default_numeric_type>,
                                         ct_expr<ct_constant<numerator_2>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef ct_expr< ct_constant<value_1 * denominator_2 - numerator_2>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_1> >,
                                         op_minus<default_numeric_type>,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1 - value_2 * denominator_1>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1> >        result_type;
  };
  
  // A * B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_1> >,
                                         op_mult<default_numeric_type>,
                                         ct_expr<ct_constant<numerator_2>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1 * numerator_2>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1 * denominator_2> >        result_type;
  };
  
  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_mult<default_numeric_type>,
                                         ct_expr<ct_constant<numerator_2>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef ct_expr< ct_constant<value_1 * numerator_2>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_1> >,
                                         op_mult<default_numeric_type>,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1 * value_2>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1> >        result_type;
  };
  
  // A / B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_1> >,
                                         op_div<default_numeric_type>,
                                         ct_expr<ct_constant<numerator_2>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1 * denominator_2>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1 * numerator_2> >        result_type;
  };
  
  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_div<default_numeric_type>,
                                         ct_expr<ct_constant<numerator_2>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef ct_expr< ct_constant<value_1 * denominator_2>,
                        op_div<default_numeric_type>,
                        ct_constant<numerator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< ct_expr<ct_expr<ct_constant<numerator_1>,
                                                    op_div<default_numeric_type>,
                                                    ct_constant<denominator_1> >,
                                         op_div<default_numeric_type>,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef ct_expr< ct_constant<numerator_1>,
                        op_div<default_numeric_type>,
                        ct_constant<denominator_1 * value_2> >        result_type;
  };
  
  //primitive expressions
  template <long value_1, long value_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_plus<default_numeric_type>,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef ct_constant<value_1 + value_2>   result_type;
  };
  
  template <long value_1, long value_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_minus<default_numeric_type>,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef ct_constant<value_1 - value_2>   result_type;
  };

  template <long value_1, long value_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_mult<default_numeric_type>,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef ct_constant<value_1 * value_2>   result_type;
  };
  
  template <long value_1, long value_2>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_div<default_numeric_type>,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef ct_expr<ct_constant<value_1>,
                       op_div<default_numeric_type>,
                       ct_constant<value_2>
                      >                      result_type;
  };
  
  template <long value_1>
  struct rational_evaluation< ct_expr<ct_constant<value_1>,
                                         op_div<default_numeric_type>,
                                         ct_constant<1>
                                        >
                            >
  {
    typedef ct_constant<value_1>             result_type;
  };
  
  //primitive constant:
  template <long value_1>
  struct rational_evaluation< ct_constant<value_1> >
  {
    typedef ct_constant<value_1>             result_type;
  };
  
  
  
  
  
  
  ///////////////// compile time evaluation //////////////////////////
  
  
  template <typename ExpressionType, typename VectorType>
  struct ct_evaluation
  {
    typedef typename ExpressionType::ERROR_INVALID_EXPRESSION_TYPE_FOR_COMPILETIME_EVALUATION  error_type;
  };
  
  
  template <typename ScalarType, typename InterfaceType, typename VectorType>
  struct ct_evaluation < rt_constant<ScalarType, InterfaceType>, VectorType>
  {
    typedef typename VectorType::ERROR_RUNTIME_CONSTANT_NOT_ALLOWED_IN_COMPILETIME_EVALUATION  error_type;
  };

  template <typename InterfaceType, typename VectorType>
  struct ct_evaluation < rt_unary_expr<InterfaceType>, VectorType>
  {
    typedef typename VectorType::ERROR_RUNTIME_EXPRESSION_NOT_ALLOWED_IN_COMPILETIME_EVALUATION  error_type;
  };
  
  template <typename InterfaceType, typename VectorType>
  struct ct_evaluation < rt_binary_expr<InterfaceType>, VectorType>
  {
    typedef typename VectorType::ERROR_RUNTIME_EXPRESSION_NOT_ALLOWED_IN_COMPILETIME_EVALUATION  error_type;
  };

  //valid arguments:
  template <typename LHS, typename OP, typename RHS, typename VectorType>
  struct ct_evaluation< ct_expr<LHS, OP, RHS>, VectorType>
  {
    typedef ct_expr< typename ct_evaluation<LHS, VectorType>::result_type,
                        OP,
                        typename ct_evaluation<RHS, VectorType>::result_type >  intermediate_type;
                        
    typedef typename rational_evaluation<intermediate_type>::result_type   result_type;                    
    //typedef intermediate_type   result_type; //DEBUG                    
  };
  
  template <long value, typename VectorType>
  struct ct_evaluation< ct_constant<value>, VectorType>
  {
    typedef ct_constant<value>    result_type;
  };
  
  template <unsigned long id, typename VectorType>
  struct ct_evaluation< ct_variable<id>, VectorType>
  {
    typedef typename type_by_index<VectorType, id>::result_type  result_type;
  };
  
  template <long value>
  struct ct_evaluation< ct_variable<0>, ct_constant<value> >
  {
    typedef ct_constant<value>  result_type;
  };
  
  
  
  
  
  /** @brief Returns nonzero if supplied expression can be evaluated at compile time */
  template <typename E>
  struct is_ct_evaluable
  {
    enum { return_value = 0 };
  };
  
  template <typename LHS, typename OP, typename RHS>
  struct is_ct_evaluable< ct_expr<LHS, OP, RHS> >
  {
    enum { return_value = is_ct_evaluable<LHS>::return_value * is_ct_evaluable<RHS>::return_value };
  };
  
  template <long value>
  struct is_ct_evaluable< ct_constant<value> >
  {
    enum { return_value = 1 };
  };
  
  template <unsigned long id>
  struct is_ct_evaluable< ct_variable<id> >
  {
    enum { return_value = 1 };
  };
  
  //the public interface function:
  template <typename ExpressionType, typename VectorType>
  typename ct_evaluation<ExpressionType, VectorType>::result_type
  ct_eval(ExpressionType const & e, VectorType const & v)
  {
    return typename ct_evaluation<ExpressionType, VectorType>::result_type();
  }
  
}

#endif