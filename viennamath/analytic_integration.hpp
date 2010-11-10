/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */

// provides the necessary metafunctions and objects neeed for analytic integration.

// Included by expressions.h


  //post processing function: Eliminate divisons occuring from basisfunction-integrals. Get smallest common multiple of all denominators and denominators then.

  //Step 1: Get common denominator:
  template <typename EXPR>
  struct EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR
  {
    typedef typename EXPR::ERROR_ARGUMENT_IS_NOT_AN_EXPRESSION       ResultType;
  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR < Expression <T, LHS, RHS, op_minus<T> > >
  {
    enum { ReturnValue = LEAST_COMMON_MULTIPLE<
                              EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR<LHS>::ReturnValue,
                              EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR<RHS>::ReturnValue
                                               >::ReturnValue };
  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR < Expression <T, LHS, RHS, op_plus<T> > >
  {
    enum { ReturnValue = LEAST_COMMON_MULTIPLE<
                              EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR<LHS>::ReturnValue,
                              EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR<RHS>::ReturnValue
                                               >::ReturnValue };
  };

  //(ab)use known structure: (num/denum) * (dt_dx<> * dt_dx<>)
  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR < Expression <T, LHS, RHS, op_mult<T> > >
  {
    enum { ReturnValue = EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR<LHS>::ReturnValue };
  };

  template <typename T, long num, long denum>
  struct EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR < Expression <T, ScalarExpression<num>, ScalarExpression<denum>, op_div<T> > >
  {
    enum { ReturnValue = denum };
  };

  //Step 2: Extract the common prefactor and eliminate division-overhead:
  template <typename EXPR, long factor>
  struct EXPRESSION_REDUCE_DIVISIONS_REMOVE
  {
    typedef typename EXPR::ERROR_ARGUMENT_IS_NOT_AN_EXPRESSION       ResultType;
  };

  template <typename T, typename LHS, typename RHS, long factor>
  struct EXPRESSION_REDUCE_DIVISIONS_REMOVE < Expression <T, LHS, RHS, op_minus<T> >, factor >
  {
    typedef Expression <T,
                          typename EXPRESSION_REDUCE_DIVISIONS_REMOVE<LHS, factor>::ResultType,
                          typename EXPRESSION_REDUCE_DIVISIONS_REMOVE<RHS, factor>::ResultType,
                          op_minus<T>
                        >                                                 ResultType;
  };

  template <typename T, typename LHS, typename RHS, long factor>
  struct EXPRESSION_REDUCE_DIVISIONS_REMOVE < Expression <T, LHS, RHS, op_plus<T> >, factor >
  {
    typedef Expression <T,
                          typename EXPRESSION_REDUCE_DIVISIONS_REMOVE<LHS, factor>::ResultType,
                          typename EXPRESSION_REDUCE_DIVISIONS_REMOVE<RHS, factor>::ResultType,
                          op_plus<T>
                        >                                                 ResultType;
  };

  //again, (ab)use known structure:
  template <typename T, typename LHS, typename RHS, long factor>
  struct EXPRESSION_REDUCE_DIVISIONS_REMOVE < Expression <T, LHS, RHS, op_mult<T> >, factor >
  {
    typedef Expression <T,
                          typename EXPRESSION_REDUCE_DIVISIONS_REMOVE<LHS, factor>::ResultType,
                          RHS,
                          op_mult<T>
                        >                                               ResultType;
  };

  template <typename T, long num, long denum, long factor>
  struct EXPRESSION_REDUCE_DIVISIONS_REMOVE < Expression <T,
                                                            ScalarExpression<num>,
                                                            ScalarExpression<denum>,
                                                            op_div<T>
                                                          >,
                                                factor
                                              >
  {
    typedef ScalarExpression< num * (factor/denum) >                   ResultType;
  };

  //step 3: call step 1 and 2 and wrap division around
  template <typename EXPR>
  struct EXPRESSION_REDUCE_DIVISIONS
  {
    //typedef typename EXPR::ERROR_ARGUMENT_IS_NOT_A_SUM_NOR_A_DIFFERENCE   ResultType;
    typedef EXPR            ResultType;
  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_REDUCE_DIVISIONS < Expression <T, LHS, RHS, op_minus<T> > >
  {
    typedef Expression <T, LHS, RHS, op_minus<T> >                EXPR;

    enum { Denum = EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR<EXPR>::ReturnValue };
    typedef typename EXPRESSION_REDUCE_DIVISIONS_REMOVE<EXPR, Denum>::ResultType    InterType;
    typedef Expression < T,
                          typename EXPRESSION_OPTIMIZER<InterType>::ResultType,
                          ScalarExpression<Denum>,
                          op_div<T>
                         >                                              ResultType;
  };

  template <typename T, typename LHS, typename RHS>
  struct EXPRESSION_REDUCE_DIVISIONS < Expression <T, LHS, RHS, op_plus<T> > >
  {
    typedef Expression <T, LHS, RHS, op_minus<T> >                EXPR;

    enum { Denum = EXPRESSION_REDUCE_DIVISIONS_GET_DENOMINATOR<EXPR>::ReturnValue };
    typedef typename EXPRESSION_REDUCE_DIVISIONS_REMOVE<EXPR, Denum>::ResultType    InterType;
    typedef Expression < T,
                          typename EXPRESSION_OPTIMIZER<InterType>::ResultType,
                          ScalarExpression<Denum>,
                          op_div<T>
                         >                                              ResultType;
  };


  // Substitute correct terms (transformed derivatives!) for the given expression::

  // prototype that is only called if given expression is not (easily) analytically
  // integrable, i.e. there are space-dependent coefficients.
  template <typename EXPR, long dim>
  struct EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT
  {
    typedef typename EXPR::ERROR_EXPLICIT_SPACE_DEPENDENCE_OF_INTEGRAND_BUT_ANALYTIC_INTEGRATION   ResultType;
  };

  template <typename T, typename LHS, typename RHS, typename OP, long dim>
  struct EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT < Expression <T, LHS, RHS, OP>, dim >
  {
    typedef Expression < T,
                        typename EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT<LHS, dim>::ResultType,
                        typename EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT<RHS, dim>::ResultType,
                          OP >                             ResultType;
  };

  template <long i, long dim>
  struct EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT < basisfun<i, diff_none>, dim >
  {
    typedef basisfun<i, diff_none>                 ResultType;
  };

  template <long val, long dim>
  struct EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT < ScalarExpression<val>, dim >
  {
    typedef ScalarExpression<val>                 ResultType;
  };

  template <long i, long j, long dim>
  struct EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT < basisfun<i, diff<j> >, dim >
  {
    typedef Expression< ExpressionDefaultScalarType,
                          typename EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT
                                      < basisfun<i, diff<j> >, dim-1 >::ResultType,
                          Expression< ExpressionDefaultScalarType,
                                      basisfun<i, diff<dim-1> >,
                                      dt_dx<dim-1,j>,
                                      op_mult<ExpressionDefaultScalarType>
                                    >,
                          op_plus<ExpressionDefaultScalarType>
                        >                                                 ResultType;
  };

  //stop recursion:
  template <long i, long j>
  struct EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT < basisfun<i, diff<j> >, 1 >
  {
    typedef Expression< ExpressionDefaultScalarType,
                         basisfun<i, diff<0> >,
                         dt_dx<0,j>,
                         op_mult<ExpressionDefaultScalarType>
                         >                                                ResultType;
  };

  //interface function for testing:
//   template <typename EXPR>
//   typename EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT < EXPR >::ResultType
//   transform_to_reference_element(EXPR const & expr)
//   {
//     return typename EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT < EXPR >::ResultType();
//   }

  template <typename EXPR, typename BF1, typename BF2>
  struct EXPRESSION_SUBSTITUTE_BASISFUNCTIONS
  {
    typedef EXPR    ResultType;   //default: return expression
  };

  template <typename T, typename LHS, typename RHS, typename OP, typename BF1, typename BF2>
  struct EXPRESSION_SUBSTITUTE_BASISFUNCTIONS < Expression <T, LHS, RHS, OP>, BF1, BF2>
  {
    typedef Expression < T,
                          typename EXPRESSION_SUBSTITUTE_BASISFUNCTIONS <LHS, BF1, BF2>::ResultType,
                          typename EXPRESSION_SUBSTITUTE_BASISFUNCTIONS <RHS, BF1, BF2>::ResultType,
                          OP >                             ResultType;
  };

  template <typename BF1, typename BF2>
  struct EXPRESSION_SUBSTITUTE_BASISFUNCTIONS < basisfun<1, diff_none>, BF1, BF2>
  {
    typedef BF1                 ResultType;
  };

  template <typename BF1, typename BF2>
  struct EXPRESSION_SUBSTITUTE_BASISFUNCTIONS < basisfun<2, diff_none>, BF1, BF2>
  {
    typedef BF2                 ResultType;
  };

  template <long j, typename BF1, typename BF2>
  struct EXPRESSION_SUBSTITUTE_BASISFUNCTIONS < basisfun<1, diff<j> >, BF1, BF2>
  {
    typedef typename EXPRESSION_DIFFERENTIATE<var<j>, BF1>::ResultType            ResultType;
  };

  template <long j, typename BF1, typename BF2>
  struct EXPRESSION_SUBSTITUTE_BASISFUNCTIONS < basisfun<2, diff<j> >, BF1, BF2>
  {
    typedef typename EXPRESSION_DIFFERENTIATE<var<j>, BF2>::ResultType            ResultType;
  };


  template <typename EXPR, typename BF1, typename BF2>
  inline
  typename EXPRESSION_OPTIMIZER< typename EXPRESSION_SUBSTITUTE_BASISFUNCTIONS<EXPR, BF1, BF2 >::ResultType >::ResultType
  substituteBasisfunctions(EXPR const &, BF1 const &, BF2 const &)
  {
    return typename 
      EXPRESSION_OPTIMIZER< typename EXPRESSION_SUBSTITUTE_BASISFUNCTIONS<EXPR,
                                                                          BF1,
                                                                          BF2
                                                                          >::ResultType
                          >::ResultType();
  }


  //dt-dx helper:
  template <typename EXPR>
  struct DT_DX_REMOVER
  {
    typedef EXPR      ResultType;
  };

  template <typename T, typename LHS, typename RHS>
  struct DT_DX_REMOVER < Expression<T, LHS, RHS, op_mult<T> > >
  {
    typedef Expression<T,
                        typename DT_DX_REMOVER<LHS>::ResultType,
                        typename DT_DX_REMOVER<RHS>::ResultType,
                        op_mult<T>
                        >                                                 InterType;
    typedef typename EXPRESSION_OPTIMIZER<InterType>::ResultType        ResultType;
  };

  template <typename T, long i, long j, typename RHS>
  struct DT_DX_REMOVER < Expression<T, dt_dx<i,j>, RHS, op_mult<T> > >
  {
    typedef   RHS                                ResultType;
  };

  template <typename T, typename LHS, long i, long j>
  struct DT_DX_REMOVER < Expression<T, LHS, dt_dx<i,j>, op_mult<T> > >
  {
    typedef   LHS                                ResultType;
  };

  template <typename T, long i1, long j1, long i2, long j2>
  struct DT_DX_REMOVER < Expression<T, dt_dx<i1,j1>, dt_dx<i2,j2>, op_mult<T> > >
  {
    typedef   ScalarExpression<1>                ResultType;
  };

  //extractor
  template <typename EXPR>
  struct DT_DX_EXTRACTOR
  {
    typedef ScalarExpression<1>      ResultType;
  };

  template <typename T, typename LHS, typename RHS>
  struct DT_DX_EXTRACTOR < Expression<T, LHS, RHS, op_mult<T> > >
  {
    typedef Expression<T,
                        typename DT_DX_EXTRACTOR<LHS>::ResultType,
                        typename DT_DX_EXTRACTOR<RHS>::ResultType,
                        op_mult<T>
                        >                                                 ResultType;
    //typedef typename EXPRESSION_OPTIMIZER<InterType>::ResultType        ResultType;
  };

  template <typename T, long i, long j, typename RHS>
  struct DT_DX_EXTRACTOR < Expression<T, dt_dx<i,j>, RHS, op_mult<T> > >
  {
    typedef Expression<T,
                        dt_dx<i,j>,
                        typename DT_DX_EXTRACTOR<RHS>::ResultType,
                        op_mult<T>
                        >                                                 ResultType;
    //typedef typename EXPRESSION_OPTIMIZER<InterType>::ResultType        ResultType;
  };

  template <typename T, typename LHS, long i, long j>
  struct DT_DX_EXTRACTOR < Expression<T, LHS, dt_dx<i,j>, op_mult<T> > >
  {
    typedef Expression<T,
                        typename DT_DX_EXTRACTOR<LHS>::ResultType,
                        dt_dx<i,j>,
                        op_mult<T>
                        >                                                 ResultType;
    //typedef typename EXPRESSION_OPTIMIZER<InterType>::ResultType        ResultType;
  };

  template <typename T, long i1, long j1, long i2, long j2>
  struct DT_DX_EXTRACTOR < Expression<T, dt_dx<i1,j1>, dt_dx<i2,j2>, op_mult<T> > >
  {
    typedef Expression<T,
                        dt_dx<i1,j1>,
                        dt_dx<i2,j2>,
                        op_mult<T>
                        >                                                 ResultType;
  };


////////// Analytic Integration for all simplex elements:    ///////////////

  //helper: add/subtract fractionals:
  template <typename FRAC1, typename FRAC2>
  struct ADD_FRACTIONALS
  {};

  template <typename T, long n1, long d1, long n2, long d2>
  struct ADD_FRACTIONALS< Expression<T, ScalarExpression<n1>, ScalarExpression<d1>, op_div<T> >,
                           Expression<T, ScalarExpression<n2>, ScalarExpression<d2>, op_div<T> >
                         >
  {
    //be careful with fractional overflows!
    enum{ denumGcd = GREATEST_COMMON_DIVISOR<d1, d2>::ReturnValue };

    typedef Expression<T,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*(d2/denumGcd) + n2*(d1/denumGcd),
                                                             (d1/denumGcd)*d2>::Numerator>,
                        ScalarExpression<COMPRESS_FRACTIONAL<n1*(d2/denumGcd) + n2*(d1/denumGcd),
                                                             (d1/denumGcd)*d2>::Denominator>,
                        op_div<T> >                                 ResultType;
  };

  template <typename T, long n1, long d1>
  struct ADD_FRACTIONALS< Expression<T, ScalarExpression<n1>, ScalarExpression<d1>, op_div<T> >,
                           ScalarExpression<0>
                         >
  {
    typedef Expression<T, ScalarExpression<n1>, ScalarExpression<d1>, op_div<T> >                                 ResultType;
  };

  template <typename T, long n2, long d2>
  struct ADD_FRACTIONALS< ScalarExpression<0>,
                           Expression<T, ScalarExpression<n2>, ScalarExpression<d2>, op_div<T> >
                         >
  {
    typedef Expression<T, ScalarExpression<n2>, ScalarExpression<d2>, op_div<T> >                                 ResultType;
  };

  template <>
  struct ADD_FRACTIONALS< ScalarExpression<0>,
                           ScalarExpression<0>
                         >
  {
    typedef ScalarExpression<0>                               ResultType;
  };

  template <typename FractionalType, typename DtDxTailType>
  struct APPEND_DTDX_TAIL
  {
    typedef Expression< ExpressionDefaultScalarType,
                         FractionalType,
                         DtDxTailType,
                         op_mult<ExpressionDefaultScalarType>
                      >                                                        InterType;
    typedef typename EXPRESSION_OPTIMIZER<InterType>::ResultType            ResultType;
  };

  template <typename DtDxTailType>
  struct APPEND_DTDX_TAIL <ScalarExpression<0>, DtDxTailType>
  {
    typedef ScalarExpression<0>                                               ResultType;
  };

  template <typename EXPR>
  struct ZERO_REMOVER
  {
    typedef EXPR       ResultType;
  };

  template <typename T, typename LHS, typename OP>
  struct ZERO_REMOVER <Expression<T, LHS, ScalarExpression<0>, OP> >
  {
    typedef LHS                                                         ResultType;
  };

  template <typename T, typename RHS, typename OP>
  struct ZERO_REMOVER <Expression<T, ScalarExpression<0>, RHS, OP> >
  {
    typedef RHS                                                         ResultType;
  };

  template <typename T, typename OP>
  struct ZERO_REMOVER < Expression<T, ScalarExpression<0>, ScalarExpression<0>, OP> >
  {
    typedef ScalarExpression<0>                                        ResultType;
  };

  template <typename CellTag, typename EXPR>
  struct ANALYTIC_INTEGRATOR 
  {
    typedef typename EXPR::ERROR_INVALID_TRIANGLE_INTEGRATOR_ARGUMENT     ResultType;

  //benchmarking purposes:
//     typedef Expression<ExpressionDefaultScalarType,
//                         ScalarExpression<1>,
//                         var<0>,
//                         op_minus<ExpressionDefaultScalarType>
//                         >                                         OneMinusX;
//     typedef Expression<ExpressionDefaultScalarType,
//                         OneMinusX,
//                         var<1>,
//                         op_minus<ExpressionDefaultScalarType>
//                         >                                         OneMinusXMinusY;
//     typedef EXPR               IntegrandType;
// 
//     //benchmarking purposes:
//     typedef typename EXPRESSION_INTEGRATE<ScalarExpression<0>,
//                                              ScalarExpression<1>,
// /*                             typename EXPRESSION_INTEGRATE<ScalarExpression<0>,
//                                                              OneMinusX,*/
// /*                                 typename EXPRESSION_INTEGRATE<ScalarExpression<0>,
//                                                                  OneMinusXMinusY,*/
//                                                                  IntegrandType,
// /*                                                                 var<2> >::ResultType,*/
// /*                                                             var<1> >::ResultType,*/
//                                              var<0> >::ResultType         ResultType;

  };

  template <typename CellTag, typename T, typename LHS, typename RHS>
  struct ANALYTIC_INTEGRATOR < CellTag, Expression <T, LHS, RHS, op_plus<T> > >
  {
    typedef typename ADD_FRACTIONALS<
                         typename ANALYTIC_INTEGRATOR<CellTag, LHS>::ResultType,
                         typename ANALYTIC_INTEGRATOR<CellTag, RHS>::ResultType
                                        >::ResultType                         ResultType;
  };

//   template <typename CellTag, typename T, typename LHS, typename RHS>
//   struct ANALYTIC_INTEGRATOR < CellTag, Expression <T, LHS, RHS, op_minus<T> > >
//   {
//     typedef Expression< T,
//                          typename ANALYTIC_INTEGRATOR<CellTag, LHS>::ResultType,
//                          typename ANALYTIC_INTEGRATOR<CellTag, RHS>::ResultType,
//                          op_minus<T>
//                         >                                                     ResultType;
//   };

  //use derived formula for a simplex:
  template <typename SimplexTag, long num, long denum,
              typename EXPR1, long alpha1,
              typename EXPR2, long alpha2,
              typename EXPR3, long alpha3,
              typename EXPR4, long alpha4
             >
  struct ANALYTIC_INTEGRATOR < SimplexTag,
                                CompoundExpression <num, denum,
                                                    EXPR1, alpha1,
                                                    EXPR2, alpha2,
                                                    EXPR3, alpha3,
                                                    EXPR4, alpha4
                                                  > 
                              >
  {

    //use that monomial integrals over simplex is always of form 1/a for some a
//     enum{ SimplexDenominator = COMPRESS_FRACTIONAL<
//                                              FACTORIAL<alpha1>::ReturnValue *
//                                              FACTORIAL<alpha2>::ReturnValue *
//                                              FACTORIAL<alpha3>::ReturnValue *
//                                              FACTORIAL<alpha4>::ReturnValue,
//                                              FACTORIAL<alpha1 + alpha2 + alpha3 +
//                                                        alpha4 + SimplexTag::TopoLevel>::ReturnValue
//                                             >::Denominator };
    enum{ SimplexDenominator = FACTORIAL<alpha1 + alpha2 + alpha3 +
                                          alpha4 + SimplexTag::TopoLevel>::ReturnValue /
                               (FACTORIAL<alpha1>::ReturnValue * FACTORIAL<alpha2>::ReturnValue *
                                FACTORIAL<alpha3>::ReturnValue * FACTORIAL<alpha4>::ReturnValue) };


    typedef Expression< ExpressionDefaultScalarType,
                         ScalarExpression<COMPRESS_FRACTIONAL< num,
                                                               SimplexDenominator
                                                             >::Numerator
                                          >,
                         ScalarExpression<denum * COMPRESS_FRACTIONAL< num,
                                                               SimplexDenominator
                                                             >::Denominator
                                          >,
                         op_div<ExpressionDefaultScalarType>
                        >                                                     ResultType;
  };

  template <typename SimplexTag>
  struct ANALYTIC_INTEGRATOR < SimplexTag, ScalarExpression<0> >
  {
    typedef ScalarExpression<0>                 ResultType;
  };


  template <typename CellTag, typename EXPR, typename BF1, typename BF2>
  struct ANALYTIC_INTEGRATION_IMPL
  {
    //EXPR is now a single multiplicative term. Extract dt/dx-terms and integrate everything else

    //delegate the integration work:
    typedef typename BFStock<CellTag>::CompoundType                     CellCompound;

    //Extract everything but dt_dx:
    typedef typename DT_DX_REMOVER<EXPR>::ResultType                          IntegrandType1;
    typedef typename DT_DX_EXTRACTOR<EXPR>::ResultType                        DtDxTailType;

    //testing purposes:
//     typedef typename COMPOUND_TO_FULL<BF1>::ResultType     BFType1;
//     typedef typename COMPOUND_TO_FULL<BF2>::ResultType     BFType2;

    typedef typename EXPRESSION_SUBSTITUTE_BASISFUNCTIONS 
                        < IntegrandType1,
                          typename EXPRESSION_TO_COMPOUND<BF1, CellCompound>::ResultType,
                          typename EXPRESSION_TO_COMPOUND<BF2, CellCompound>::ResultType
                        >::ResultType                                               IntegrandType2;

    typedef typename EXPRESSION_OPTIMIZER
                          <typename EXPRESSION_EXPAND< IntegrandType2
                                                       >::ResultType
                          >::ResultType            IntegrandType3;

    typedef typename ANALYTIC_INTEGRATOR < CellTag,
                          IntegrandType3
                        >::ResultType                                               IntegratedType;

    //optimize the result and append dt_dx-tail:

    typedef typename APPEND_DTDX_TAIL< IntegratedType,
                                          DtDxTailType
                                        >::ResultType                           ResultType;
  };

  template <typename CellTag,
              typename T, typename LHS, typename RHS,
              typename BF1, typename BF2>
  struct ANALYTIC_INTEGRATION_IMPL <CellTag, Expression<T, LHS, RHS, op_plus<T> >, BF1, BF2 >
  {
    //just perform the integration separately for each term:
    typedef Expression<T,
                        typename ANALYTIC_INTEGRATION_IMPL<CellTag, LHS, BF1, BF2>::ResultType,
                        typename ANALYTIC_INTEGRATION_IMPL<CellTag, RHS, BF1, BF2>::ResultType,
                        op_plus<T> >                                        InterType;
    typedef typename ZERO_REMOVER<InterType>::ResultType                  ResultType;
  };

  template <typename CellTag,
              typename T, typename LHS, typename RHS,
              typename BF1, typename BF2>
  struct ANALYTIC_INTEGRATION_IMPL < CellTag, Expression<T, LHS, RHS, op_minus<T> >, BF1, BF2 >
  {
    //just perform the integration separately for each term:
    typedef Expression<T,
                        typename ANALYTIC_INTEGRATION_IMPL<CellTag, LHS, BF1, BF2>::ResultType,
                        typename ANALYTIC_INTEGRATION_IMPL<CellTag, RHS, BF1, BF2>::ResultType,
                        op_minus<T> >                                        InterType;
    typedef typename ZERO_REMOVER<InterType>::ResultType                  ResultType;
  };

  //the public interface:
  template <typename CellTag,
              typename EXPR,
              typename BF1, typename BF2>
  struct ANALYTIC_INTEGRATION
  {
    //default case: Transform this term (something like basisfun<1, diff_x>*basisfun<2,diff_y>) to the reference cell and pass it to ANALYTIC_INTEGRATION_IMPL
    typedef typename EXPRESSION_TRANSFORM_TO_REFERENCE_ELEMENT<EXPR, CellTag::TopoLevel>::ResultType       TransformedType;

    typedef typename ANALYTIC_INTEGRATION_IMPL<CellTag,
                                       typename EXPRESSION_EXPAND<TransformedType>::ResultType,
                                       BF1, BF2>::ResultType                    ResultType;
  };

  template <typename CellTag,
              typename T, typename LHS, typename RHS,
              typename BF1, typename BF2>
  struct ANALYTIC_INTEGRATION < CellTag, Expression<T, LHS, RHS, op_plus<T> >, BF1, BF2 >
  {
    //just perform the integration separately for each term:
    typedef Expression<T,
                        typename ANALYTIC_INTEGRATION<CellTag, LHS, BF1, BF2>::ResultType,
                        typename ANALYTIC_INTEGRATION<CellTag, RHS, BF1, BF2>::ResultType,
                        op_plus<T> >                                        ResultType;
  };

  template <typename CellTag,
              typename T, typename LHS, typename RHS,
              typename BF1, typename BF2>
  struct ANALYTIC_INTEGRATION< CellTag, Expression<T, LHS, RHS, op_minus<T> >, BF1, BF2 >
  {
    //just perform the integration separately for each term:
    typedef Expression<T,
                        typename ANALYTIC_INTEGRATION<CellTag, LHS, BF1, BF2>::ResultType,
                        typename ANALYTIC_INTEGRATION<CellTag, RHS, BF1, BF2>::ResultType,
                        op_minus<T> >                                        ResultType;
  };
