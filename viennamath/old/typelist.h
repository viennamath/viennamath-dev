/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */

#ifndef ELFEM_TYPELIST_GUARD
#define ELFEM_TYPELIST_GUARD

#include "expression_header.h"


#define TYPELIST_1(T1) \
TypeList< T1 , TypeListEnd>
#define TYPELIST_2(T1, T2) \
TypeList< T1 , \
          TYPELIST_1( T2 ) \
        >
#define TYPELIST_3(T1, T2, T3) \
TypeList< T1 , \
          TYPELIST_2( T2 , T3 ) \
        >
#define TYPELIST_4(T1, T2, T3, T4) \
TypeList< T1 , \
          TYPELIST_3( T2 , T3, T4 ) \
        >
#define TYPELIST_5(T1, T2, T3, T4, T5) \
TypeList< T1 , \
          TYPELIST_4( T2 , T3, T4, T5 ) \
        >
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) \
TypeList< T1 , \
          TYPELIST_5( T2 , T3, T4, T5, T6 ) \
        >
#define TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
TypeList< T1 , \
          TYPELIST_6( T2 , T3, T4, T5, T6, T7 ) \
        >
#define TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
TypeList< T1 , \
          TYPELIST_7( T2 , T3, T4, T5, T6, T7, T8 ) \
        >
#define TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
TypeList< T1 , \
          TYPELIST_8( T2 , T3, T4, T5, T6, T7, T8, T9 ) \
        >
#define TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
TypeList< T1 , \
          TYPELIST_9( T2 , T3, T4, T5, T6, T7, T8, T9, T10 ) \
        >
#define TYPELIST_11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) \
TypeList< T1 , \
          TYPELIST_10( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11 ) \
        >
#define TYPELIST_12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) \
TypeList< T1 , \
          TYPELIST_11( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12 ) \
        >
#define TYPELIST_13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) \
TypeList< T1 , \
          TYPELIST_12( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13 ) \
        >
#define TYPELIST_14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) \
TypeList< T1 , \
          TYPELIST_13( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14 ) \
        >
#define TYPELIST_15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) \
TypeList< T1 , \
          TYPELIST_14( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15 ) \
        >
#define TYPELIST_16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) \
TypeList< T1 , \
          TYPELIST_15( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16 ) \
        >
#define TYPELIST_17(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) \
TypeList< T1 , \
          TYPELIST_16( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17 ) \
        >
#define TYPELIST_18(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) \
TypeList< T1 , \
          TYPELIST_17( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18 ) \
        >
#define TYPELIST_19(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) \
TypeList< T1 , \
          TYPELIST_18( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19 ) \
        >
#define TYPELIST_20(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) \
TypeList< T1 , \
          TYPELIST_19( T2 , T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20 ) \
        >


// Note: Due to problems with the comma-sign write it by hand:
#define TYPELIST_3x3( T11 , T12 , T13 , \
                      T21 , T22 , T23 , \
                      T31 , T32 , T33 )   \
TypeList < TYPELIST_3( T11 , T12 , T13 ), \
           TypeList < TYPELIST_3( T21 , T22 , T23 ), \
                      TypeList < TYPELIST_3( T31 , T32 , T33 ) , TypeListEnd \
                               > \
                    > \
         >

#define TYPELIST_2x2( T11 , T12,  \
                      T21 , T22 )   \
TypeList < TYPELIST_2( T11 , T12 ), \
           TypeList < TYPELIST_2( T21 , T22), \
                      TypeListEnd \
                    > \
         >

#define TYPELIST_1x1(T) TYPELIST_1(T)

namespace elfem{

  using expressions::EquationType;
  using expressions::IntegrationType;
  using expressions::Expression;
  using expressions::ScalarExpression;

  //Typelists:
  struct TypeListEnd
  {
    void print() { std::cout << "TypeListEnd" << std::endl; }
  };

  template <typename Head_, typename Tail_>
  struct TypeList
  {
    typedef Head_    ResultType;
    typedef Tail_    Tail;

    TypeList() {};
    //provide constructor for result-vectors, but omit it:
    template <typename VectorType>
    explicit TypeList(VectorType & result) {};

    //provide constructor for two result-vectors, but omit them:
    template <typename VectorType>
    explicit TypeList(VectorType & result1, VectorType & result2) {};


