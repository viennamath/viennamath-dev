/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */

// provides some meta-functions for expression manipulation.

// Included by expressions.h

/********* Create the n-th power of an expression ****/
  template <typename EXPR, long exponent>
  struct POW
  {
    typedef Expression < ExpressionDefaultScalarType,
                          typename POW<EXPR, exponent - 1>::ResultType,
                          EXPR,
                          op_mult<ExpressionDefaultScalarType>
                        >                                           ResultType;
  };

  template <typename EXPR>
  struct POW < EXPR, 1 >
  {
    typedef EXPR                                           ResultType;
  };

  template <typename EXPR>
  struct POW < EXPR, 0 >
  {
    typedef ScalarExpression<1>                            ResultType;
  };

/************************ Check for pure scalar expression: ****************/
  //if expression is scalar, then ReturnValue !=0 
  template <typename EXPR>
  struct EXPRESSION_IS_SCALAR
  {
    enum { ReturnValue = 0 };
  };

  template <long val>
  struct EXPRESSION_IS_SCALAR < ScalarExpression<val> >
  {
    enum { ReturnValue = 1 };
  };

  //on a triangle or tetrahedron dt_dx is scalar as well:
  template <long row, long col>
  struct EXPRESSION_IS_SCALAR < dt_dx<row, col> >
  {
    enum { ReturnValue = 1 };
  };

  template <typename T, typename LHS, typename RHS, typename OP>
  struct EXPRESSION_IS_SCALAR < Expression<T, LHS, RHS, OP> >
  {
    enum { ReturnValue = EXPRESSION_IS_SCALAR<LHS>::ReturnValue *
                          EXPRESSION_IS_SCALAR<RHS>::ReturnValue };
  };

/************************ Substitute: ****************/

  // general case: EXPR is a non-matching primitive expression type, so nothing needs to be substituted:
  template <typename EXPR, typename KEY, typename REPLACEMENT>
  struct EXPRESSION_SUBSTITUTE
  {
    typedef EXPR      ResultType;
  };

  // substitute a primitive expression type:
  template <typename KEY, typename REPLACEMENT>
  struct EXPRESSION_SUBSTITUTE < KEY, KEY, REPLACEMENT >
  {
    typedef REPLACEMENT      ResultType;
  };

  // Left hand side matches:
  template <typename T, typename RHS, typename OP, typename KEY, typename REPLACEMENT>
  struct EXPRESSION_SUBSTITUTE < Expression<T, KEY, RHS, OP>, KEY, REPLACEMENT >
  {
    typedef Expression< T,
                          REPLACEMENT,
                          typename EXPRESSION_SUBSTITUTE<RHS, KEY, REPLACEMENT>::ResultType,
                          OP>                                           ResultType;
  };

  // Right hand side matches:
  template <typename T, typename LHS, typename OP, typename KEY, typename REPLACEMENT>
  struct EXPRESSION_SUBSTITUTE < Expression<T, LHS, KEY, OP>, KEY, REPLACEMENT >
  {
    typedef Expression< T,
                          typename EXPRESSION_SUBSTITUTE<LHS, KEY, REPLACEMENT>::ResultType,
                          REPLACEMENT,
                          OP>                                           ResultType;
  };

  // Both sides match:
  template <typename T, typename OP, typename KEY, typename REPLACEMENT>
  struct EXPRESSION_SUBSTITUTE < Expression<T, KEY, KEY, OP>, KEY, REPLACEMENT >
  {
    typedef Expression<T, REPLACEMENT, REPLACEMENT, OP>  ResultType;
  };

  //No match: Replace on RHS and LHS:
  template <typename T, typename LHS, typename RHS, typename OP, typename KEY, typename REPLACEMENT>
  struct EXPRESSION_SUBSTITUTE < Expression<T, LHS, RHS, OP>, KEY, REPLACEMENT >
  {
    typedef Expression < T,  
                          typename EXPRESSION_SUBSTITUTE < LHS, KEY, REPLACEMENT >::ResultType,
                          typename EXPRESSION_SUBSTITUTE < RHS, KEY, REPLACEMENT >::ResultType,
                          OP
                        >  ResultType;
  };

  //interface function
  template <typename EXPR, typename KEY, typename REPLACEMENT>
  typename EXPRESSION_SUBSTITUTE<EXPR, KEY, REPLACEMENT>::ResultType
  substitute(EXPR const &, KEY const &, REPLACEMENT const &)
  {
    return typename EXPRESSION_SUBSTITUTE<EXPR, KEY, REPLACEMENT>::ResultType();
  };

/************************ Operation Counter: ****************/

  //determine number of an operation in expression:
  template <typename EXPR, template<typename> class OP_KEY >
  struct EXPRESSION_OPERATION_COUNT
  { 
    enum { ReturnValue = 0 };
  };

  template <typename T, typename LHS, typename RHS, template<typename> class OP, template<typename> class OP_KEY>
  struct EXPRESSION_OPERATION_COUNT < Expression <T, LHS, RHS, OP<T> >, OP_KEY >
  {
    enum { ReturnValue = EXPRESSION_OPERATION_COUNT<LHS, OP_KEY>::ReturnValue +
                           EXPRESSION_OPERATION_COUNT<RHS, OP_KEY>::ReturnValue };
  };

  template <typename T, typename LHS, typename RHS, template<typename> class OP_KEY>
  struct EXPRESSION_OPERATION_COUNT < Expression <T, LHS, RHS, OP_KEY<T> >, OP_KEY  >
  {
    enum { ReturnValue = 1 + EXPRESSION_OPERATION_COUNT<LHS, OP_KEY>::ReturnValue +
                               EXPRESSION_OPERATION_COUNT<RHS, OP_KEY>::ReturnValue };
  };

  template < template<typename> class OP_KEY, typename EXPR>
  long get_operation_count(EXPR const &)
  {
    return EXPRESSION_OPERATION_COUNT<EXPR, OP_KEY>::ReturnValue;
  }

/*********************** Plus/Minus-Counter ********************/
  template <typename EXPR>
  struct EXPRESSION_PLUS_MINUS_COUNT
  {
    enum { ReturnValue = EXPRESSION_OPERATION_COUNT<EXPR, op_plus>::ReturnValue
                          + EXPRESSION_OPERATION_COUNT<EXPR, op_minus>::ReturnValue };
  };

