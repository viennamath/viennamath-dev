/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */

/********** Mathematical Expressions for basis-function setup *************/
/********** Inspired by Todd Veldhuizen's expression-templates ************/
/********** Applied on polynomials for easier basis-function-setup ********/

#ifndef VIENNAMATH_EXPRESSION_GUARD
#define VIENNAMATH_EXPRESSION_GUARD

#include "typelist.h"

namespace viennamath{

  template <typename LHS_TYPE, typename RHS_TYPE, typename op_tag>
  struct op_traits
  {
    typedef typename op_tag::ERROR_CANNOT_DETERMINE_TYPE_OF_RESULT  error_type;
  };
  
  
  //sample overload for expr + expr (needs refinement...)
  template <typename LHS_TYPE, typename RHS_TYPE>
  struct op_traits<LHS_TYPE, RHS_TYPE, op_plus>
  {
    typedef ct_expr<typename LHS_TYPE::result_type,
                    LHS_TYPE,
                    RHS_TYPE,
                    op_plus>  result_type;
  };
  
  //tons of other overloads to follow...
  
  
  //operators:
  struct op_plus
  {
    template <typename LHS_TYPE, typename RHS_TYPE>
    static typename op_traits<LHS_TYPE, RHS_TYPE, op_plus>::result_type
    apply(LHS_TYPE const & lhs, RHS_TYPE const & rhs)
    { return lhs + rhs; }

    static void print()
    {
      std::cout << "+";
    }

  };

  template <typename T>
  struct op_minus
  {
    static T apply(T lhs, T rhs)
    { return lhs - rhs; }

    static void print()
    {
      std::cout << "-";
    }

  };

  template <typename T>
  struct op_mult
  {
    static T apply(T lhs, T rhs)
    { return lhs * rhs; }

    static void print()
    {
      std::cout << "*";
    }

  };

  template <typename T>
  struct op_div
  {
    static ExpressionDefaultScalarType apply(T lhs, T rhs)
    { return lhs / rhs; }

    static void print()
    {
      std::cout << "/";
    }

  };

  //helper struct for no operation:
  struct op_none
  {};

  struct op_and
  {
    template<typename T, typename U>
    static bool apply(T const & lhs, U const & rhs)
    { return lhs && rhs; }

    static void print()
    {
      std::cout << "&&";
    }
  };

  struct op_or
  {
    template<typename T, typename U>
    static bool apply(T const & lhs, U const & rhs)
    { return lhs || rhs; }

    static void print()
    {
      std::cout << "||";
    }
  };

  struct op_equal
  {
    template<typename T, typename U>
    static bool apply(T const & lhs, U const & rhs)
    { return lhs == rhs; }

    static void print()
    {
      std::cout << "==";
    }
  };

  struct op_unequal
  {
    template<typename T, typename U>
    static bool apply(T const & lhs, U const & rhs)
    { return lhs != rhs; }

    static void print()
    {
      std::cout << "!=";
    }
  };

  struct op_greaterthan
  {
    template<typename T, typename U>
    static bool apply(T const & lhs, U const & rhs)
    { return lhs > rhs; }

    static void print()
    {
      std::cout << ">";
    }
  };

  struct op_lessthan
  {
    template<typename T, typename U>
    static bool apply(T const & lhs, U const & rhs)
    { return lhs < rhs; }

    static void print()
    {
      std::cout << "<";
    }
  };

  //placeholders for basisfunction:
  //tags for differentiation of a basisfunction used in basefun-placeholder
  struct diff_none
  {
//     template <typename BasisFun, typename Point>
//     static typename Point::CoordType apply(BasisFun & bf, const Point & p) { return bf(p); }

    template <typename CellType, typename BasisFun, typename Point>
    static typename CellType::Configuration::CoordType apply(CellType const & cell, BasisFun const & bf, const Point & p)
      { return bf(p); }

/*    template <typename CellType, typename BasisFun, typename Point>
    static typename Point::CoordType apply(CellType const & cell, BasisFun const & bf, const Point & p, ThreeDimensionsTag)
      { return bf(p); }*/

    static void print()
    {
      //do nothing
    }

  };


#include "expression_types.h"


