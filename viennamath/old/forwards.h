/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */

#ifndef VIENNAMATH_FORWARDS_GUARD
#define VIENNAMATH_FORWARDS_GUARD

namespace viennamath{

 namespace expressions{

  template <typename EXP, bool again = true>
  struct EXPRESSION_OPTIMIZER;

  ///////// representation of a mathematical expression: ///////////////
  
  //compile time expression:
  template <typename RetType, typename LHS, typename RHS, typename OP >
  class ct_expr;

  //runtime expression
  template <typename RetType>
  class rt_expr;
  
  
  ///////// representation of (scalar and vector-valued) functions: ////////////
  
  //       (to be done) - concept required!
  
  
  ///////// tags for operators: /////////////////////
  struct op_plus;
  struct op_minus;
  struct op_mult;
  struct op_div;
  //struct op_equal;

  template <typename L_BOUND, typename U_BOUND, typename EXPR, typename INTVAR>
  struct EXPRESSION_INTEGRATE;

  template <typename EXPR, long startval = 1>
  struct EXPRESSION_EXPAND;

  template <typename EXPR>
  struct EXPRESSION_REDUCE_DIVISIONS;


  template <char diffvar, typename EXPR, typename op_tag = typename EXPR::OperatorType>
  struct DiffTraits;

  // helper struct for evaluation at a point (cf. ExpressionHelper)

  template <long arg>
  struct FACTORIAL
  {
    enum { ReturnValue = arg * FACTORIAL<arg-1>::ReturnValue };
  };

  template <>
  struct FACTORIAL<0>
  {
    enum { ReturnValue = 1 };
  };

  //Definitions from assembly:
  template <typename LHSType, typename RHSType>
  struct EquationType;

  template <typename IntDomain, typename Integrand, typename IntTag>
  struct IntegrationType;

} //expressions

} //elfem

#endif