/*********************** Expandable: ***************************/

  //determine whether a given expression can be expanded any further:
  // if expandable: ReturnValue != 0
  // if not expandable: ReturnValue == 0
  template < typename EXPR>
  struct EXPRESSION_EXPANDABLE
  {
    enum { ReturnValue = 0 };
  };

  template < typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPANDABLE < Expression<T, LHS, RHS, op_plus<T> > >
  {
    enum { ReturnValue = EXPRESSION_EXPANDABLE<LHS>::ReturnValue
                          + EXPRESSION_EXPANDABLE<RHS>::ReturnValue };
  };

  template < typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPANDABLE < Expression<T, LHS, RHS, op_minus<T> > >
  {
    enum { ReturnValue = EXPRESSION_EXPANDABLE<LHS>::ReturnValue
                          + EXPRESSION_EXPANDABLE<RHS>::ReturnValue };
  };

  template < typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPANDABLE < Expression<T, LHS, RHS, op_mult<T> > >
  {
    enum { ReturnValue = EXPRESSION_OPERATION_COUNT<LHS, op_plus>::ReturnValue
                          + EXPRESSION_OPERATION_COUNT<LHS, op_minus>::ReturnValue
                          + EXPRESSION_OPERATION_COUNT<RHS, op_plus>::ReturnValue
                          + EXPRESSION_OPERATION_COUNT<RHS, op_minus>::ReturnValue };
  };

  template < typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPANDABLE < Expression<T, LHS, RHS, op_div<T> > >
  {
    enum { ReturnValue = EXPRESSION_EXPANDABLE<LHS>::ERROR_EXPANDABLE_FOUND_op_div
                          + EXPRESSION_EXPANDABLE<RHS>::ERROR_EXPANDABLE_FOUND_op_div };
  };

  template <typename EXPR>
  long isExpandable(EXPR const &)
  {
    return EXPRESSION_EXPANDABLE<EXPR>::ReturnValue;
  }

/***************** Expand an expression by a factor: ****************/
  template <typename EXPR, typename FACTOR>
  struct EXPRESSION_EXPAND_BY_FACTOR
  {
    typedef Expression< ExpressionDefaultScalarType,
                          EXPR,
                          FACTOR,
                          op_mult <ExpressionDefaultScalarType>
                        >                 ResultType;
  };
  
  template <typename T, typename LHS, typename RHS, typename FACTOR>
  struct EXPRESSION_EXPAND_BY_FACTOR < Expression<T, LHS, RHS, op_plus<T> >, FACTOR>
  {
    typedef Expression< T,
                          typename EXPRESSION_EXPAND_BY_FACTOR< LHS, FACTOR >::ResultType,
                          typename EXPRESSION_EXPAND_BY_FACTOR< RHS, FACTOR >::ResultType,
                          op_plus<T>
                        >                 ResultType;
  };

  template <typename T, typename LHS, typename RHS, typename FACTOR>
  struct EXPRESSION_EXPAND_BY_FACTOR < Expression<T, LHS, RHS, op_minus<T> >, FACTOR>
  {
    typedef Expression< T,
                          typename EXPRESSION_EXPAND_BY_FACTOR< LHS, FACTOR >::ResultType,
                          typename EXPRESSION_EXPAND_BY_FACTOR< RHS, FACTOR >::ResultType,
                          op_minus<T>
                        >                 ResultType;
  };

  template <typename EXPR, typename FACTOR>
  typename EXPRESSION_EXPAND_BY_FACTOR<EXPR, FACTOR>::ResultType
  expand_by_factor(EXPR const &, FACTOR const &)
  {
    return typename EXPRESSION_EXPAND_BY_FACTOR<EXPR, FACTOR>::ResultType();
  }

/************************ if-else-metafunction: ****************/

  template <bool b, typename TRUE_TYPE, typename FALSE_TYPE>
  struct IF_THEN_ELSE
  {
    typedef TRUE_TYPE     ResultType;
  };

  template <typename TRUE_TYPE, typename FALSE_TYPE>
  struct IF_THEN_ELSE<false, TRUE_TYPE, FALSE_TYPE>
  {
    typedef FALSE_TYPE    ResultType;
  };

 /*********************** Type equality check: ******************/
  template <typename T1, typename T2>
  struct EQUALS
  {
    enum{ ReturnValue = 0 };
  };

  template <typename T>
  struct EQUALS<T,T>
  {
    enum{ ReturnValue = 1 };
  };