  //Helper for expression-struct:
  template <typename EXPR, typename Point>
  struct ExpressionHelper
  {
    static ExpressionDefaultScalarType apply(EXPR const & expr, Point const & p)
    {
      return expr(p);
    }

//     template <typename BasisFun>
//     static ExpressionDefaultScalarType apply(EXPR const & expr, BasisFun const & bf, Point const & p)
//     {
//       return expr(bf,p);
//     }
// 
//     template <typename CellType,typename BasisFun>
//     static ExpressionDefaultScalarType apply(EXPR const & expr, CellType & cell, BasisFun const & bf, Point const & p)
//     {
//       return expr(cell, bf, p);
//     }

//     template <typename BasisFun>
//     static ExpressionDefaultScalarType apply(EXPR const & expr, BasisFun const & bf1, BasisFun const & bf2, Point const & p)
//     {
//       return expr(bf1, bf2, p);
//     }

    template <typename CellType, typename BasisFun1, typename BasisFun2>
    static ExpressionDefaultScalarType apply(EXPR const & expr, CellType & cell, BasisFun1 const & bf1, BasisFun2 const & bf2, Point const & p)
    {
      return expr(cell, bf1, bf2, p);
    }

  };

  //special treatment for ExpressionDefaultScalarType:
  template <typename Point>
  struct ExpressionHelper<ExpressionDefaultScalarType, Point>
  {
//     static ExpressionDefaultScalarType apply(ExpressionDefaultScalarType expr, Point const & p)
//     {
//       return expr;
//     }
// 
//     template <typename BasisFun>
//     static ExpressionDefaultScalarType apply(ExpressionDefaultScalarType expr, BasisFun const & bf, Point const & p)
//     {
//       return expr;
//     }

//     template <typename CellType, typename BasisFun>
//     static ExpressionDefaultScalarType apply(ExpressionDefaultScalarType expr, CellType const & cell, BasisFun const & bf, Point const & p)
//     {
//       return expr;
//     }

//     template <typename BasisFun>
//     static ExpressionDefaultScalarType apply(ExpressionDefaultScalarType expr, BasisFun const & bf1, BasisFun const & bf2, Point const & p)
//     {
//       return expr;
//     }

    template <typename CellType, typename BasisFun1, typename BasisFun2>
    static ExpressionDefaultScalarType apply(ExpressionDefaultScalarType expr, CellType const & cell, BasisFun1 const & bf1, BasisFun2 const & bf2, Point const & p)
    {
      return expr;
    }

  };

  //Compounded expression:
  template <typename T, typename LHS, typename RHS, typename OP >
  class Expression
  {
    public:
      typedef T                   ScalarType;
      typedef OP                  OperatorType;
      typedef LHS                 LHSType;
      typedef RHS                 RHSType;

      explicit Expression() {} ;

      //for result:
      template <typename VectorType>
      Expression(VectorType & result) : lhs_(result), rhs_(result) {};

      //for two results:
      template <typename VectorType>
      Expression(VectorType & result1, VectorType & result2) : lhs_(result1, result2), rhs_(result1, result2) {};

      Expression(LHS const & lhs, RHS const & rhs) : lhs_(lhs), rhs_(rhs) {};

      //Evaluation of a compile-time scalar:
      T operator() () const
      {
        return OP::apply(lhs_(), rhs_());
      }

      template <typename Point>
      T operator() (const Point & p) const
      {
        return OP::apply(ExpressionHelper<LHS, Point>::apply(lhs_, p), ExpressionHelper<RHS, Point>::apply(rhs_, p));
      }

//       template <typename BasisFun, typename Point>
//       T operator() (const BasisFun & bf, const Point & p) const
//       {
//         return OP::apply(ExpressionHelper<LHS, Point>::apply(lhs_, bf, p),
//                           ExpressionHelper<RHS, Point>::apply(rhs_, bf, p));
//       }
// 
//       template <typename CellType, typename BasisFun, typename Point>
//       T operator() (CellType & cell, const BasisFun & bf, const Point & p) const
//       {
//         return OP::apply(ExpressionHelper<LHS, Point>::apply(lhs_, cell, bf, p),
//                           ExpressionHelper<RHS, Point>::apply(rhs_, cell, bf, p));
//       }

//       template <typename BasisFun1, typename BasisFun2, typename Point>
//       T operator() (const BasisFun1 & bf1, const BasisFun2 & bf2, const Point & p) const
//       {
//         return OP::apply(ExpressionHelper<LHS, Point>::apply(lhs_, bf1, bf2, p),
//                           ExpressionHelper<RHS, Point>::apply(rhs_, bf1, bf2, p));
//       }

