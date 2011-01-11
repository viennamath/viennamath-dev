/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */


 //overloaded operators for types in expressions.h


  /****************** Expression with Expression: *************************/

  template <typename T, typename L_LHS, typename L_RHS, typename L_OP, typename R_LHS, typename R_RHS, typename R_OP>
  inline Expression< T,
                      Expression<T, L_LHS, L_RHS, L_OP>,
                      Expression<T, R_LHS, R_RHS, R_OP>,
                      op_plus<T>
                     >
  operator+(Expression<T, L_LHS, L_RHS, L_OP> const & lhs, Expression<T, R_LHS, R_RHS, R_OP> const & rhs)
  {
    return Expression< T,
                        Expression<T, L_LHS, L_RHS, L_OP>,
                        Expression<T, R_LHS, R_RHS, R_OP>,
                        op_plus<T>
                      >(lhs, rhs);
  }

  template <typename T, typename L_LHS, typename L_RHS, typename L_OP, typename R_LHS, typename R_RHS, typename R_OP>
  inline Expression<T,
                      Expression<T, L_LHS, L_RHS, L_OP>,
                      Expression<T, R_LHS, R_RHS, R_OP>,
                      op_minus<T>
                    >
  operator-(Expression<T, L_LHS, L_RHS, L_OP> const & lhs, Expression<T, R_LHS, R_RHS, R_OP> const & rhs)
  {
    return Expression< T,
                        Expression<T, L_LHS, L_RHS, L_OP>,
                        Expression<T, R_LHS, R_RHS, R_OP>,
                        op_minus<T>
                      >(lhs, rhs);
  }

  template <typename T, typename L_LHS, typename L_RHS, typename L_OP, typename R_LHS, typename R_RHS, typename R_OP>
  inline Expression< T,
                      Expression<T, L_LHS, L_RHS, L_OP>,
                      Expression<T, R_LHS, R_RHS, R_OP>,
                      op_mult<T>
                    >
  operator*(Expression<T, L_LHS, L_RHS, L_OP> const & lhs, Expression<T, R_LHS, R_RHS, R_OP> const & rhs)
  {
    return Expression< T,
                        Expression<T, L_LHS, L_RHS, L_OP>,
                        Expression<T, R_LHS, R_RHS, R_OP>,
                        op_mult<T>
                      >(lhs, rhs);
  }

  template <typename T, typename L_LHS, typename L_RHS, typename L_OP, typename R_LHS, typename R_RHS, typename R_OP>
  inline Expression< T,
                      Expression<T, L_LHS, L_RHS, L_OP>,
                      Expression<T, R_LHS, R_RHS, R_OP>,
                      op_div<T>
                    >
  operator/(Expression<T, L_LHS, L_RHS, L_OP> const & lhs, Expression<T, R_LHS, R_RHS, R_OP> const & rhs)
  {
    return Expression< T,
                        Expression<T, L_LHS, L_RHS, L_OP>,
                        Expression<T, R_LHS, R_RHS, R_OP>,
                        op_div<T>
                      >(lhs, rhs);
  }

  /****************** Expression with Variable: *************************/
  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      EXPR,
                      var<coord>,
                      op_plus<typename EXPR::ScalarType>
                    >
  operator+(EXPR const & expr, var<coord> const & v)
  {
    return Expression< typename EXPR::ScalarType,
                        EXPR,
                        var<coord>,
                        op_plus<typename EXPR::ScalarType>
                      >(expr, v);
  }

  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      var<coord>,
                      EXPR,
                      op_plus<typename EXPR::ScalarType>
                    >
  operator+(var<coord> const & v, EXPR const & expr)
  {
    return Expression< typename EXPR::ScalarType,
                        var<coord>,
                        EXPR,
                        op_plus<typename EXPR::ScalarType>
                      >(v, expr);
  }


  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      EXPR,
                      var<coord>,
                      op_minus<typename EXPR::ScalarType>
                    >
  operator-(EXPR const & expr, var<coord> const & v)
  {
    return Expression< typename EXPR::ScalarType,
                        EXPR,
                        var<coord>,
                        op_minus<typename EXPR::ScalarType>
                      >(expr, v);
  }

  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      var<coord>,
                      EXPR,
                      op_minus<typename EXPR::ScalarType>
                    >
  operator-(var<coord> const & v, EXPR const & expr)
  {
    return Expression< typename EXPR::ScalarType,
                        var<coord>,
                        EXPR,
                        op_minus<typename EXPR::ScalarType>
                      >(v, expr);
  }

  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      EXPR,
                      var<coord>,
                      op_mult<typename EXPR::ScalarType>
                    >
  operator*(EXPR const & expr, var<coord> const & v)
  {
    return Expression< typename EXPR::ScalarType,
                        EXPR,
                        var<coord>,
                        op_mult<typename EXPR::ScalarType>
                      >(expr, v);
  }

  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      var<coord>,
                      EXPR,
                      op_mult<typename EXPR::ScalarType>
                    >
  operator*(var<coord> const & v, EXPR const & expr)
  {
    return Expression< typename EXPR::ScalarType,
                        var<coord>,
                        EXPR,
                        op_mult<typename EXPR::ScalarType>
                      >(v, expr);
  }


  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      EXPR,
                      var<coord>,
                      op_div<typename EXPR::ScalarType>
                    >
  operator/(EXPR const & expr, var<coord> const & v)
  {
    return Expression< typename EXPR::ScalarType,
                        EXPR,
                        var<coord>,
                        op_div<typename EXPR::ScalarType>
                      >(expr, v);
  }

  template <typename EXPR, unsigned long coord>
  inline Expression< typename EXPR::ScalarType,
                      var<coord>,
                      EXPR,
                      op_div<typename EXPR::ScalarType>
                    >
  operator/(var<coord> const & v, EXPR const & expr)
  {
    return Expression< typename EXPR::ScalarType,
                        var<coord>,
                        EXPR,
                        op_div<typename EXPR::ScalarType>
                      >(v, expr);
  }

  /****************** ScalarExpression with Variable: *************************/
  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ScalarExpression<value>,
                      var<coord>,
                      op_plus<ExpressionDefaultScalarType>
                    >
  operator+(ScalarExpression<value> const & se, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ScalarExpression<value>,
                        var<coord>,
                        op_plus<ExpressionDefaultScalarType>
                      >(se, v);
  }

  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ScalarExpression<value>,
                      op_plus<ExpressionDefaultScalarType>
                    >
  operator+(var<coord> const & v, ScalarExpression<value> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ScalarExpression<value>,
                        op_plus<ExpressionDefaultScalarType>
                      >(v, se);
  }

  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ScalarExpression<value>,
                      var<coord>,
                      op_minus<ExpressionDefaultScalarType>
                    >
  operator-(ScalarExpression<value> const & se, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ScalarExpression<value>,
                        var<coord>,
                        op_minus<ExpressionDefaultScalarType>
                      >(se, v);
  }

  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ScalarExpression<value>,
                      op_minus<ExpressionDefaultScalarType>
                    >
  operator-(var<coord> const & v, ScalarExpression<value> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ScalarExpression<value>,
                        op_minus<ExpressionDefaultScalarType>
                      >(v, se);
  }


  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ScalarExpression<value>,
                      var<coord>,
                      op_mult<ExpressionDefaultScalarType>
                    >
  operator*(ScalarExpression<value> const & se, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ScalarExpression<value>,
                        var<coord>,
                        op_mult<ExpressionDefaultScalarType>
                      >(se, v);
  }

  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ScalarExpression<value>,
                      op_mult<ExpressionDefaultScalarType>
                    >
  operator*(var<coord> const & v, ScalarExpression<value> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ScalarExpression<value>,
                        op_mult<ExpressionDefaultScalarType>
                      >(v, se);
  }

  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ScalarExpression<value>,
                      var<coord>,
                      op_div<ExpressionDefaultScalarType>
                    >
  operator/(ScalarExpression<value> const & se, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ScalarExpression<value>,
                        var<coord>,
                        op_div<ExpressionDefaultScalarType>
                      >(se, v);
  }

  template <long value, unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ScalarExpression<value>,
                      op_div<ExpressionDefaultScalarType>
                    >
  operator/(var<coord> const & v, ScalarExpression<value> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ScalarExpression<value>,
                        op_div<ExpressionDefaultScalarType>
                      >(v, se);
  }


  /*********************** Variable with Variable: ******************/
  template <unsigned long coordLHS, unsigned long coordRHS>
  inline Expression< ExpressionDefaultScalarType,
                      var<coordLHS>,
                      var<coordRHS>,
                      op_plus<ExpressionDefaultScalarType>
                    >
  operator+(var<coordLHS> const & v1, var<coordRHS> const & v2)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coordLHS>,
                        var<coordRHS>,
                        op_plus<ExpressionDefaultScalarType>
                      >(v1, v2);
  }

  template <unsigned long coordLHS, unsigned long coordRHS>
  inline Expression< ExpressionDefaultScalarType,
                      var<coordLHS>,
                      var<coordRHS>,
                      op_minus<ExpressionDefaultScalarType>
                    >
  operator-(var<coordLHS> const & v1, var<coordRHS> const & v2)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coordLHS>,
                        var<coordRHS>,
                        op_minus<ExpressionDefaultScalarType>
                      >(v1, v2);
  }

  template <unsigned long coordLHS, unsigned long coordRHS>
  inline Expression< ExpressionDefaultScalarType,
                      var<coordLHS>,
                      var<coordRHS>,
                      op_mult<ExpressionDefaultScalarType>
                    >
  operator*(var<coordLHS> const & v1, var<coordRHS> const & v2)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coordLHS>,
                        var<coordRHS>,
                        op_mult<ExpressionDefaultScalarType>
                      >(v1, v2);
  }

  template <unsigned long coordLHS, unsigned long coordRHS>
  inline Expression< ExpressionDefaultScalarType,
                      var<coordLHS>,
                      var<coordRHS>,
                      op_div<ExpressionDefaultScalarType>
                    >
  operator/(var<coordLHS> const & v1, var<coordRHS> const & v2)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coordLHS>,
                        var<coordRHS>,
                        op_div<ExpressionDefaultScalarType>
                      >(v1, v2);
  }


  // basisfunction with expression:
  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_plus<T>
                     >
  operator+(basisfun<num, diff_tag> const & bf, Expression<T, LHS, RHS, OP> const & e)
  {
    return Expression<  T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_plus<T>
                     > (bf, e);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_plus<T>
                     >
  operator+(Expression<T, LHS, RHS, OP> const & e, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_plus<T>
                     > (e, bf);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_minus<T>
                     >
  operator-(basisfun<num, diff_tag> const & bf, Expression<T, LHS, RHS, OP> const & e)
  {
    return Expression<  T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_minus<T>
                     > (bf, e);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_minus<T>
                     >
  operator-(Expression<T, LHS, RHS, OP> const & e, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_minus<T>
                     > (e, bf);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_mult<T>
                     >
  operator*(basisfun<num, diff_tag> const & bf, Expression<T, LHS, RHS, OP> const & e)
  {
    return Expression<  T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_mult<T>
                     > (bf, e);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_mult<T>
                     >
  operator*(Expression<T, LHS, RHS, OP> const & e, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_mult<T>
                     > (e, bf);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_div<T>
                     >
  operator/(basisfun<num, diff_tag> const & bf, Expression<T, LHS, RHS, OP> const & e)
  {
    return Expression<  T,
                       basisfun<num, diff_tag>,
                       Expression<T, LHS, RHS, OP>,
                       op_div<T>
                     > (bf, e);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long num, typename diff_tag>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_div<T>
                     >
  operator/(Expression<T, LHS, RHS, OP> const & e, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  T,
                       Expression<T, LHS, RHS, OP>,
                       basisfun<num, diff_tag>,
                       op_div<T>
                     > (e, bf);
  }

  //basisfunction with basisfunction:
  template <long num1, typename diff_tag1, long num2, typename diff_tag2>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(basisfun<num1, diff_tag1> const & bf1, basisfun<num2, diff_tag2> const & bf2)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_plus<ExpressionDefaultScalarType>
                     > (bf1, bf2);
  }

  template <long num1, typename diff_tag1, long num2, typename diff_tag2>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(basisfun<num1, diff_tag1> const & bf1, basisfun<num2, diff_tag2> const & bf2)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_minus<ExpressionDefaultScalarType>
                     > (bf1, bf2);
  }

  template <long num1, typename diff_tag1, long num2, typename diff_tag2>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(basisfun<num1, diff_tag1> const & bf1, basisfun<num2, diff_tag2> const & bf2)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_mult<ExpressionDefaultScalarType>
                     > (bf1, bf2);
  }

  template <long num1, typename diff_tag1, long num2, typename diff_tag2>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(basisfun<num1, diff_tag1> const & bf1, basisfun<num2, diff_tag2> const & bf2)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num1, diff_tag1>,
                       basisfun<num2, diff_tag2>,
                       op_div<ExpressionDefaultScalarType>
                     > (bf1, bf2);
  }

  //basisfunction with variable:
  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(basisfun<num, diff_tag> const & bf, var<coord> const & v)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_plus<ExpressionDefaultScalarType>
                     > (bf, v);
  }

  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(var<coord> const & v, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_plus<ExpressionDefaultScalarType>
                     > (v, bf);
  }

  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(basisfun<num, diff_tag> const & bf, var<coord> const & v)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_minus<ExpressionDefaultScalarType>
                     > (bf, v);
  }

  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(var<coord> const & v, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_minus<ExpressionDefaultScalarType>
                     > (v, bf);
  }

  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(basisfun<num, diff_tag> const & bf, var<coord> const & v)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_mult<ExpressionDefaultScalarType>
                     > (bf, v);
  }

  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(var<coord> const & v, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_mult<ExpressionDefaultScalarType>
                     > (v, bf);
  }

  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(basisfun<num, diff_tag> const & bf, var<coord> const & v)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       var<coord>,
                       op_div<ExpressionDefaultScalarType>
                     > (bf, v);
  }

  template <unsigned long coord, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(var<coord> const & v, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       var<coord>,
                       basisfun<num, diff_tag>,
                       op_div<ExpressionDefaultScalarType>
                     > (v, bf);
  }


  //basisfunction with ScalarExpression:
  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(basisfun<num, diff_tag> const & bf, ScalarExpression<value_> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_plus<ExpressionDefaultScalarType>
                     > (bf, se);
  }

  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(ScalarExpression<value_> const & se, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_plus<ExpressionDefaultScalarType>
                     > (se, bf);
  }

  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(basisfun<num, diff_tag> const & bf, ScalarExpression<value_> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_minus<ExpressionDefaultScalarType>
                     > (bf, se);
  }

  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(ScalarExpression<value_> const & se, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_minus<ExpressionDefaultScalarType>
                     > (se, bf);
  }

  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(basisfun<num, diff_tag> const & bf, ScalarExpression<value_> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_mult<ExpressionDefaultScalarType>
                     > (bf, se);
  }

  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(ScalarExpression<value_> const & se, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_mult<ExpressionDefaultScalarType>
                     > (se, bf);
  }

  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(basisfun<num, diff_tag> const & bf, ScalarExpression<value_> const & se)
  {
    return Expression< ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ScalarExpression<value_>,
                       op_div<ExpressionDefaultScalarType>
                     > (bf, se);
  }

  template <long value_, long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(ScalarExpression<value_> const & se, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value_>,
                       basisfun<num, diff_tag>,
                       op_div<ExpressionDefaultScalarType>
                     > (se, bf);
  }

  //ScalarExpression with ScalarExpression:
  template <long lvalue_, long rvalue_>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(ScalarExpression<lvalue_> const & sel, ScalarExpression<rvalue_> const & ser)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_plus<ExpressionDefaultScalarType>
                     > (sel, ser);
  }

  template <long lvalue_, long rvalue_>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(ScalarExpression<lvalue_> const & sel, ScalarExpression<rvalue_> const & ser)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_minus<ExpressionDefaultScalarType>
                     > (sel, ser);
  }

  template <long lvalue_, long rvalue_>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(ScalarExpression<lvalue_> const & sel, ScalarExpression<rvalue_> const & ser)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_mult<ExpressionDefaultScalarType>
                     > (sel, ser);
  }

  template <long lvalue_, long rvalue_>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(ScalarExpression<lvalue_> const & sel, ScalarExpression<rvalue_> const & ser)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<lvalue_>,
                       ScalarExpression<rvalue_>,
                       op_div<ExpressionDefaultScalarType>
                     > (sel, ser);
  }

  //Expression with ScalarExpression:
  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_plus<T>
                     >
  operator+(Expression<T, LHS, RHS, OP> const & expr, ScalarExpression<value_> const & se)
  {
    return Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_plus<T>
                     > (expr, se);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_plus<T>
                     >
  operator+(ScalarExpression<value_> const & se, Expression<T, LHS, RHS, OP> const & expr)
  {
    return Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_plus<T>
                     > (se, expr);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_minus<T>
                     >
  operator-(Expression<T, LHS, RHS, OP> const & expr, ScalarExpression<value_> const & se)
  {
    return Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_minus<T>
                     > (expr, se);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_minus<T>
                     >
  operator-(ScalarExpression<value_> const & se, Expression<T, LHS, RHS, OP> const & expr)
  {
    return Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_minus<T>
                     > (se, expr);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_mult<T>
                     >
  operator*(Expression<T, LHS, RHS, OP> const & expr, ScalarExpression<value_> const & se)
  {
    return Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_mult<T>
                     > (expr, se);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_mult<T>
                     >
  operator*(ScalarExpression<value_> const & se, Expression<T, LHS, RHS, OP> const & expr)
  {
    return Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_mult<T>
                     > (se, expr);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_div<T>
                     >
  operator/(Expression<T, LHS, RHS, OP> const & expr, ScalarExpression<value_> const & se)
  {
    return Expression < T,
                       Expression<T, LHS, RHS, OP>,
                       ScalarExpression<value_>,
                       op_div<T>
                     > (expr, se);
  }

  template <typename T, typename LHS, typename RHS, typename OP, long value_>
  inline Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_div<T>
                     >
  operator/(ScalarExpression<value_> const & se, Expression<T, LHS, RHS, OP> const & expr)
  {
    return Expression < T,
                       ScalarExpression<value_>,
                       Expression<T, LHS, RHS, OP>,
                       op_div<T>
                     > (se, expr);
  }

  /************************ Usability functions *********************/

  // provide easier expression setup by using simple scalars instead
  // of the ScalarExpression-Wrapper:

  // scalar with var:
  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      var<coord>,
                      op_plus<ExpressionDefaultScalarType>
                    >
  operator+(ExpressionDefaultScalarType scalar, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        var<coord>,
                        op_plus<ExpressionDefaultScalarType>
                      > (scalar, v);
  }

  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ExpressionDefaultScalarType,
                      op_plus<ExpressionDefaultScalarType>
                    >
  operator+(var<coord> const & v, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ExpressionDefaultScalarType,
                        op_plus<ExpressionDefaultScalarType>
                      > (v, scalar);
  }


  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      var<coord>,
                      op_minus<ExpressionDefaultScalarType>
                    >
  operator-(ExpressionDefaultScalarType scalar, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        var<coord>,
                        op_minus<ExpressionDefaultScalarType>
                      > (scalar, v);
  }

  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ExpressionDefaultScalarType,
                      op_minus<ExpressionDefaultScalarType>
                    >
  operator-(var<coord> const & v, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ExpressionDefaultScalarType,
                        op_minus<ExpressionDefaultScalarType>
                      > (v, scalar);
  }


  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      var<coord>,
                      op_mult<ExpressionDefaultScalarType>
                    >
  operator*(ExpressionDefaultScalarType scalar, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        var<coord>,
                        op_mult<ExpressionDefaultScalarType>
                      > (scalar, v);
  }

  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ExpressionDefaultScalarType,
                      op_mult<ExpressionDefaultScalarType>
                    >
  operator*(var<coord> const & v, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ExpressionDefaultScalarType,
                        op_mult<ExpressionDefaultScalarType>
                      > (v, scalar);
  }


  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      var<coord>,
                      op_div<ExpressionDefaultScalarType>
                    >
  operator/(ExpressionDefaultScalarType scalar, var<coord> const & v)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        var<coord>,
                        op_div<ExpressionDefaultScalarType>
                      > (scalar, v);
  }

  template <unsigned long coord>
  inline Expression< ExpressionDefaultScalarType,
                      var<coord>,
                      ExpressionDefaultScalarType,
                      op_div<ExpressionDefaultScalarType>
                    >
  operator/(var<coord> const & v, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        var<coord>,
                        ExpressionDefaultScalarType,
                        op_div<ExpressionDefaultScalarType>
                      > (v, scalar);
  } 

  // scalar with expression:
  template <typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      op_plus<ExpressionDefaultScalarType>
                    >
  operator+(ExpressionDefaultScalarType scalar, Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        op_plus<ExpressionDefaultScalarType>
                      > (scalar, e);
  }

  template <typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      ExpressionDefaultScalarType,
                      op_plus<ExpressionDefaultScalarType>
                    >
  operator+(Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        ExpressionDefaultScalarType,
                        op_plus<ExpressionDefaultScalarType>
                      > (e, scalar);
  }

  template <typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      op_minus<ExpressionDefaultScalarType>
                    >
  operator-(ExpressionDefaultScalarType scalar, Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        op_minus<ExpressionDefaultScalarType>
                      > (scalar, e);
  }

  template <typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      ExpressionDefaultScalarType,
                      op_minus<ExpressionDefaultScalarType>
                    >
  operator-(Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        ExpressionDefaultScalarType,
                        op_minus<ExpressionDefaultScalarType>
                      > (e, scalar);
  }

  template <typename ExpressionDefaultScalarType, typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      op_mult<ExpressionDefaultScalarType>
                    >
  operator*(ExpressionDefaultScalarType scalar, Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        op_mult<ExpressionDefaultScalarType>
                      > (scalar, e);
  }

  template <typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      ExpressionDefaultScalarType,
                      op_mult<ExpressionDefaultScalarType>
                    >
  operator*(Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        ExpressionDefaultScalarType,
                        op_mult<ExpressionDefaultScalarType>
                      > (e, scalar);
  }

  template <typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      op_div<ExpressionDefaultScalarType>
                    >
  operator/(ExpressionDefaultScalarType scalar, Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e)
  {
    return Expression< ExpressionDefaultScalarType,
                        ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        op_div<ExpressionDefaultScalarType>
                      > (scalar, e);
  }

  template <typename LHS, typename RHS, typename OP >
  inline Expression< ExpressionDefaultScalarType,
                      Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                      ExpressionDefaultScalarType,
                      op_div<ExpressionDefaultScalarType>
                    >
  operator/(Expression<ExpressionDefaultScalarType, LHS, RHS, OP> const & e, ExpressionDefaultScalarType scalar)
  {
    return Expression< ExpressionDefaultScalarType,
                        Expression<ExpressionDefaultScalarType, LHS, RHS, OP>,
                        ExpressionDefaultScalarType,
                        op_div<ExpressionDefaultScalarType>
                      > (e, scalar);
  }

  // scalar with basisfunction:
  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(basisfun<num, diff_tag> const & bf, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_plus<ExpressionDefaultScalarType>
                     > (bf, scalar);
  }

  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(ExpressionDefaultScalarType scalar, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_plus<ExpressionDefaultScalarType>
                     > (scalar, bf);
  }

  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(basisfun<num, diff_tag> const & bf, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_minus<ExpressionDefaultScalarType>
                     > (bf, scalar);
  }

  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(ExpressionDefaultScalarType scalar, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_minus<ExpressionDefaultScalarType>
                     > (scalar, bf);
  }

  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(basisfun<num, diff_tag> const & bf, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_mult<ExpressionDefaultScalarType>
                     > (bf, scalar);
  }

  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(ExpressionDefaultScalarType scalar, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_mult<ExpressionDefaultScalarType>
                     > (scalar, bf);
  }

  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(basisfun<num, diff_tag> const & bf, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       ExpressionDefaultScalarType,
                       op_div<ExpressionDefaultScalarType>
                     > (bf, scalar);
  }

  template <long num, typename diff_tag>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(ExpressionDefaultScalarType scalar, basisfun<num, diff_tag> const & bf)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       basisfun<num, diff_tag>,
                       op_div<ExpressionDefaultScalarType>
                     > (scalar, bf);
  }

  //Scalar with ScalarExpression:
  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(ScalarExpression<value> se, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_plus<ExpressionDefaultScalarType>
                     > (se, scalar);
  }

  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(ExpressionDefaultScalarType scalar, ScalarExpression<value> se)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_plus<ExpressionDefaultScalarType>
                     > (scalar, se);
  }

  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(ScalarExpression<value> se, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_minus<ExpressionDefaultScalarType>
                     > (se, scalar);
  }

  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(ExpressionDefaultScalarType scalar, ScalarExpression<value> se)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_minus<ExpressionDefaultScalarType>
                     > (scalar, se);
  }

  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(ScalarExpression<value> se, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_mult<ExpressionDefaultScalarType>
                     > (se, scalar);
  }

  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(ExpressionDefaultScalarType scalar, ScalarExpression<value> se)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_mult<ExpressionDefaultScalarType>
                     > (scalar, se);
  }

  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(ScalarExpression<value> se, ExpressionDefaultScalarType scalar)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       ExpressionDefaultScalarType,
                       op_div<ExpressionDefaultScalarType>
                     > (se, scalar);
  }

  template <long value>
  inline Expression < ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(ExpressionDefaultScalarType scalar, ScalarExpression<value> se)
  {
    return Expression<  ExpressionDefaultScalarType,
                       ExpressionDefaultScalarType,
                       ScalarExpression<value>,
                       op_div<ExpressionDefaultScalarType>
                     > (scalar, se);
  }


  //generic template for everything: (DANGEROUS!!)
