/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */


// Expression optimisation engine. Included by expressions.h!

  //forward declaration of working horse EXPRESSION_OPTIMIZER_IMPL:
  template <typename EXP>
  struct EXPRESSION_OPTIMIZER_IMPL;

  //public interface and loop over optimisation steps:
  template <typename EXP, bool again>
  struct EXPRESSION_OPTIMIZER
  {
    typedef typename EXPRESSION_OPTIMIZER< typename EXPRESSION_OPTIMIZER_IMPL<EXP>::ResultType,
                                        (EXPRESSION_OPTIMIZER_IMPL<EXP>::Again != 0)
                                      >::ResultType   ResultType;
  };

  template <typename EXP>
  struct EXPRESSION_OPTIMIZER <EXP, false>
  {
    typedef EXP   ResultType;
  };

  //testing purposes:
  template <typename EXPR>
  typename EXPRESSION_OPTIMIZER<EXPR>::ResultType
  expression_optimize(EXPR const &)
  {
    return typename EXPRESSION_OPTIMIZER<EXPR>::ResultType();
  }

  //general optimisation rule if no specialisation applies: Do not change the expression! (e.g. x*y)
  template <typename EXP>
  struct EXPRESSION_OPTIMIZER_IMPL
  {
    enum { Again = 0 };
    typedef EXP ResultType;
  };

  //general expression: optimise LHS and RHS:
  template <typename T, typename LHS, typename RHS, typename OP>
  struct EXPRESSION_OPTIMIZER_IMPL< Expression<T, LHS, RHS, OP> >
  {
    typedef Expression< T,
                          typename EXPRESSION_OPTIMIZER_IMPL<LHS>::ResultType,
                          typename EXPRESSION_OPTIMIZER_IMPL<RHS>::ResultType,
                          OP
                        > ResultType;
    enum { Again = EXPRESSION_OPTIMIZER_IMPL<LHS>::Again + EXPRESSION_OPTIMIZER_IMPL<RHS>::Again };
  };