      template <typename CellType, typename BasisFun1, typename BasisFun2, typename Point>
      T operator() (CellType & cell, const BasisFun1 & bf1, const BasisFun2 & bf2, const Point & p) const
      {
        return OP::apply(ExpressionHelper<LHS, Point>::apply(lhs_, cell, bf1, bf2, p),
                          ExpressionHelper<RHS, Point>::apply(rhs_, cell, bf1, bf2, p));
      }

      //support for analytic integration:
      double operator()(double dtdx00, double dtdx01,
                          double dtdx10, double dtdx11) const
      {
        return OP::apply(lhs_(dtdx00, dtdx01, dtdx10, dtdx11), rhs_(dtdx00, dtdx01, dtdx10, dtdx11));
      }

      double operator()(double dtdx00, double dtdx01, double dtdx02,
                          double dtdx10, double dtdx11, double dtdx12,
                          double dtdx20, double dtdx21, double dtdx22) const
      {
        return OP::apply(lhs_(dtdx00, dtdx01, dtdx02,
                               dtdx10, dtdx11, dtdx12,
                               dtdx20, dtdx21, dtdx22), rhs_(dtdx00, dtdx01, dtdx02,
                                                             dtdx10, dtdx11, dtdx12,
                                                             dtdx20, dtdx21, dtdx22));
      }

      template <typename CellType>
      double operator()(CellType & cell, AnalyticIntegrationTag const & ait) const
      {
        return OP::apply(lhs_(cell, ait), rhs_(cell, ait));
      }

      const LHS & getLHS() const { return lhs_; }
      const RHS & getRHS() const { return rhs_; }

      //debug info:
      void print() const
      {
        std::cout << "(";
        lhs_.print();
        OP::print();
        rhs_.print();
        std::cout << ")";
      }

/*      static void print()
      {
          std::cout << "(";
          LHS::print();
          OP::print();
          RHS::print();
          std::cout << ")";
      }*/
  
      template <typename Point, typename Cell>
      static double eval(Point & p, Cell & c, long i, long j)
      {
        return OP::apply(LHS::eval(p,c,i,j), RHS::eval(p,c,i,j));
      }
  
      //logical:
      template <typename U>
      LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_equal> operator==(U const & rhs) const
      {
        return LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_equal>(*this, rhs);
      }
  
      template <typename U>
      LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_unequal> operator!=(U const & rhs) const
      {
        return LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_unequal>(*this, rhs);
      }
  
      template <typename U>
      LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_lessthan> operator<(U const & rhs) const
      {
        return LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_lessthan>(*this, rhs);
      }

      template <typename U>
      LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_greaterthan> operator>(U const & rhs) const
      {
        return LogicalExpression< Expression<T, LHS, RHS, OP>, U, op_greaterthan>(*this, rhs);
      }





      //overload for assembly support:
      template <typename EXPR2, typename DOM2, typename INTTAG2>
      EquationType< Expression< ExpressionDefaultScalarType, LHS, RHS, OP>,
                    IntegrationType<EXPR2, DOM2, INTTAG2>
                  >
      operator=(IntegrationType<EXPR2, DOM2, INTTAG2> const & rhs)
      {
        return EquationType< Expression< ExpressionDefaultScalarType, LHS, RHS, OP>,
                              IntegrationType<EXPR2, DOM2, INTTAG2>
                            > ();
      }
  
      template <typename LHS2, typename RHS2, typename OP2>
      EquationType< Expression< ExpressionDefaultScalarType, LHS, RHS, OP>,
                    Expression< ExpressionDefaultScalarType, LHS2, RHS2, OP2>
                  >
      operator=( Expression< ExpressionDefaultScalarType, LHS2, RHS2, OP2> const & rhs)
      {
        return EquationType< Expression< ExpressionDefaultScalarType, LHS, RHS, OP>,
                              Expression< ExpressionDefaultScalarType, LHS2, RHS2, OP2>
                            > ();
      }
  
      EquationType < Expression< ExpressionDefaultScalarType, LHS, RHS, OP>,
                      ScalarExpression<0>
                    >
      operator=( ScalarExpression<0> const & rhs)
      {
          return EquationType < Expression< ExpressionDefaultScalarType, LHS, RHS, OP>,
                                ScalarExpression<0>
                                > ();
      }
  
      //for expressions arising from equations
      template <typename VectorType, typename Cell, typename BF1, typename BF2>
      static double evaluate(VectorType const & prev_res1, VectorType const & prev_res2, Cell & cell, BF1 const & bf1, BF2 const & bf2)
      {
        return OP::apply( LHS::evaluate(prev_res1, prev_res2, cell, bf1, bf2),
                            RHS::evaluate(prev_res1, prev_res2, cell, bf1, bf2) );
      }
  