    template <typename IntDomain2, typename Integrand2, typename IntTag2>
    EquationType < TypeList<Head_, Tail_>,
                    IntegrationType <IntDomain2, Integrand2, IntTag2>
                  >
    operator=( IntegrationType <IntDomain2, Integrand2, IntTag2> const & rhs)
    {
        return EquationType < TypeList<Head_, Tail_>,
                                IntegrationType <IntDomain2, Integrand2, IntTag2>
                              > ();
    }
  
    template <typename ScalarType, typename LHS2, typename RHS2, typename OP2>
    EquationType < TypeList<Head_, Tail_>,
                    Expression <ScalarType, LHS2, RHS2, OP2>
                  >
    operator=( Expression <ScalarType, LHS2, RHS2, OP2> const & rhs)
    {
        return EquationType < TypeList<Head_, Tail_>,
                                Expression <ScalarType, LHS2, RHS2, OP2>
                              > ();
    }

    EquationType < TypeList<Head_, Tail_>,
                    ScalarExpression<0>
                  >
    operator=( ScalarExpression<0> const & rhs)
    {
        return EquationType < TypeList<Head_, Tail_>,
                               ScalarExpression<0>
                              > ();
    }

    template <typename Head2, typename Tail2>
    EquationType < TypeList<Head_, Tail_>,
                   TypeList<Head2, Tail2>
                  >
    operator=( TypeList<Head2, Tail2> const & rhs)
    {
        return EquationType < TypeList<Head_, Tail_>,
                              TypeList<Head2, Tail2>
                              > ();
    }

    void print() const
    {
      Head_().print();
      std::cout << ",";
      Tail().print();
    }
  };

  //number of entries in typelist:
  template <typename TypeList>
  struct ElementNum
  {
    enum{ ReturnValue = 1 + ElementNum<typename TypeList::Tail>::ReturnValue }; 
  };

  template <>
  struct ElementNum<TypeListEnd>
  {
    enum { ReturnValue = 0 };
  };

  //ElementAt:
  template <typename Typelist, int i>
  struct ElementAt
  {
    typedef typename ElementAt<typename Typelist::Tail, i-1>::Tail        Tail;
    typedef typename ElementAt<typename Typelist::Tail, i-1>::ResultType  ResultType;
  };

  template <typename T, typename U>
  struct ElementAt<TypeList<T,U>, 0>
  {
    typedef T   ResultType;
    typedef U   Tail;
  };

  //adds TL2 at end of TL1:
  template <typename TL1, typename TL2>
  struct AppendToTypeList
  {
    typedef TypeList< typename TL1::ResultType,
                       typename AppendToTypeList<typename TL1::Tail, TL2>::ResultType
                      >      ResultType;
  };

  template <typename TL2Head, typename TL2Tail>
  struct AppendToTypeList< TypeListEnd, TypeList<TL2Head, TL2Tail> >
  {
    typedef TypeList<TL2Head, TL2Tail>           ResultType;
  };

  //TL2 is "empty":
  template <typename TL1>
  struct AppendToTypeList< TL1, TypeListEnd>
  {
    typedef TL1           ResultType;
  };

  //TL2 is not a typelist yet:
  template <typename T>
  struct AppendToTypeList< TypeListEnd, T>
  {
    typedef TypeList<T, TypeListEnd>           ResultType;
  };


/*  TypeList< TypeList< Expr11,
                    TypeList< Expr12,
                              TypeList< Expr13,
                                        TypeListEnd
                                      >
                            >
                  >,
          TypeList< TypeList< Expr21,
                              TypeList< Expr22,
                                        TypeList< Expr23,
                                                  TypeListEnd
                                                >
                                      >
                            >,
                    TypeList< TypeList< Expr31,
                                        TypeList< Expr32,
                                                  TypeList< Expr33,
                                                            TypeListEnd
                                                          >
                                                >
                                      >,
                              TypeListEnd
                            >
                  >
        >*/

  //Typelist-Iterator:
  //iterates along a typelist with rowdim*coldim entries
  //for vectors, coldim is set to 1.
  //iteration is done one row after another
  //the public iterator:
  template <typename TList, long rowdim, long coldim = 1, long currentrow = 0, long currentcol = 0>
  struct TypeListIterator;

  template <typename TListTail, long rowdim, long coldim, long nextrow, long nextcol, bool rowcheck = (nextrow == rowdim), bool colcheck = (nextcol == coldim)>
  struct TypeListIteratorIncrementer
  {
    typedef TypeListIterator<TListTail, rowdim, coldim, nextrow - 1, nextcol>    ResultType;
  };

