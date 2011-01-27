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
#include "viennamath/variable.hpp"

namespace viennamath
{
  //////////////// reduce a rational expression consistnig of ct_constants to its simplest form ///////////////////////
  template <typename ExpressionType>
  struct rational_evaluation
  {
    typedef typename ExpressionType::ERROR_INVALID_TYPE_SUPPLIED   result_type;
  };
  

  template <typename LHS, typename OP, typename RHS>
  struct rational_evaluation < expression<LHS, OP, RHS> >
  {
    typedef expression< typename rational_evaluation<LHS>::result_type,
                        OP,
                        typename rational_evaluation<RHS>::result_type>  result_type;
  };
  
  //////////////////  compound expressions (with fractions) ////////////////////////////
  
  // A + B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_plus,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1 * denominator_2 + numerator_2 * denominator_1>,
                        op_div,
                        ct_constant<denominator_1 * denominator_2> >        result_type;
  };

  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_plus,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<value_1 * denominator_2 + numerator_2>,
                        op_div,
                        ct_constant<denominator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_plus,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1 + value_2 * denominator_1>,
                        op_div,
                        ct_constant<denominator_1> >        result_type;
  };
  
  
  
  // A - B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_minus,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1 * denominator_2 - numerator_2 * denominator_1>,
                        op_div,
                        ct_constant<denominator_1 * denominator_2> >        result_type;
  };
  
  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_minus,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<value_1 * denominator_2 - numerator_2>,
                        op_div,
                        ct_constant<denominator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_minus,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1 - value_2 * denominator_1>,
                        op_div,
                        ct_constant<denominator_1> >        result_type;
  };
  
  // A * B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_mult,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1 * numerator_2>,
                        op_div,
                        ct_constant<denominator_1 * denominator_2> >        result_type;
  };
  
  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_mult,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<value_1 * numerator_2>,
                        op_div,
                        ct_constant<denominator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_mult,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1 * value_2>,
                        op_div,
                        ct_constant<denominator_1> >        result_type;
  };
  
  // A / B:
  template <long numerator_1, long denominator_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_div,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1 * denominator_2>,
                        op_div,
                        ct_constant<denominator_1 * numerator_2> >        result_type;
  };
  
  template <long value_1,
            long numerator_2, long denominator_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_div,
                                         expression<ct_constant<numerator_2>,
                                                    op_div,
                                                    ct_constant<denominator_2> >
                                         >
                            >
  {
    typedef expression< ct_constant<value_1 * denominator_2>,
                        op_div,
                        ct_constant<numerator_2> >        result_type;
  };

  template <long numerator_1, long denominator_1,
            long value_2>
  struct rational_evaluation< expression<expression<ct_constant<numerator_1>,
                                                    op_div,
                                                    ct_constant<denominator_1> >,
                                         op_div,
                                         ct_constant<value_2>
                                         >
                            >
  {
    typedef expression< ct_constant<numerator_1>,
                        op_div,
                        ct_constant<denominator_1 * value_2> >        result_type;
  };
  
  //primitive expressions
  template <long value_1, long value_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_plus,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef ct_constant<value_1 + value_2>   result_type;
  };
  
  template <long value_1, long value_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_minus,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef ct_constant<value_1 - value_2>   result_type;
  };

  template <long value_1, long value_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_mult,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef ct_constant<value_1 * value_2>   result_type;
  };
  
  template <long value_1, long value_2>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_div,
                                         ct_constant<value_2>
                                        >
                            >
  {
    typedef expression<ct_constant<value_1>,
                       op_div,
                       ct_constant<value_2>
                      >                      result_type;
  };
  
  template <long value_1>
  struct rational_evaluation< expression<ct_constant<value_1>,
                                         op_div,
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
  
  
  template <typename ScalarType, typename VectorType>
  struct ct_evaluation < constant<ScalarType>, VectorType>
  {
    typedef typename VectorType::ERROR_RUNTIME_CONSTANT_NOT_ALLOWED_IN_COMPILETIME_EVALUATION  error_type;
  };

  template <typename VectorType>
  struct ct_evaluation < binary_expr, VectorType>
  {
    typedef typename VectorType::ERROR_RUNTIME_EXPRESSION_NOT_ALLOWED_IN_COMPILETIME_EVALUATION  error_type;
  };

  //valid arguments:
  template <typename LHS, typename OP, typename RHS, typename VectorType>
  struct ct_evaluation< expression<LHS, OP, RHS>, VectorType>
  {
    typedef expression< typename ct_evaluation<LHS, VectorType>::result_type,
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
  struct ct_evaluation< variable<id>, VectorType>
  {
    typedef typename type_by_index<VectorType, id>::result_type  result_type;
  };
  
  template <long value>
  struct ct_evaluation< variable<0>, ct_constant<value> >
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
  struct is_ct_evaluable< expression<LHS, OP, RHS> >
  {
    enum { return_value = is_ct_evaluable<LHS>::return_value * is_ct_evaluable<RHS>::return_value };
  };
  
  template <long value>
  struct is_ct_evaluable< ct_constant<value> >
  {
    enum { return_value = 1 };
  };
  
  template <unsigned long id>
  struct is_ct_evaluable< variable<id> >
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