      template <typename VectorType, typename Cell, typename BF1>
      static double evaluate(VectorType const & prev_res1, VectorType const & prev_res2, Cell & cell, BF1 const & bf1)
      {
        return OP::apply( LHS::evaluate(prev_res1, prev_res2, cell, bf1),
                            RHS::evaluate(prev_res1, prev_res2, cell, bf1) );
      }

    private:
      LHS lhs_;
      RHS rhs_;
  };

  /******************************************************************/
  /***************************** OPERATORS **************************/
  /******************************************************************/

  //#include "evalresult.h"
  #include "expression_operators.h"

  /******************************************************************/
  /************************** Expression-Optimizer*******************/
  /******************************************************************/
  #include "expression_optimizer.h"

  /******************************************************************/
  /*********************** Expression-Manipulation ******************/
  /******************************************************************/
  #include "expression_manipulation.h"

  /******************************************************************/
  /************************** Differentiation ***********************/
  /******************************************************************/

  namespace {
    template <bool condition>
    struct DiffDispatcher
    {
      static long const value = 0;
    };
  
    template <>
    struct DiffDispatcher<true>
    {
      static long const value = 1;
    };
  }

  //Helper traits class for operators:
  template <typename EXPR>
  struct OpTraits
  {
    typedef typename EXPR::OperatorType       OperatorType;
  };

  template <>
  struct OpTraits<ExpressionDefaultScalarType>
  {
    typedef op_none       OperatorType;
  };

  //Traits class for results:
  template <char diffvar, typename EXPR, typename op_tag>
  struct DiffTraits {};

  template <char diffvar, typename EXPR>
  struct DiffTraits<diffvar, EXPR, op_plus<typename EXPR::ScalarType> >
  {
    typedef typename EXPR::ScalarType         ScalarType;
    typedef typename EXPR::LHSType            LHSType;
    typedef typename EXPR::RHSType            RHSType;

    typedef Expression< ScalarType,
                          typename DiffTraits<diffvar, LHSType, typename OpTraits<LHSType>::OperatorType>::ResultType,
                          typename DiffTraits<diffvar, RHSType, typename OpTraits<RHSType>::OperatorType>::ResultType,
                          op_plus<typename EXPR::ScalarType>
                        >                                               ResultType;
  };

  template <char diffvar, typename EXPR>
  struct DiffTraits<diffvar, EXPR, op_minus<typename EXPR::ScalarType> >
  {
    typedef typename EXPR::ScalarType         ScalarType;
    typedef typename EXPR::LHSType            LHSType;
    typedef typename EXPR::RHSType            RHSType;

    typedef Expression< ScalarType,
                          typename DiffTraits<diffvar, LHSType, typename OpTraits<LHSType>::OperatorType>::ResultType,
                          typename DiffTraits<diffvar, RHSType, typename OpTraits<RHSType>::OperatorType>::ResultType,
                          op_minus<typename EXPR::ScalarType>
                        >                                               ResultType;
  };

  template <char diffvar, typename EXPR>
  struct DiffTraits<diffvar, EXPR, op_mult<typename EXPR::ScalarType> >
  {
    typedef typename EXPR::ScalarType         ScalarType;
    typedef typename EXPR::LHSType            LHSType;
    typedef typename EXPR::RHSType            RHSType;

    typedef Expression< ScalarType,
                          Expression <ScalarType,
                                      typename DiffTraits<diffvar, LHSType, typename OpTraits<LHSType>::OperatorType>::ResultType,
                                      RHSType,
                                      op_mult<ScalarType>
                                     >,
                          Expression <ScalarType,
                                      LHSType,
                                      typename DiffTraits<diffvar, RHSType, typename OpTraits<RHSType>::OperatorType>::ResultType,
                                      op_mult<ScalarType>
                                     >,
                          op_plus<typename EXPR::ScalarType>
                        >                                               ResultType;
  };

  template <char diffvar, typename EXPR>
  struct DiffTraits<diffvar, EXPR, op_div<typename EXPR::ScalarType> >
  {
    typedef typename EXPR::ScalarType         ScalarType;
    typedef typename EXPR::LHSType            LHSType;
    typedef typename EXPR::RHSType            RHSType;