/**************************************************************************/
/**************       Optimization rules         **************************/
/**************************************************************************/

  /*
  * pull scalars together:
  * (for +,-,*, but not for / since template argument must be an integer!
  */
  template <typename T, long left, long right>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<left>,
                                          ScalarExpression<right>,
                                          op_plus<T>
                                        >
                              >
  {
    typedef ScalarExpression< left + right > ResultType;
    enum { Again = 1 };
  };

  template <typename T, long left, long right>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<left>,
                                          ScalarExpression<right>,
                                          op_minus<T>
                                        >
                              >
  {
    typedef ScalarExpression< left - right > ResultType;
    enum { Again = 1 };
  };

  template <typename T, long left, long right>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<left>,
                                          ScalarExpression<right>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression< left * right > ResultType;
    enum { Again = 1 };
  };

  /*
  * eliminate multiplications by zero:
  */
  template <typename T, typename RHS>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          RHS,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression< 0 > ResultType;
    enum { Again = 1 };
  };

  template <typename T, typename LHS>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          LHS,
                                          ScalarExpression<0>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression< 0 > ResultType;
    enum { Again = 1 };
  };

  //avoid ambiguities:
  template <typename T>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<0>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression< 0 > ResultType;
    enum { Again = 1 };
  };

  template <typename T, long lhs>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<lhs>,
                                          ScalarExpression<0>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression< 0 > ResultType;
    enum { Again = 1 };
  };

  template <typename T, long rhs>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<rhs>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression< 0 > ResultType;
    enum { Again = 1 };
  };

  /*
  * eliminate addition/subtraction of zero:
  */

  //for plus:
  template <typename T, typename RHS>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          RHS,
                                          op_plus<T>
                                        >
                              >
  {
    typedef RHS ResultType;
    enum { Again = 1 };
  };

  template <typename T, typename LHS>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          LHS,
                                          ScalarExpression<0>,
                                          op_plus<T>
                                        >
                              >
  {
    typedef LHS ResultType;
    enum { Again = 1 };
  };

  //avoid ambiguity:
  template <typename T>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<0>,
                                          op_plus<T>
                                        >
                              >
  {
    typedef ScalarExpression<0> ResultType;
    enum { Again = 1 };
  };

  template <typename T, long left>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<left>,
                                          ScalarExpression<0>,
                                          op_plus<T>
                                        >
                              >
  {
    typedef ScalarExpression<left> ResultType;
    enum { Again = 1 };
  };

  template <typename T, long right>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<right>,
                                          op_plus<T>
                                        >
                              >
  {
    typedef ScalarExpression<right> ResultType;
    enum { Again = 1 };
  };

  //for minus: since 0-x = -x the only case of interest is x-0=x.
  template <typename T, typename LHS>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          LHS,
                                          ScalarExpression<0>,
                                          op_minus<T>
                                        >
                              >
  {
    typedef LHS ResultType;
    enum { Again = 1 };
  };

  template <typename T, long value>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<value>,
                                          ScalarExpression<0>,
                                          op_minus<T>
                                        >
                              >
  {
    typedef ScalarExpression<value> ResultType;
    enum { Again = 1 };
  };

  /*
  * eliminate multiplication by 1:
  */
  template <typename T, typename LHS>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          LHS,
                                          ScalarExpression<1>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef LHS ResultType;
    enum { Again = 1 };
  };

  template <typename T, typename RHS>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<1>,
                                          RHS,
                                          op_mult<T>
                                        >
                              >
  {
    typedef RHS ResultType;
    enum { Again = 1 };
  };

  template <typename T>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<1>,
                                          ScalarExpression<1>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression<1> ResultType;
    enum { Again = 1 };
  };

  template <typename T, long left>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<left>,
                                          ScalarExpression<1>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression<left> ResultType;
    enum { Again = 1 };
  };

  template <typename T, long right>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<1>,
                                          ScalarExpression<right>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression<right> ResultType;
    enum { Again = 1 };
  };

  //special case 1*0:
  template <typename T>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<1>,
                                          ScalarExpression<0>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression<0> ResultType;
    enum { Again = 1 };
  };

  template <typename T>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<1>,
                                          op_mult<T>
                                        >
                              >
  {
    typedef ScalarExpression<0> ResultType;
    enum { Again = 1 };
  };

  //division of zero by something non-zero
  template <typename T, long rhsval>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<rhsval>,
                                          op_div<T>
                                        >
                              >
  {
    typedef ScalarExpression<0>             ResultType;
    enum { Again = 1 };
  };

  //remove division by one:
  template <typename T, typename NUMERATOR>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          NUMERATOR,
                                          ScalarExpression<1>,
                                          op_div<T>
                                        >
                              >
  {
    typedef NUMERATOR        ResultType;
    enum { Again = 1 };
  };

  //special (ambiguity) case 0/1:
  template <typename T>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<1>,
                                          op_div<T>
                                        >
                              >
  {
    typedef ScalarExpression<0>        ResultType;
    enum { Again = 1 };
  };

  //force error for 0/0:
  template <typename T>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          ScalarExpression<0>,
                                          ScalarExpression<0>,
                                          op_div<T>
                                        >
                              >
  {
    typedef typename T::ERROR_0_DIVIDED_BY_ZERO_FOUND_BY_OPTIMIZER   ResultType;
    enum { Again = 1 };
  };

  //sum variables together:
  template <typename T, char c>
  struct EXPRESSION_OPTIMIZER_IMPL <
                              Expression< T,
                                          var<c>,
                                          var<c>,
                                          op_plus<T>
                                        >
                              >
  {
    typedef Expression< T,
                          ScalarExpression<2>,
                          var<c>,
                          op_mult<T>
                        >                                 ResultType;
    enum { Again = 1 };
  };

  //eliminate 0-minus-something terms:
  template<typename T, typename LHS1, typename RHS2>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 LHS1,
                                                 Expression<T,
                                                            ScalarExpression<0>,
                                                            RHS2,
                                                            op_minus<T>
                                                           >,
                                                 op_plus<T>
                                                >
                                  >
  {
    typedef Expression <T,
                         LHS1,
                         RHS2,
                         op_minus<T>
                        >                               ResultType;
    enum { Again = 1 };
  };

  //resolve ambiguity:
  template<typename T, typename RHS2>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 ScalarExpression<0>,
                                                 Expression<T,
                                                            ScalarExpression<0>,
                                                            RHS2,
                                                            op_minus<T>
                                                           >,
                                                 op_plus<T>
                                                >
                                  >
  {
    typedef Expression <T,
                         ScalarExpression<0>,
                         RHS2,
                         op_minus<T>
                        >                               ResultType;
    enum { Again = 1 };
  };

  template<typename T, typename LHS1, typename RHS2>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 LHS1,
                                                 Expression<T,
                                                            ScalarExpression<0>,
                                                            RHS2,
                                                            op_minus<T>
                                                           >,
                                                 op_minus<T>
                                                >
                                  >
  {
    typedef Expression <T,
                         LHS1,
                         RHS2,
                         op_plus<T>
                        >                               ResultType;
    enum { Again = 1 };
  };

  //eliminate multiplication by -1:
  template<typename T, typename LHS1, typename RHS2>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 LHS1,
                                                 Expression<T,
                                                            ScalarExpression<-1>,
                                                            RHS2,
                                                            op_mult<T>
                                                           >,
                                                 op_minus<T>
                                                >
                                  >
  {
    typedef Expression <T,
                         LHS1,
                         RHS2,
                         op_plus<T>
                        >                               ResultType;
    enum { Again = 1 };
  };

  template<typename T, typename LHS1, typename LHS2>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 LHS1,
                                                 Expression<T,
                                                            LHS2,
                                                            ScalarExpression<-1>,
                                                            op_mult<T>
                                                           >,
                                                 op_minus<T>
                                                >
                                  >
  {
    typedef Expression <T,
                         LHS1,
                         LHS2,
                         op_plus<T>
                        >                               ResultType;
    enum { Again = 1 };
  };

  template<typename T, typename LHS1>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 LHS1,
                                                 Expression<T,
                                                            ScalarExpression<-1>,
                                                            ScalarExpression<-1>,
                                                            op_mult<T>
                                                           >,
                                                 op_minus<T>
                                                >
                                  >
  {
    typedef Expression <T,
                         LHS1,
                         ScalarExpression<1>,
                         op_minus<T>
                        >                               ResultType;
    enum { Again = 1 };
  };


  /********************* fractionals: **********************/

  template <long a, long b>
  struct GREATEST_COMMON_DIVISOR
  {
    enum { ReturnValue = GREATEST_COMMON_DIVISOR< b, a - (a/b) * b >::ReturnValue };    //integer division!
  };

  template <long a>
  struct GREATEST_COMMON_DIVISOR<a, 0>
  {
    enum { ReturnValue = a };
  };


  //least common multiple is easy with gcd at hand:
  template <long a, long b>
  struct LEAST_COMMON_MULTIPLE
  {
    enum { ReturnValue = (a / GREATEST_COMMON_DIVISOR<a,b>::ReturnValue) * b };
  };


  template <long num, long denum>
  struct COMPRESS_FRACTIONAL 
  {
    enum{ Numerator = num / GREATEST_COMMON_DIVISOR<num, denum>::ReturnValue,
           Denominator = denum / GREATEST_COMMON_DIVISOR<num, denum>::ReturnValue };
  };

  template <typename T, long n1, long d1, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                            >,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_plus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*d2 + n2*d1, d1*d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*d2 + n2*d1, d1*d2>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long n1, long d1, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                            >,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_minus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*d2 - n2*d1, d1*d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*d2 - n2*d1, d1*d2>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };


  template <typename T, long n1, long d1, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                            >,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_mult<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*n2, d1*d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*n2, d1*d2>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };


  template <typename T, long val, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<val>,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_plus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * d2 + n2, d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * d2 + n2, d2>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  //eliminate ambiguities:
  template <typename T, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<0>,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_plus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n2, d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n2, d2>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };


  template <typename T, long val, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<val>,
                                                  op_plus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * d1 + n1, d1>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * d1 + n1, d1>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  //resolve ambiguities
  template <typename T, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<0>,
                                                  op_plus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1, d1>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1, d1>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };


  template <typename T, long val, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<val>,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_minus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * d2 - n2, d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * d2 - n2, d2>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long val, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<val>,
                                                  op_minus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1 - val * d1, d1>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1 - val * d1, d1>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  //resolve ambiguities:
  template <typename T, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<0>,
                                                  op_minus<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1, d1>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1, d1>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };


  template <typename T, long val, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<val>,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_mult<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * n2, d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * n2, d2>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<0>,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_mult<T>
                                                >
                                  >
  {
    typedef ScalarExpression<0>                 ResultType;
    enum { Again = 1 };
  };

  template <typename T, long d2, long n2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<1>,
                                                 Expression< T,
                                                             ScalarExpression<n2>,
                                                             ScalarExpression<d2>,
                                                             op_div<T>
                                                           >,
                                                  op_mult<T>
                                                >
                                  >
  {
    typedef Expression< T,
                          ScalarExpression<n2>,
                          ScalarExpression<d2>,
                          op_div<T>
                        >                           ResultType;
    enum { Again = 1 };
  };

  template <typename T, long val, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<val>,
                                                  op_mult<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * n1, d1>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<val * n1, d1>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<0>,
                                                  op_mult<T>
                                                >
                                  >
  {
    typedef ScalarExpression<0>                 ResultType;
    enum { Again = 1 };
  };

  template <typename T, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<1>,
                                                  op_mult<T>
                                                >
                                  >
  {
    typedef  Expression< T,
                          ScalarExpression<n1>,
                          ScalarExpression<d1>,
                          op_div<T>
                        >                                       ResultType;
    enum { Again = 1 };
  };


  template <typename T, long val, long d1, long n1>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 Expression< T,
                                                             ScalarExpression<n1>,
                                                             ScalarExpression<d1>,
                                                             op_div<T>
                                                           >,
                                                 ScalarExpression<val>,
                                                  op_div<T>
                                                >
                                  >
  {
    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1, d1 * val>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1, d1 * val>::Denominator>,
                        op_div<T>
                        >                                   ResultType;
    enum { Again = 1 };
  };

  /******************* compound Expression: **********************/

  template <typename T, long val, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<val>,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< COMPRESS_FRACTIONAL<num * val, denum>::Numerator,
                                  COMPRESS_FRACTIONAL<num * val, denum>::Denominator,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long val, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 ScalarExpression<val>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< COMPRESS_FRACTIONAL<num * val, denum>::Numerator,
                                  COMPRESS_FRACTIONAL<num * val, denum>::Denominator,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  //avoid ambiguities: multiplication by zero and one (unfortunately necessary)
  //for 1:
  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<1>,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 ScalarExpression<1>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 ScalarExpression<0>,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef ScalarExpression<0>                ResultType;
    enum { Again = 1 };
  };

  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 ScalarExpression<0>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef ScalarExpression<0>                ResultType;
    enum { Again = 1 };
  };

  ////////// absorb parts of compounded expression (x, y, z, ...) ////////////
  //for T1:
  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 T1,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1+1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 T1,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1+1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  //for T2:
  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 T2,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2+1,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 T2,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2+1,
                                  T3, pow3,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  //for T3:
  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 T3,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3+1,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 T3,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3+1,
                                  T4, pow4>                   ResultType;
    enum { Again = 1 };
  };

  //for T4:
  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 T4,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4+1>                   ResultType;
    enum { Again = 1 };
  };

  template <typename T, long num, long denum,
              typename T1, long pow1, typename T2, long pow2, typename T3, long pow3, typename T4, long pow4>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num, denum,
                                                                     T1, pow1,
                                                                     T2, pow2,
                                                                     T3, pow3,
                                                                     T4, pow4>,
                                                 T4,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< num, denum,
                                  T1, pow1,
                                  T2, pow2,
                                  T3, pow3,
                                  T4, pow4+1>                   ResultType;
    enum { Again = 1 };
  };

  //////////// multiply compounded expressions //////////////
  template <typename T, long num1, long denum1, long num2, long denum2,
              typename T1, long pow1_1, long pow1_2,
              typename T2, long pow2_1, long pow2_2,
              typename T3, long pow3_1, long pow3_2,
              typename T4, long pow4_1, long pow4_2>
  struct EXPRESSION_OPTIMIZER_IMPL < Expression < T,
                                                 CompoundExpression< num1, denum1,
                                                                     T1, pow1_1,
                                                                     T2, pow2_1,
                                                                     T3, pow3_1,
                                                                     T4, pow4_1>,
                                                 CompoundExpression< num2, denum2,
                                                                     T1, pow1_2,
                                                                     T2, pow2_2,
                                                                     T3, pow3_2,
                                                                     T4, pow4_2>,
                                                 op_mult<T>
                                                >
                                  >
  {
    typedef CompoundExpression< COMPRESS_FRACTIONAL<num1*num2, denum1*denum2>::Numerator,
                                  COMPRESS_FRACTIONAL<num1*num2, denum1*denum2>::Denominator,
                                  T1, pow1_1 + pow1_2,
                                  T2, pow2_1 + pow2_2,
                                  T3, pow3_1 + pow3_2,
                                  T4, pow4_1 + pow4_2>                   ResultType;
    enum { Again = 1 };
  };


  // eliminate possible 0 - integral(...) terms:
  template <typename T, typename IntDom, typename Integrand, typename IntTag>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 ScalarExpression<0>,
                                                 IntegrationType< IntDom,
                                                                  Integrand,
                                                                  IntTag
                                                           >,
                                                 op_minus<T>
                                                >
                                  >
  {
    typedef IntegrationType< IntDom,
                              Expression <T,
                                          ScalarExpression<-1>,
                                          Integrand,
                                          op_mult<T>
                                          >,
                              IntTag >                                    ResultType;
    enum { Again = 1 };
  };

  //prevent accumulation of (-1) for successive use of previous rule:
  template <typename T, typename IntDom, typename Integrand, typename IntTag>
  struct EXPRESSION_OPTIMIZER_IMPL <  Expression <T,
                                                 ScalarExpression<0>,
                                                 IntegrationType< IntDom,
                                                                Expression <T,
                                                                            ScalarExpression<-1>,
                                                                            Integrand,
                                                                            op_mult<T>
                                                                            >,
                                                                IntTag
                                                           >,
                                                 op_minus<T>
                                                >
                                  >
  {
    typedef IntegrationType< IntDom,
                            Integrand,
                            IntTag >                                    ResultType;
    enum { Again = 1 };
  };