/*
  template <typename LHS, typename RHS>
  inline Expression < ExpressionDefaultScalarType,
                       LHS,
                       RHS,
                       op_plus<ExpressionDefaultScalarType>
                     >
  operator+(LHS const & lhs, RHS const & rhs)
  {
    return Expression < ExpressionDefaultScalarType,
                         LHS,
                         RHS,
                         op_plus<ExpressionDefaultScalarType>
                        >(lhs, rhs);
  }

  template <typename LHS, typename RHS>
  inline Expression < ExpressionDefaultScalarType,
                       LHS,
                       RHS,
                       op_minus<ExpressionDefaultScalarType>
                     >
  operator-(LHS const & lhs, RHS const & rhs)
  {
    return Expression < ExpressionDefaultScalarType,
                         LHS,
                         RHS,
                         op_minus<ExpressionDefaultScalarType>
                       >(lhs, rhs);
  }

  template <typename LHS, typename RHS>
  inline Expression < ExpressionDefaultScalarType,
                       LHS,
                       RHS,
                       op_mult<ExpressionDefaultScalarType>
                     >
  operator*(LHS const & lhs, RHS const & rhs)
  {
    return Expression < ExpressionDefaultScalarType,
                         LHS,
                         RHS,
                         op_mult<ExpressionDefaultScalarType>
                       >(lhs, rhs);
  }

  template <typename LHS, typename RHS>
  inline Expression < ExpressionDefaultScalarType,
                       LHS,
                       RHS,
                       op_div<ExpressionDefaultScalarType>
                     >
  operator/(LHS const & lhs, RHS const & rhs)
  {
    return Expression < ExpressionDefaultScalarType,
                         LHS,
                         RHS,
                         op_div<ExpressionDefaultScalarType>
                       >(lhs, rhs);
  }
 /*/