/************************ Expand: ****************/

  //first a tiny guard for expression_expand_impl with division:
  template <typename T, long test>
  struct EXPRESSION_EXPAND_IMPL_GUARD
  {
    typedef T       ResultType;
  };

  template <typename T>
  struct EXPRESSION_EXPAND_IMPL_GUARD <T, 0>
  {
    typedef typename T::ERROR_op_div_FOUND_NON_SCALAR_TYPE_IN_EXPRESSION_EXPAND      ResultType;
  };

  template <typename EXPR>
  struct EXPRESSION_EXPAND_IMPL 
  {
    typedef EXPR ResultType;
    enum { updated = 0 };
  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPAND_IMPL < Expression<T, LHS, RHS, op_plus<T> > >
  {
    typedef Expression< T,
                         typename EXPRESSION_EXPAND_IMPL<LHS>::ResultType,
                         typename EXPRESSION_EXPAND_IMPL<RHS>::ResultType,
                         op_plus<T>
                        >                   ResultType;
    enum { updated = EXPRESSION_EXPAND_IMPL<LHS>::updated + EXPRESSION_EXPAND_IMPL<RHS>::updated };
  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPAND_IMPL < Expression<T, LHS, RHS, op_minus<T> > >
  {
    typedef Expression< T,
                         typename EXPRESSION_EXPAND_IMPL<LHS>::ResultType,
                         typename EXPRESSION_EXPAND_IMPL<RHS>::ResultType,
                         op_minus<T>
                        >                   ResultType;
    enum { updated = EXPRESSION_EXPAND_IMPL<LHS>::updated + EXPRESSION_EXPAND_IMPL<RHS>::updated };
  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPAND_IMPL < Expression<T, LHS, RHS, op_mult<T> > >
  {
    typedef typename EXPRESSION_EXPAND_IMPL<LHS>::ResultType LHS_NEW;
    typedef typename EXPRESSION_EXPAND_IMPL<RHS>::ResultType RHS_NEW;

    typedef typename 
          IF_THEN_ELSE
          < (EXPRESSION_PLUS_MINUS_COUNT<LHS_NEW>::ReturnValue > 0),
            typename EXPRESSION_EXPAND_BY_FACTOR<LHS_NEW, RHS_NEW>::ResultType,
            typename IF_THEN_ELSE
                        < (EXPRESSION_PLUS_MINUS_COUNT<RHS_NEW>::ReturnValue > 0),
                          typename EXPRESSION_EXPAND_BY_FACTOR<RHS_NEW, LHS_NEW>::ResultType,
                          Expression<T, LHS_NEW, RHS_NEW, op_mult<T> >
                        >::ResultType
          >::ResultType                        ResultType;

    enum { updated = EXPRESSION_EXPAND_IMPL<LHS>::updated
                      + EXPRESSION_EXPAND_IMPL<RHS>::updated
                      + EXPRESSION_PLUS_MINUS_COUNT<LHS_NEW>::ReturnValue
                      + EXPRESSION_PLUS_MINUS_COUNT<RHS_NEW>::ReturnValue
          };

  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_EXPAND_IMPL < Expression<T, LHS, RHS, op_div<T> > >
  {
    typedef Expression< T,
                         typename EXPRESSION_EXPAND_IMPL<LHS>::ResultType,
                         typename EXPRESSION_EXPAND_IMPL_GUARD<RHS, EXPRESSION_IS_SCALAR<RHS>::ReturnValue >::ResultType,
                         op_div<T>
                        >                                      ResultType;
    enum{ updated =  EXPRESSION_EXPAND_IMPL<LHS>::updated };
  };

  //Expression-expand-loop:
  template <typename EXPR, long startval>
  struct EXPRESSION_EXPAND
  {
    typedef typename EXPRESSION_EXPAND< typename EXPRESSION_EXPAND_IMPL<EXPR>::ResultType,
                                           EXPRESSION_EXPAND_IMPL<EXPR>::updated
                                         >::ResultType                   ResultType; 
  };

  template <typename T, typename LHS, typename RHS, long startval>
  struct EXPRESSION_EXPAND < Expression<T, LHS, RHS, op_plus<T> >, startval >
  {
    typedef Expression < T,
                          typename EXPRESSION_EXPAND< LHS, 1>::ResultType,
                          typename EXPRESSION_EXPAND< RHS, 1>::ResultType,
                          op_plus<T>
                        >                                     ResultType;
  };

  template <typename T, typename LHS, typename RHS, long startval>
  struct EXPRESSION_EXPAND < Expression<T, LHS, RHS, op_minus<T> >, startval >
  {
    typedef Expression < T,
                          typename EXPRESSION_EXPAND< LHS, 1>::ResultType,
                          typename EXPRESSION_EXPAND< RHS, 1>::ResultType,
                          op_minus<T>
                        >                                     ResultType;
  };


  template <typename EXPR>
  struct EXPRESSION_EXPAND <EXPR, 0>
  {
    //typedef typename EXPRESSION_OPTIMIZER<EXPR>::ResultType                   ResultType; 
    typedef EXPR                  ResultType; 
  };

  template <typename EXPR>
  typename EXPRESSION_OPTIMIZER< typename EXPRESSION_EXPAND<EXPR>::ResultType >::ResultType
  expand_expression(EXPR const &)
  {
    return
      typename EXPRESSION_OPTIMIZER< typename EXPRESSION_EXPAND<EXPR>::ResultType >::ResultType();
  }

/************************ Determine Power of a variable: ****************/

  //must not be called for expressions with operators other than multiplication or division!
  template <typename EXPR, typename VARIABLE>
  struct EXPRESSION_POWER_OF_VARIABLE
  {
    enum { ReturnValue = 0 };
  };

  template <typename VARIABLE>
  struct EXPRESSION_POWER_OF_VARIABLE <VARIABLE, VARIABLE>
  {
    enum { ReturnValue = 1 };
  };

  template <typename T, typename LHS, typename RHS, typename VARIABLE>
  struct EXPRESSION_POWER_OF_VARIABLE < Expression<T, LHS, RHS, op_mult<T> >, VARIABLE>
  {
    enum { ReturnValue = EXPRESSION_POWER_OF_VARIABLE<LHS, VARIABLE>::ReturnValue
                          + EXPRESSION_POWER_OF_VARIABLE<RHS, VARIABLE>::ReturnValue };
  };

  template <typename T, typename LHS, typename RHS, typename VARIABLE>
  struct EXPRESSION_POWER_OF_VARIABLE < Expression<T, LHS, RHS, op_div<T> >, VARIABLE>
  {
    enum { ReturnValue = EXPRESSION_POWER_OF_VARIABLE<LHS, VARIABLE>::ReturnValue
                          - EXPRESSION_POWER_OF_VARIABLE<RHS, VARIABLE>::ReturnValue };
  };

  //prevent wrong usage:
  template <typename T, typename LHS, typename RHS, typename VARIABLE>
  struct EXPRESSION_POWER_OF_VARIABLE < Expression<T, LHS, RHS, op_plus<T> >, VARIABLE>
  {
    enum { ReturnValue = T::ERROR_op_plus_IN_POWER_OF_VARIABLE };
  };

  template <typename T, typename LHS, typename RHS, typename VARIABLE>
  struct EXPRESSION_POWER_OF_VARIABLE < Expression<T, LHS, RHS, op_minus<T> >, VARIABLE>
  {
    enum { ReturnValue = T::ERROR_op_minus_IN_POWER_OF_VARIABLE };
  };

  template <typename EXPR, typename VAR>
  long power_of_variable(EXPR const &, VAR const & )
  {
    return EXPRESSION_POWER_OF_VARIABLE<EXPR, VAR>::ReturnValue;
  }

/************************ Integration: ****************/

  //Expand the expression, then substitute appropriate bounds.

  //default case: integrate a scalar or variable (not equal INTVAR) only
  template <typename L_BOUND, typename U_BOUND, typename EXPR, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL
  {
    typedef Expression < ExpressionDefaultScalarType,
                          Expression < ExpressionDefaultScalarType,
                                       EXPR,
                                       U_BOUND,
                                       op_mult<ExpressionDefaultScalarType>
                                      >,
                          Expression < ExpressionDefaultScalarType,
                                       EXPR,
                                       L_BOUND,
                                       op_mult<ExpressionDefaultScalarType>
                                      >,
                          op_minus<ExpressionDefaultScalarType>
                         >                                                  ResultType;
  };

  //default case: integrate a scalar or variable (not equal INTVAR) only
  // + specialisation: if L_BOUND=0, throw it away!
  template <typename U_BOUND, typename EXPR, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < ScalarExpression<0>, U_BOUND, EXPR, INTVAR >
  {
    typedef  Expression < ExpressionDefaultScalarType,
                           EXPR,
                           U_BOUND,
                           op_mult<ExpressionDefaultScalarType>
                         >                                    ResultType;
  };

  //integrate INTVAR:
  template <typename L_BOUND, typename U_BOUND, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL <L_BOUND, U_BOUND, INTVAR, INTVAR>
  {
    typedef Expression < ExpressionDefaultScalarType,
                          Expression < ExpressionDefaultScalarType,
                                        Expression < ExpressionDefaultScalarType,
                                                    U_BOUND,
                                                    U_BOUND,
                                                    op_mult<ExpressionDefaultScalarType>
                                                    >,
                                        Expression < ExpressionDefaultScalarType,
                                                    L_BOUND,
                                                    L_BOUND,
                                                    op_mult<ExpressionDefaultScalarType>
                                                    >,
                                        op_minus<ExpressionDefaultScalarType>
                                      >,
                          ScalarExpression<2>,
                          op_div<ExpressionDefaultScalarType>
                          >                                                  ResultType;
  };

  //integrate INTVAR + specialisation: L_BOUND is zero!
  template <typename U_BOUND, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL <ScalarExpression<0>, U_BOUND, INTVAR, INTVAR>
  {
    typedef Expression < ExpressionDefaultScalarType,
                          Expression < ExpressionDefaultScalarType,
                                      U_BOUND,
                                      U_BOUND,
                                      op_mult<ExpressionDefaultScalarType>
                                      >,
                          ScalarExpression<2>,
                          op_div<ExpressionDefaultScalarType>
                          >                                                  ResultType;
  };

  //integrate both operands of '+' separately:
  template <typename L_BOUND, typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < L_BOUND,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_plus<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T,
                          typename EXPRESSION_INTEGRATE_IMPL< L_BOUND,
                                                                U_BOUND,
                                                                LHS,
                                                                INTVAR >::ResultType,
                          typename EXPRESSION_INTEGRATE_IMPL< L_BOUND,
                                                                U_BOUND,
                                                                RHS,
                                                                INTVAR >::ResultType,
                          op_plus<T>
                        >                                         ResultType;
  };

  //integrate both operands of '+' separately + resolve ambiguity for L_BOUND == 0
  template <typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < ScalarExpression<0>,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_plus<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T,
                          typename EXPRESSION_INTEGRATE_IMPL< ScalarExpression<0>,
                                                                U_BOUND,
                                                                LHS,
                                                                INTVAR >::ResultType,
                          typename EXPRESSION_INTEGRATE_IMPL< ScalarExpression<0>,
                                                                U_BOUND,
                                                                RHS,
                                                                INTVAR >::ResultType,
                          op_plus<T>
                        >                                         ResultType;
  };

  //integrate both operands of '-' separately:
  template <typename L_BOUND, typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < L_BOUND,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_minus<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T,
                          typename EXPRESSION_INTEGRATE_IMPL< L_BOUND,
                                                                U_BOUND,
                                                                LHS,
                                                                INTVAR >::ResultType,
                          typename EXPRESSION_INTEGRATE_IMPL< L_BOUND,
                                                                U_BOUND,
                                                                RHS,
                                                                INTVAR >::ResultType,
                          op_minus<T>
                        >                                         ResultType;
  };

  //integrate both operands of '-' separately + resolve ambiguity for L_BOUND == 0
  template <typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < ScalarExpression<0>,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_minus<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T,
                          typename EXPRESSION_INTEGRATE_IMPL< ScalarExpression<0>,
                                                                U_BOUND,
                                                                LHS,
                                                                INTVAR >::ResultType,
                          typename EXPRESSION_INTEGRATE_IMPL< ScalarExpression<0>,
                                                                U_BOUND,
                                                                RHS,
                                                                INTVAR >::ResultType,
                          op_minus<T>
                        >                                         ResultType;
  };

  //integrate a single expanded term:
  template <typename L_BOUND, typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < L_BOUND,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_mult<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T, LHS, RHS, op_mult<T> >                 IntegrandType;

    enum { PowerOfIntegrationVariable = EXPRESSION_POWER_OF_VARIABLE< IntegrandType,
                                                                       INTVAR >::ReturnValue };

    typedef Expression < T,
                          Expression < T,
                                       Expression < T,
                                                    typename POW< U_BOUND,
                                                                   PowerOfIntegrationVariable + 1
                                                                  >::ResultType,
                                                    typename EXPRESSION_SUBSTITUTE< IntegrandType,
                                                                                      INTVAR,
                                                                                      ScalarExpression<1>
                                                                                    >::ResultType,
                                                    op_mult<T>
                                                  >,
                                       Expression < T,
                                                    typename POW< L_BOUND,
                                                                   PowerOfIntegrationVariable + 1
                                                                  >::ResultType,
                                                    typename EXPRESSION_SUBSTITUTE< IntegrandType,
                                                                                      INTVAR,
                                                                                      ScalarExpression<1>
                                                                                    >::ResultType,
                                                    op_mult<T>
                                                  >,
                                        op_minus<T>
                                      >,
                          ScalarExpression< PowerOfIntegrationVariable + 1 >,
                          op_div<T>
                          >                                                  ResultType;
  };

  //specialisation: if lower bound is zero, throw it away:
  template <typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < ScalarExpression<0>,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_mult<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T, LHS, RHS, op_mult<T> >                 IntegrandType;

    enum { PowerOfIntegrationVariable = EXPRESSION_POWER_OF_VARIABLE< IntegrandType,
                                                                       INTVAR >::ReturnValue };

    typedef Expression < T,
                          Expression < T,
                                      typename POW< U_BOUND,
                                                      PowerOfIntegrationVariable + 1
                                                    >::ResultType,
                                      typename EXPRESSION_SUBSTITUTE< IntegrandType,
                                                                        INTVAR,
                                                                        ScalarExpression<1>
                                                                      >::ResultType,
                                      op_mult<T>
                                    >,
                          ScalarExpression< PowerOfIntegrationVariable + 1 >,
                          op_div<T>
                          >                                                  ResultType;
  };

  //integrate:
  // a tiny guard for expression_expand_impl with division:
  template <typename T, long test>
  struct EXPRESSION_INTEGRATE_IMPL_GUARD
  {
    typedef T       ResultType;
  };

  template <typename T>
  struct EXPRESSION_INTEGRATE_IMPL_GUARD <T, 0>
  {
    typedef typename T::ERROR_op_div_FOUND_NON_SCALAR_TYPE_IN_EXPRESSION_INTEGRATE_IMPL      ResultType;
  };

  template <typename L_BOUND, typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < L_BOUND,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_div<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T,
                          typename EXPRESSION_INTEGRATE_IMPL<L_BOUND, U_BOUND, LHS, INTVAR>::ResultType,
                          typename EXPRESSION_INTEGRATE_IMPL_GUARD<RHS, EXPRESSION_IS_SCALAR<RHS>::ReturnValue>::ResultType,
                          op_div<T>
                          >                                                  ResultType;
  };

  // + specialisation to resolve ambiguity at L_BOUND == 0:
  template <typename U_BOUND, typename T, typename LHS, typename RHS, typename INTVAR>
  struct EXPRESSION_INTEGRATE_IMPL < ScalarExpression<0>,
                                      U_BOUND,
                                      Expression <T, LHS, RHS, op_div<T> >,
                                      INTVAR
                                     >
  {
    typedef Expression < T,
                          typename EXPRESSION_INTEGRATE_IMPL<ScalarExpression<0>, U_BOUND, LHS, INTVAR>::ResultType,
                          typename EXPRESSION_INTEGRATE_IMPL_GUARD<RHS, EXPRESSION_IS_SCALAR<RHS>::ReturnValue>::ResultType,
                          op_div<T>
                          >                                                  ResultType;
  };


  template <typename L_BOUND, typename U_BOUND, typename EXPR, typename INTVAR>
  struct EXPRESSION_INTEGRATE
  {
    typedef typename EXPRESSION_OPTIMIZER
                < typename EXPRESSION_INTEGRATE_IMPL
                     <  L_BOUND,
                        U_BOUND,
                        typename EXPRESSION_EXPAND<EXPR>::ResultType,
                        INTVAR
                     >::ResultType
                >::ResultType                                               ResultType;
  };

  template <typename L_BOUND, typename U_BOUND, typename EXPR, typename INTVAR>
  struct EXPRESSION_INTEGRATE_DEBUG
  {
    typedef typename EXPRESSION_INTEGRATE_IMPL
                     <  L_BOUND,
                        U_BOUND,
                        typename EXPRESSION_EXPAND<EXPR>::ResultType,
                        INTVAR
                     >::ResultType                                          ResultType;
  };

  template <typename L_BOUND, typename U_BOUND, typename EXPR, typename INTVAR>
  typename EXPRESSION_INTEGRATE<L_BOUND, U_BOUND, EXPR, INTVAR>::ResultType
  integrate_expression(L_BOUND const &, U_BOUND const &, EXPR const &, INTVAR const &)
  {
    return typename EXPRESSION_INTEGRATE<L_BOUND, U_BOUND, EXPR, INTVAR>::ResultType();
  };

  template <typename L_BOUND, typename U_BOUND, typename EXPR, typename INTVAR>
  typename EXPRESSION_INTEGRATE_DEBUG<L_BOUND, U_BOUND, EXPR, INTVAR>::ResultType
  integrate_expression_debug(L_BOUND const &, U_BOUND const &, EXPR const &, INTVAR const &)
  {
    return typename EXPRESSION_INTEGRATE_DEBUG<L_BOUND, U_BOUND, EXPR, INTVAR>::ResultType();
  };


 /********************** Occurs ************************/
  //checks whether a particular KEY term occurs in an expression:
  //ReturnValue != 0 if KEY is found

  template <typename EXPR, typename KEY>
  struct EXPRESSION_OCCURS
  {
    enum { ReturnValue = 0 };
  };

  template <typename KEY>
  struct EXPRESSION_OCCURS <KEY, KEY>
  {
    enum { ReturnValue = 1 };
  };

  template <typename T, typename LHS, typename RHS, typename OP, typename KEY>
  struct EXPRESSION_OCCURS < Expression<T, LHS, RHS, OP> , KEY>
  {
    enum { ReturnValue = EXPRESSION_OCCURS<LHS, KEY>::ReturnValue + 
                          EXPRESSION_OCCURS<RHS, KEY>::ReturnValue };
  };


 /********************** Extract *************************/

  //similar to substitute, but removes only the first occurence of KEY and returns the result

  template <typename EXPR, typename KEY>
  struct EXPRESSION_EXTRACT
  {
    typedef ScalarExpression<0>         ResultType;       //Default: Key not found
  };

  template <typename KEY>
  struct EXPRESSION_EXTRACT <KEY, KEY>
  {
    typedef ScalarExpression<1>         ResultType;
  };

  template <typename T, typename KEY>
  struct EXPRESSION_EXTRACT < Expression<T, KEY, KEY, op_mult<T> >, KEY >
  {
    typedef KEY       ResultType;             //just replace one occurance of KEY!
  };

  template <typename T, typename LHS, typename KEY>
  struct EXPRESSION_EXTRACT < Expression<T, LHS, KEY, op_mult<T> >, KEY >
  {
    typedef LHS       ResultType;             //just replace one occurance of KEY!
  };

  template <typename T, typename RHS, typename KEY>
  struct EXPRESSION_EXTRACT < Expression<T, KEY, RHS, op_mult<T> >, KEY >
  {
    typedef RHS       ResultType;             //just replace one occurance of KEY!
  };

  template <typename T, typename LHS, typename RHS, typename KEY>
  struct EXPRESSION_EXTRACT < Expression<T, LHS, RHS, op_mult<T> >, KEY >
  {
    typedef typename IF_THEN_ELSE< (EXPRESSION_OCCURS<LHS, KEY>::ReturnValue != 0),
                                      Expression< T,
                                                  typename EXPRESSION_EXTRACT<LHS, KEY>::ResultType,
                                                  RHS,
                                                  op_mult<T>
                                                >,
                            typename IF_THEN_ELSE< (EXPRESSION_OCCURS<RHS, KEY>::ReturnValue != 0),
                                                    Expression< T,
                                                                LHS,
                                                                typename EXPRESSION_EXTRACT<RHS, KEY>::ResultType,
                                                                op_mult<T>
                                                              >,
                                                    ScalarExpression<0>
                                                  >::ResultType
                                    >::ResultType                           ResultType;
  };

  struct EXPRESSION_EXTRACT_ERROR_DIV_BY_NON_SCALAR {};

  template <typename T, typename LHS, typename RHS, typename KEY>
  struct EXPRESSION_EXTRACT < Expression<T, LHS, RHS, op_div<T> >, KEY >
  {
    typedef typename IF_THEN_ELSE< EXPRESSION_IS_SCALAR<RHS>::ReturnValue != 0,
                                      Expression< T,
                                                  typename EXPRESSION_EXTRACT<LHS, KEY>::ResultType,
                                                  RHS,
                                                  op_div<T>
                                                >,
                                      EXPRESSION_EXTRACT_ERROR_DIV_BY_NON_SCALAR
                                    >::ResultType                 ResultType;
  };

  template <typename T, typename LHS, typename RHS, typename KEY>
  struct EXPRESSION_EXTRACT < Expression<T, LHS, RHS, op_plus<T> >, KEY >
  {
    enum { error = T::ERROR_EXPRESSION_EXTRACT_FOUND_PLUS };
  };

  template <typename T, typename LHS, typename RHS, typename KEY>
  struct EXPRESSION_EXTRACT < Expression<T, LHS, RHS, op_minus<T> >, KEY >
  {
    enum { error = T::ERROR_EXPRESSION_EXTRACT_FOUND_MINUS };
  };

  /********************* improved differentiation *******************/

  template <typename DIFF_VAR, typename EXPR>
  struct EXPRESSION_DIFFERENTIATE_IMPL
  {
    //default: everything vanishes:
    typedef ScalarExpression<0>     ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LHS, typename RHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LHS, RHS, op_plus<T> > >
  {
    typedef Expression < T,
                          typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LHS>::ResultType,
                          typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, RHS>::ResultType,
                          op_plus<T>
                        >                                               ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LHS, typename RHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LHS, RHS, op_minus<T> > >
  {
    typedef Expression < T,
                          typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LHS>::ResultType,
                          typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, RHS>::ResultType,
                          op_minus<T>
                        >                                               ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LHS, typename RHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LHS, RHS, op_mult<T> > >
  {
    typedef Expression < T,
                          Expression < T,
                                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LHS>::ResultType,
                                       RHS,
                                       op_mult<T>
                                      >,
                          Expression < T,
                                       LHS,
                                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, RHS>::ResultType,
                                       op_mult<T>
                                      >,
                          op_plus<T>
                        >                                               ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LHS, typename RHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LHS, RHS, op_div<T> > >
  {
    // (u/v)' = (u'v - uv')/v^2

    typedef Expression < T,
                          Expression < T,
                                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LHS>::ResultType,
                                       RHS,
                                       op_mult<T>
                                      >,
                          Expression < T,
                                       LHS,
                                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, RHS>::ResultType,
                                       op_mult<T>
                                      >,
                          op_minus<T>
                        >                                               NumeratorType;

    typedef Expression < T,
                          RHS,
                          RHS,
                          op_mult<T>
                        >                                               DenominatorType;

    typedef Expression < T,
                          NumeratorType,
                          DenominatorType,
                          op_div<T>
                        >                                               ResultType;
  };

  //differentiate variables:
  template <typename DIFF_VAR>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, DIFF_VAR >
  {
    typedef ScalarExpression<1>               ResultType;
  };


  template <typename DIFF_VAR, long num, long denum,
              typename T1, long pow1,
              typename T2, long pow2,
              typename T3, long pow3,
              typename T4, long pow4
            >
  struct EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, CompoundExpression <num, denum,
                                                  T1, pow1,
                                                  T2, pow2,
                                                  T3, pow3,
                                                  T4, pow4> >
  {
    typedef ExpressionDefaultScalarType                         ScalarType;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow1>,
                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, T1>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1-1, T2, pow2, T3, pow3, T4, pow4>,
                         op_mult<ScalarType>
                        >                                         DiffType1;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow2>,
                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, T2>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1, T2, pow2-1, T3, pow3, T4, pow4>,
                         op_mult<ScalarType>
                        >                                         DiffType2;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow3>,
                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, T3>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1, T2, pow2, T3, pow3-1, T4, pow4>,
                         op_mult<ScalarType>
                        >                                         DiffType3;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow4>,
                       typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, T4>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1, T2, pow2, T3, pow3, T4, pow4-1>,
                         op_mult<ScalarType>
                        >                                         DiffType4;

    // use chain rule
    typedef Expression< ScalarType,
                          Expression<ScalarType,
                                     typename EXPRESSION_OPTIMIZER<DiffType1>::ResultType,
                                     typename EXPRESSION_OPTIMIZER<DiffType2>::ResultType,
                                     op_plus<ScalarType> >,
                          Expression<ScalarType,
                                     typename EXPRESSION_OPTIMIZER<DiffType3>::ResultType,
                                     typename EXPRESSION_OPTIMIZER<DiffType4>::ResultType,
                                     op_plus<ScalarType> >,
                          op_plus<ScalarType>
                        >                                       IntermediateType;

    typedef typename EXPRESSION_OPTIMIZER<IntermediateType>::ResultType      ResultType;
  };


  /* add some more cleverness to differentiation: 
     (mainly prevention of zeroes and ones)      */
  template <typename DIFF_VAR, typename T, typename LRHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LRHS, LRHS, op_plus<T> > >
  {
    typedef Expression <T,
                          ScalarExpression<2>,
                          typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LRHS>::ResultType,
                          op_mult<T>
                        >                                         ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LRHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LRHS, LRHS, op_minus<T> > >
  {
    typedef ScalarExpression<0>                                 ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LRHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LRHS, LRHS, op_mult<T> > >
  {
    typedef Expression <T,
                          ScalarExpression<2>,
                          Expression< T,
                                      LRHS,
                              typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LRHS>::ResultType,
                                      op_mult<T>
                                    >,
                          op_mult<T>
                        >                                         ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LRHS>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LRHS, LRHS, op_div<T> > >
  {
    typedef ScalarExpression<0>                                 ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LHS, long val>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LHS, ScalarExpression<val>, op_plus<T> > >
  {
    typedef typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LHS>::ResultType      ResultType;
  };

  template <typename DIFF_VAR, typename T, typename RHS, long val>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, ScalarExpression<val>, RHS, op_plus<T> > >
  {
    typedef typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, RHS>::ResultType      ResultType;
  };

  template <typename DIFF_VAR, typename T, long val1, long val2>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T,
                                                              ScalarExpression<val1>,
                                                              ScalarExpression<val2>,
                                                              op_plus<T>
                                                              >
                                        >
  {
    typedef ScalarExpression<0>      ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LHS, long val>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LHS, ScalarExpression<val>, op_minus<T> > >
  {
    typedef typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LHS>::ResultType      ResultType;
  };

  template <typename DIFF_VAR, typename T, typename RHS, long val>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, ScalarExpression<val>, RHS, op_minus<T> > >
  {
    typedef Expression < T,
                          ScalarExpression<-1>,
                          typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, RHS>::ResultType,
                          op_mult<T>
                        >                                   ResultType;
  };

  template <typename DIFF_VAR, typename T, long val1, long val2>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T,
                                                              ScalarExpression<val1>,
                                                              ScalarExpression<val2>,
                                                              op_minus<T>
                                                              >
                                        >
  {
    typedef ScalarExpression<0>      ResultType;
  };

  template <typename DIFF_VAR, typename T, typename LHS, long val>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, LHS, ScalarExpression<val>, op_mult<T> > >
  {
    typedef Expression<T,
                        typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, LHS>::ResultType,
                        ScalarExpression<val>,
                        op_mult<T>
                        >                   ResultType;
  };

  template <typename DIFF_VAR, typename T, typename RHS, long val>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T, ScalarExpression<val>, RHS, op_mult<T> > >
  {
    typedef Expression<T,
                        ScalarExpression<val>,
                        typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR, RHS>::ResultType,
                        op_mult<T>
                        >                   ResultType;
  };

  template <typename DIFF_VAR, typename T, long val1, long val2>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T,
                                                              ScalarExpression<val1>,
                                                              ScalarExpression<val2>,
                                                              op_mult<T>
                                                              >
                                        >
  {
    typedef ScalarExpression<0>      ResultType;
  };

  template <typename DIFF_VAR, typename T, long val>
  struct EXPRESSION_DIFFERENTIATE_IMPL < DIFF_VAR, Expression<T,
                                                              ScalarExpression<val>,
                                                              ScalarExpression<val>,
                                                              op_mult<T>
                                                              >
                                        >
  {
    typedef ScalarExpression<0>      ResultType;
  };

  /************ Public metafunction ************/

  template <typename DIFF_VAR, typename EXPR>
  struct EXPRESSION_DIFFERENTIATE
  {
/*    typedef typename DiffTraits<diffvar,
                                   typename EXPRESSION_EXPAND<EXPR>::ResultType
                                  >::ResultType                                   ResultType2;*/
    typedef typename EXPRESSION_DIFFERENTIATE_IMPL<DIFF_VAR,
                                                      typename EXPRESSION_EXPAND<EXPR>::ResultType
                                                     >::ResultType               ResultType2;
    typedef typename EXPRESSION_OPTIMIZER<ResultType2>::ResultType             ResultType;
  };

  template <typename DIFF_VAR, typename EXPR>
  typename EXPRESSION_DIFFERENTIATE<DIFF_VAR, EXPR>::ResultType
  expression_differentiate(EXPR const &)  
  {
    return typename EXPRESSION_DIFFERENTIATE<DIFF_VAR, EXPR>::ResultType();
  }


  //////////******************* TO COMPOUND *************************/////
  //translate an expression into compounded pieces

  template <typename EXPR, typename COMPOUNDTYPE>
  struct EXPRESSION_TO_COMPOUND
  {
    //use the Expression-Optimizer to do the job:
    typedef typename COMPOUNDTYPE::ERROR_COMPOUNDTYPE_IS_NOT_CONSTANT_1   ResultType;
  };

  //if compoundType is ScalarExpression<1>, no compounding:
  template <typename EXPR>
  struct EXPRESSION_TO_COMPOUND<EXPR, ScalarExpression<1> >
  {
    typedef typename EXPRESSION_OPTIMIZER<EXPR>::ResultType      ResultType;
  };

  template <typename T, typename LHS, typename RHS, typename OP,
              long val, typename T1, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND < Expression<T, LHS, RHS, OP >,
                                   CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef typename EXPRESSION_TO_COMPOUND < LHS, CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >::ResultType                                               LHSType;
    typedef typename EXPRESSION_TO_COMPOUND < RHS, CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >::ResultType                                               RHSType;

    typedef typename EXPRESSION_OPTIMIZER< Expression< T,
                                                         LHSType,
                                                         RHSType,
                                                         OP > 
                                            >::ResultType                     ResultType;
  };

  template < long val,
              long val2, typename T1, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND< ScalarExpression<val>,
                                  CompoundExpression<val2,val2, T1, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef CompoundExpression<val,1, T1, 0, T2, 0, T3, 0, T4, 1>             ResultType;
  };

  template <long val, typename T1, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND < T1,
                                   CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef CompoundExpression<val,val, T1, 1, T2, 0, T3, 0, T4, 0>             ResultType;
  };

  template <long val, typename T1, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND < T2,
                                   CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef CompoundExpression<val,val, T1, 0, T2, 1, T3, 0, T4, 0>             ResultType;
  };

  template <long val, typename T1, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND < T3,
                                   CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef CompoundExpression<val,val, T1, 0, T2, 0, T3, 1, T4, 0>             ResultType;
  };

  template <long val, typename T1, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND < T4,
                                   CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 1>             ResultType;
  };

  template <typename EXPR,
              long val, typename T1, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND< EXPR,
                                  CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef EXPR   ResultType;
  };

  //resolve ambiguities:
  template <typename T, typename LHS, typename RHS, typename OP,
              long val, typename T2, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND < Expression<T, LHS, RHS, OP >,
                                   CompoundExpression<val,val, Expression<T, LHS, RHS, OP >, 0, T2, 0, T3, 0, T4, 0> >
  {
    typedef CompoundExpression<val,val, Expression<T, LHS, RHS, OP >, 1, T2, 0, T3, 0, T4, 0>             ResultType;
  };

  template <typename T, typename LHS, typename RHS, typename OP,
              long val, typename T1, typename T3, typename T4>
  struct EXPRESSION_TO_COMPOUND < Expression<T, LHS, RHS, OP >,
                                   CompoundExpression<val,val, T1, 0, Expression<T, LHS, RHS, OP >, 0, T3, 0, T4, 0> >
  {
    typedef CompoundExpression<val,val, T1, 0, Expression<T, LHS, RHS, OP >, 1, T3, 0, T4, 0>             ResultType;
  };

  template <typename T, typename LHS, typename RHS, typename OP,
              long val, typename T1, typename T2, typename T4>
  struct EXPRESSION_TO_COMPOUND < Expression<T, LHS, RHS, OP >,
                                   CompoundExpression<val,val, T1, 0, T2, 0, Expression<T, LHS, RHS, OP >, 0, T4, 0> >
  {
    typedef CompoundExpression<val,val, T1, 0, T2, 0, Expression<T, LHS, RHS, OP >, 1, T4, 0>             ResultType;
  };

  template <typename T, typename LHS, typename RHS, typename OP,
              long val, typename T1, typename T2, typename T3>
  struct EXPRESSION_TO_COMPOUND < Expression<T, LHS, RHS, OP >,
                                   CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, Expression<T, LHS, RHS, OP >, 0> >
  {
    typedef CompoundExpression<val,val, T1, 0, T2, 0, T3, 0, Expression<T, LHS, RHS, OP >, 1>             ResultType;
  };


  template <typename EXPR, typename COMPOUND>
  typename EXPRESSION_TO_COMPOUND<EXPR, COMPOUND>::ResultType
  expression_to_compound(EXPR const & expr, COMPOUND const & comp)
  {
    return typename EXPRESSION_TO_COMPOUND<EXPR, COMPOUND>::ResultType();
  }




   //on a list, transform iteratively:
  template <typename EXPRLIST, typename COMPOUND>
  struct EXPRESSION_LIST_TO_COMPOUND
  {  };

  template <typename HEAD, typename TAIL, typename COMPOUND>
  struct EXPRESSION_LIST_TO_COMPOUND< TypeList<HEAD, TAIL>, COMPOUND>
  {
    typedef TypeList < typename EXPRESSION_TO_COMPOUND<HEAD, COMPOUND>::ResultType,
                        typename EXPRESSION_LIST_TO_COMPOUND<TAIL, COMPOUND>::ResultType
                      >                ResultType;
  };

  template <typename COMPOUND>
  struct EXPRESSION_LIST_TO_COMPOUND< TypeListEnd, COMPOUND>
  {
    typedef TypeListEnd               ResultType;
  };

  //convert Compound expression to full expression: (mainly testing purposes)
  template <typename Compound>
  struct COMPOUND_TO_FULL
  {
    typedef Compound        ResultType;    //argument is already non-compound-type
  };

  template <long num, long denum,
              typename EXPR1, long alpha1,
              typename EXPR2, long alpha2,
              typename EXPR3, long alpha3,
              typename EXPR4, long alpha4
            >
  struct COMPOUND_TO_FULL< CompoundExpression<num, denum, EXPR1, alpha1, EXPR2, alpha2, EXPR3, alpha3, EXPR4, alpha4> >
  {
    typedef Expression< ExpressionDefaultScalarType,
                         Expression< ExpressionDefaultScalarType,
                                     ScalarExpression<num>,
                                     ScalarExpression<denum>,
                                     op_div<ExpressionDefaultScalarType>
                                   >,
                         typename COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, alpha1, EXPR2, alpha2, EXPR3, alpha3, EXPR4, alpha4> >::ResultType,
                         op_mult<ExpressionDefaultScalarType>
                       >                                            ResultType;
  };

  template <typename EXPR1, long alpha1,
              typename EXPR2, long alpha2,
              typename EXPR3, long alpha3,
              typename EXPR4, long alpha4
            >
  struct COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, alpha1, EXPR2, alpha2, EXPR3, alpha3, EXPR4, alpha4> >
  {
    typedef Expression< ExpressionDefaultScalarType,
                         EXPR1,
                         typename COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, alpha1-1, EXPR2, alpha2, EXPR3, alpha3, EXPR4, alpha4> >::ResultType,
                         op_mult<ExpressionDefaultScalarType>
                       >                                            ResultType;
  };

  template <typename EXPR1, 
              typename EXPR2, long alpha2,
              typename EXPR3, long alpha3,
              typename EXPR4, long alpha4
            >
  struct COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, 0, EXPR2, alpha2, EXPR3, alpha3, EXPR4, alpha4> >
  {
    typedef Expression< ExpressionDefaultScalarType,
                         EXPR2,
                         typename COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, 0, EXPR2, alpha2-1, EXPR3, alpha3, EXPR4, alpha4> >::ResultType,
                         op_mult<ExpressionDefaultScalarType>
                       >                                            ResultType;
  };

  template <typename EXPR1, 
              typename EXPR2,
              typename EXPR3, long alpha3,
              typename EXPR4, long alpha4
            >
  struct COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, 0, EXPR2, 0, EXPR3, alpha3, EXPR4, alpha4> >
  {
    typedef Expression< ExpressionDefaultScalarType,
                         EXPR3,
                         typename COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, 0, EXPR2, 0, EXPR3, alpha3-1, EXPR4, alpha4> >::ResultType,
                         op_mult<ExpressionDefaultScalarType>
                       >                                            ResultType;
  };

  template <typename EXPR1, 
              typename EXPR2,
              typename EXPR3,
              typename EXPR4, long alpha4
            >
  struct COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, 0, EXPR2, 0, EXPR3, 0, EXPR4, alpha4> >
  {
    typedef Expression< ExpressionDefaultScalarType,
                         EXPR4,
                         typename COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, 0, EXPR2, 0, EXPR3, 0, EXPR4, alpha4-1> >::ResultType,
                         op_mult<ExpressionDefaultScalarType>
                       >                                            ResultType;
  };

  template <typename EXPR1, 
              typename EXPR2,
              typename EXPR3,
              typename EXPR4
            >
  struct COMPOUND_TO_FULL< CompoundExpression<1,1, EXPR1, 0, EXPR2, 0, EXPR3, 0, EXPR4, 0> >
  {
    typedef ScalarExpression<1>    ResultType;
  };