  //end of row:
  template <typename TListTail, long rowdim, long coldim, long nextrow, long nextcol>
  struct TypeListIteratorIncrementer <TListTail, rowdim, coldim, nextrow, nextcol, false, true>
  {
    typedef TypeListIterator<TListTail, rowdim, coldim, nextrow, 0>    ResultType;
  };

  //end of typelist:
  template <typename TListTail, long rowdim, long coldim, long nextrow, long nextcol>
  struct TypeListIteratorIncrementer <TListTail, rowdim, coldim, nextrow, nextcol, true, true>
  {
    typedef TypeListEnd    ResultType;
  };

  //the public iterator implementation:
  template <typename HeadType, typename TailType, long rowdim, long coldim, long currentrow, long currentcol>
  struct TypeListIterator <TypeList<HeadType, TailType>, rowdim, coldim, currentrow, currentcol>
  {
    typedef HeadType          ResultType;
    enum { rowindex = currentrow,
            colindex = currentcol,
            rownum = rowdim,
            colnum = coldim };

    typedef typename TypeListIteratorIncrementer<TailType, rowdim, coldim, currentrow + 1, currentcol + 1>::ResultType                     IncrementType;
  };

  //degenerate iterator: no typelist, only a single type.
  template <typename T, long rowdim, long coldim, long currentrow, long currentcol>
  struct TypeListIterator
  {
    typedef T          ResultType;
    enum { rowindex = 0,
            colindex = 0,
            rownum = 1,
            colnum = 1 };

    typedef TypeListEnd                     IncrementType;
  };


  //Helper for typelist-Setup:
  //Note: This function is necessary, since operator-overloads work on objects only - not on types!
  template <  typename Expr11, typename Expr12,
                typename Expr21, typename Expr22 >
  inline
  TYPELIST_4(Expr11, Expr12, Expr21, Expr22)
  makeExpressionList2x2(Expr11 const & e11, Expr12 const & e12,
                        Expr21 const & e21, Expr22 const & e22)
  {
    return TYPELIST_4(Expr11, Expr12, Expr21, Expr22)();
  }

  template <  typename Expr11, typename Expr12, typename Expr13,
                typename Expr21, typename Expr22, typename Expr23,
                typename Expr31, typename Expr32, typename Expr33>
  inline
  TYPELIST_9(Expr11, Expr12, Expr13, Expr21, Expr22, Expr23, Expr31, Expr32, Expr33)
  makeExpressionList3x3(Expr11 const & e11, Expr12 const & e12, Expr13 const & e13,
                        Expr21 const & e21, Expr22 const & e22, Expr23 const & e23,
                        Expr31 const & e31, Expr32 const & e32, Expr33 const & e33)
  {
    return TYPELIST_9(Expr11, Expr12, Expr13, Expr21, Expr22, Expr23, Expr31, Expr32, Expr33)();
  }

  template <  typename Expr11, typename Expr12, typename Expr13, typename Expr14,
                typename Expr21, typename Expr22, typename Expr23, typename Expr24,
                typename Expr31, typename Expr32, typename Expr33, typename Expr34,
                typename Expr41, typename Expr42, typename Expr43, typename Expr44>
  inline
  TYPELIST_16(Expr11, Expr12, Expr13, Expr14, Expr21, Expr22, Expr23, Expr24, Expr31, Expr32, Expr33, Expr34, Expr41, Expr42, Expr43, Expr44)
  makeExpressionList4x4(Expr11 const & e11, Expr12 const & e12, Expr13 const & e13, Expr14 const & e14,
                        Expr21 const & e21, Expr22 const & e22, Expr23 const & e23, Expr24 const & e24,
                        Expr31 const & e31, Expr32 const & e32, Expr33 const & e33, Expr34 const & e34,
                        Expr41 const & e41, Expr42 const & e42, Expr43 const & e43, Expr44 const & e44)
  {
    return TYPELIST_16(Expr11, Expr12, Expr13, Expr14, Expr21, Expr22, Expr23, Expr24, Expr31, Expr32, Expr33, Expr34, Expr41, Expr42, Expr43, Expr44)();
  }