    typedef Expression< ScalarType,
                          Expression <  ScalarType,
                                        Expression <  ScalarType,
                                                      typename DiffTraits<diffvar, LHSType, typename OpTraits<LHSType>::OperatorType>::ResultType,
                                                      RHSType,
                                                      op_mult<ScalarType>
                                                   >,
                                        Expression <  ScalarType,
                                                      LHSType,
                                                      typename DiffTraits<diffvar, RHSType, typename OpTraits<RHSType>::OperatorType>::ResultType,
                                                      op_mult<ScalarType>
                                                   >,
                                        op_minus<typename EXPR::ScalarType>
                                     >,
                          Expression <  ScalarType,
                                        RHSType,
                                        RHSType,
                                        op_mult<typename EXPR::ScalarType>
                                     >,
                          op_div<typename EXPR::ScalarType>
                        >                                               ResultType;
  };

  //Specialization for Scalar:
  template <char diffvar, long value_>
  struct DiffTraits<diffvar, ScalarExpression<value_> >
  {
    typedef ExpressionDefaultScalarType   ScalarType;
    typedef ScalarExpression<0>           ResultType;
  };

  template<char diffvar>
  struct DiffTraits<diffvar, ExpressionDefaultScalarType, op_none >
  {
    typedef ExpressionDefaultScalarType                         ScalarType;
    typedef ScalarExpression<0>                                 ResultType;
  };

  //Specialization for Variable:
  template <char diffvar, char coord>
  struct DiffTraits<diffvar, var<coord> >
  {
    typedef ExpressionDefaultScalarType                         ScalarType;
    typedef ScalarExpression<DiffDispatcher<diffvar == coord>::value>       ResultType;
  };

  //Specialization for compoundExpression:
  template <char diffvar, long num, long denum,
              typename T1, long pow1,
              typename T2, long pow2,
              typename T3, long pow3,
              typename T4, long pow4
            >
  struct DiffTraits<diffvar, CompoundExpression <num, denum,
                                                  T1, pow1,
                                                  T2, pow2,
                                                  T3, pow3,
                                                  T4, pow4> >
  {
    typedef ExpressionDefaultScalarType                         ScalarType;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow1>,
                                     typename DiffTraits<diffvar, T1>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1-1, T2, pow2, T3, pow3, T4, pow4>,
                         op_mult<ScalarType>
                        >                                         DiffType1;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow2>,
                                     typename DiffTraits<diffvar, T2>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1, T2, pow2-1, T3, pow3, T4, pow4>,
                         op_mult<ScalarType>
                        >                                         DiffType2;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow3>,
                                     typename DiffTraits<diffvar, T3>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1, T2, pow2, T3, pow3-1, T4, pow4>,
                         op_mult<ScalarType>
                        >                                         DiffType3;
    typedef Expression< ScalarType,
                         Expression< ScalarType,
                                     ScalarExpression<pow4>,
                                     typename DiffTraits<diffvar, T4>::ResultType,
                                     op_mult<ScalarType>
                                    >,
                         CompoundExpression <num, denum, T1, pow1, T2, pow2, T3, pow3, T4, pow4-1>,
                         op_mult<ScalarType>
                        >                                         DiffType4;

    // use chain rule
    typedef Expression< ScalarType,
                          Expression<ScalarType,
                                     DiffType1,
                                     DiffType2,
                                     op_plus<ScalarType> >,
                          Expression<ScalarType,
                                     DiffType3,
                                     DiffType4,
                                     op_plus<ScalarType> >,
                          op_plus<ScalarType>
                        >                                       IntermediateType;

    typedef typename EXPRESSION_OPTIMIZER<IntermediateType>::ResultType      ResultType;
  };

  template <char diffvar>
  struct DiffTraits<diffvar, CompoundUnused >
  {
    typedef ExpressionDefaultScalarType                         ScalarType;
    typedef ScalarExpression<0>       ResultType;
  };


  //forward declarations:
//   template <char diffvar, typename EXPR>
//   typename DiffTraits<diffvar, EXPR>::ResultType differentiate_deprecated(EXPR const & expr);
// 
//   template <char diffvar, long value_>
//   ScalarExpression<0> differentiate_deprecated(ScalarExpression<value_> const & se);
// 
//   template <char diffvar>
//   ScalarExpression<0> differentiate_deprecated(ExpressionDefaultScalarType value);
// 
//   template <char diffvar, char coord>
//   ScalarExpression<DiffDispatcher<diffvar == coord>::value> differentiate_deprecated(var<coord> const & v);

