/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */

  //prototypes for expressions.h
#ifndef ELFEM_EXPRESSION_HEADER_GUARD
#define ELFEM_EXPRESSION_HEADER_GUARD

namespace elfem{

  template <typename CellTag>
  struct BFStock;

namespace expressions{

  template <typename EXPR, typename BF1, typename BF2>
  struct EXPRESSION_SUBSTITUTE_BASISFUNCTIONS;

  template <typename EXP, bool again = true>
  struct EXPRESSION_OPTIMIZER;

  template <typename T, typename LHS, typename RHS, typename OP >
  class Expression;

  typedef double          ExpressionDefaultScalarType;

  template <unsigned long id>
  struct var;

  template <long num, typename diff_tag>
  struct basisfun;

  template <typename LHS, typename RHS, typename OP>
  struct LogicalExpression;

  template <long value_>
  struct ScalarExpression;

  template <typename T>
  struct op_plus;

  template <typename T>
  struct op_minus;

  template <typename T>
  struct op_mult;

  template <typename T>
  struct op_div;

  struct op_equal;

  struct CompoundUnused;

  template <long num, long denum,
              typename T1, long pow1,
              typename T2, long pow2,   //no point in using less than two compound-types
              typename T3 = CompoundUnused, long pow3 = 0,
              typename T4 = CompoundUnused, long pow4 = 0
            >
  struct CompoundExpression;


  template <typename L_BOUND, typename U_BOUND, typename EXPR, typename INTVAR>
  struct EXPRESSION_INTEGRATE;

  template <typename EXPR, long startval = 1>
  struct EXPRESSION_EXPAND;

//   template <typename EXPR, typename BF1, typename BF2>
//   struct ANALYTIC_INTEGRATION_ON_LINE;
// 
//   template <typename EXPR, typename BF1, typename BF2>
//   struct ANALYTIC_INTEGRATION_ON_TRIANGLE;
// 
//   template <typename EXPR, typename BF1, typename BF2>
//   struct ANALYTIC_INTEGRATION_ON_TETRAHEDRON;


  template <typename CellTag, typename EXPR, typename BF1, typename BF2>
  struct ANALYTIC_INTEGRATION;

  template <typename EXPR>
  struct EXPRESSION_REDUCE_DIVISIONS;


  template <char diffvar, typename EXPR, typename op_tag = typename EXPR::OperatorType>
  struct DiffTraits;

  // helper struct for evaluation at a point (cf. ExpressionHelper)

  // for (compounded) expressions:
  template <typename T>
  struct PointEvaluator
  {
    template <typename Point>
    static double apply(T const & expr, Point const & p)
    {
      return expr(p);
    }
  };

  template <>
  struct PointEvaluator<double>
  {
    template <typename Point>
    static double apply(double value, Point const & p)
    {
      return value;
    }
  };

  template <>
  struct PointEvaluator<float>
  {
    template <typename Point>
    static float apply(float value, Point const & p)
    {
      return value;
    }
  };

  template <>
  struct PointEvaluator<long>
  {
    template <typename Point>
    static long apply(long value, Point const & p)
    {
      return value;
    }
  };

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

  template <long id>
  struct Gamma;

  template <long id>
  struct Interface;

} //expressions

} //elfem

#endif