  template <  typename Expr1, typename Expr2>
  inline
  TYPELIST_2(Expr1, Expr2)
  makeExpressionList2(Expr1 const & e1, Expr2 const & e2)
  {
    return TYPELIST_2(Expr1, Expr2)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3 >
  inline
  TYPELIST_3(Expr1, Expr2, Expr3)
  makeExpressionList3(Expr1 const & e1, Expr2 const & e2, Expr3 const & e3)
  {
    return TYPELIST_3(Expr1, Expr2, Expr3)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4 >
  inline
  TYPELIST_4(Expr1, Expr2, Expr3, Expr4)
  makeExpressionList4(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &)
  {
    return TYPELIST_4(Expr1, Expr2, Expr3, Expr4)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5 >
  inline
  TYPELIST_5(Expr1, Expr2, Expr3, Expr4, Expr5)
  makeExpressionList5(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &)
  {
    return TYPELIST_5(Expr1, Expr2, Expr3, Expr4, Expr5)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6 >
  inline
  TYPELIST_6(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6)
  makeExpressionList6(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &)
  {
    return TYPELIST_6(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7 >
  inline
  TYPELIST_7(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7)
  makeExpressionList7(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &)
  {
    return TYPELIST_7(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8 >
  inline
  TYPELIST_8(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8)
  makeExpressionList8(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &)
  {
    return TYPELIST_8(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9 >
  inline
  TYPELIST_9(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9)
  makeExpressionList9(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &)
  {
    return TYPELIST_9(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10 >
  inline
  TYPELIST_10(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10)
  makeExpressionList10(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &)
  {
    return TYPELIST_10(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11  >
  inline
  TYPELIST_11(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11)
  makeExpressionList11(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &)
  {
    return TYPELIST_11(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12  >
  inline
  TYPELIST_12(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12)
  makeExpressionList12(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &)
  {
    return TYPELIST_12(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13  >
  inline
  TYPELIST_13(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13)
  makeExpressionList13(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &)
  {
    return TYPELIST_13(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13, typename Expr14  >
  inline
  TYPELIST_14(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14)
  makeExpressionList14(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &, Expr14 const &)
  {
    return TYPELIST_14(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13, typename Expr14, typename Expr15  >
  inline
  TYPELIST_15(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15)
  makeExpressionList15(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &, Expr14 const &, Expr15 const &)
  {
    return TYPELIST_15(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13, typename Expr14, typename Expr15, typename Expr16  >
  inline
  TYPELIST_16(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16)
  makeExpressionList16(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &, Expr14 const &, Expr15 const &, Expr16 const &)
  {
    return TYPELIST_16(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13, typename Expr14, typename Expr15, typename Expr16, typename Expr17 >
  inline
  TYPELIST_17(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17)
  makeExpressionList17(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &, Expr14 const &, Expr15 const &, Expr16 const &, Expr17 const &)
  {
    return TYPELIST_17(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13, typename Expr14, typename Expr15, typename Expr16, typename Expr17, typename Expr18 >
  inline
  TYPELIST_18(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17, Expr18)
  makeExpressionList18(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &, Expr14 const &, Expr15 const &, Expr16 const &, Expr17 const &, Expr18 const &)
  {
    return TYPELIST_18(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17, Expr18)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13, typename Expr14, typename Expr15, typename Expr16, typename Expr17, typename Expr18, typename Expr19 >
  inline
  TYPELIST_19(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17, Expr18, Expr19)
  makeExpressionList19(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &, Expr14 const &, Expr15 const &, Expr16 const &, Expr17 const &, Expr18 const &, Expr19 const &)
  {
    return TYPELIST_19(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17, Expr18, Expr19)();
  }

  template <  typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6, typename Expr7, typename Expr8, typename Expr9, typename Expr10, typename Expr11, typename Expr12, typename Expr13, typename Expr14, typename Expr15, typename Expr16, typename Expr17, typename Expr18, typename Expr19, typename Expr20 >
  inline
  TYPELIST_20(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17, Expr18, Expr19, Expr20)
  makeExpressionList20(Expr1 const &, Expr2 const &, Expr3 const &, Expr4 const &, Expr5 const &, Expr6 const &, Expr7 const &, Expr8 const &, Expr9 const &, Expr10 const &, Expr11 const &, Expr12 const &, Expr13 const &, Expr14 const &, Expr15 const &, Expr16 const &, Expr17 const &, Expr18 const &, Expr19 const &, Expr20 const &)
  {
    return TYPELIST_20(Expr1, Expr2, Expr3, Expr4, Expr5, Expr6, Expr7, Expr8, Expr9, Expr10, Expr11, Expr12, Expr13, Expr14, Expr15, Expr16, Expr17, Expr18, Expr19, Expr20)();
  }

}

#endif