  //****************    Differentiation routines: **************************////

//   //plus:
//   template <char diffvar, typename EXPR>
//   typename DiffTraits<diffvar, EXPR>::ResultType differentiate_impl(EXPR const & expr, op_plus<typename EXPR::ScalarType> )
//   {
//     return differentiate_deprecated<diffvar>(expr.getLHS()) + differentiate_deprecated<diffvar>(expr.getRHS());
//   }
// 
//   //minus:
//   template <char diffvar, typename EXPR>
//   typename DiffTraits<diffvar, EXPR>::ResultType differentiate_impl(EXPR const & expr, op_minus<typename EXPR::ScalarType> )
//   {
//     return differentiate_deprecated<diffvar>(expr.getLHS()) - differentiate_deprecated<diffvar>(expr.getRHS());
//   }
// 
// 
//   //mult:
//   template <char diffvar, typename EXPR>
//   typename DiffTraits<diffvar, EXPR>::ResultType differentiate_impl(EXPR const & expr, op_mult<typename EXPR::ScalarType> )
//   {
//     return differentiate_deprecated<diffvar>(expr.getLHS()) * expr.getRHS() +
//             expr.getLHS() * differentiate_deprecated<diffvar>(expr.getRHS());
//   }
// 
// 
//   //div:
//   template <char diffvar, typename EXPR>
//   typename DiffTraits<diffvar, EXPR>::ResultType differentiate_impl(EXPR const & expr, op_div<typename EXPR::ScalarType> )
//   {
//     return ( differentiate_deprecated<diffvar>(expr.getLHS()) * expr.getRHS() -
//               expr.getLHS() * differentiate_deprecated<diffvar>(expr.getRHS()) ) /
//             ( expr.getRHS() * expr.getRHS() );
//   }


  //public interface:
  template <char diffvar, typename EXPR>
  typename DiffTraits<diffvar, EXPR>::ResultType differentiate_slowslow(EXPR const & expr)
  {
    //return differentiate_impl<diffvar, EXPR>(expr, typename EXPR::OperatorType());
    return typename DiffTraits<diffvar, EXPR>::ResultType();
  }

  template <char diffvar, typename EXPR>
  ScalarExpression<1> differentiate_slowslow2(EXPR const & expr)
  {
    //return differentiate_impl<diffvar, EXPR>(expr, typename EXPR::OperatorType());
    return ScalarExpression<1>();
  }

  //better engine:
  template <char diffvar, typename EXPR>
  typename EXPRESSION_OPTIMIZER< typename DiffTraits<diffvar, EXPR>::ResultType >::ResultType differentiate_slow(EXPR const & expr)
  {
    //return differentiate_impl<diffvar, EXPR>(expr, typename EXPR::OperatorType());
    return typename EXPRESSION_OPTIMIZER< 
                                      typename DiffTraits<diffvar, EXPR>::ResultType
                                    >::ResultType();
  }

  //optimised engine:
  template <typename DIFF_VAR, typename EXPR>
  typename EXPRESSION_DIFFERENTIATE<DIFF_VAR, EXPR>::ResultType
  differentiate(EXPR const & expr)
  {
    return typename EXPRESSION_DIFFERENTIATE<DIFF_VAR, EXPR>::ResultType();
  }

  //provide a Meta-Function only:
  template <char diffvar, typename EXPR>
  struct Differentiate
  {
    typedef typename EXPRESSION_OPTIMIZER< typename DiffTraits<diffvar, EXPR>::ResultType >::ResultType    ResultType;
  };

  //specializations:
//   template <char diffvar, long value_>
//   ScalarExpression<0> differentiate_deprecated(ScalarExpression<value_> const & se)
//   {
//     return ScalarExpression<0>();
//   }
// 
//   template <char diffvar>
//   ScalarExpression<0> differentiate_deprecated(ExpressionDefaultScalarType value)
//   {
//     return ScalarExpression<0>();
//   }
// 
//   template <char diffvar, char coord>
//   ScalarExpression<DiffDispatcher<diffvar == coord>::value> differentiate_deprecated(var<coord> const & v)
//   {
//     return ScalarExpression<DiffDispatcher<diffvar == coord>::value>();
//   };

  //differentiation tags for basisfunction object
  #include "difftags.h"

  //further expression-extensions:
  #include "expressions_operators.h"

  //extension for analytic integration
  #include "analytic_integration.h"

} //expressions

} //elfem

#endif
