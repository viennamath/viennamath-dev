/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_MANIPULATION_OPTIMIZE_HPP
#define VIENNAMATH_MANIPULATION_OPTIMIZE_HPP

#include "viennamath/forwards.h"
#include "viennamath/runtime/functor_wrapper.hpp"
#include <assert.h>

namespace viennamath
{
  
  //
  //   Section 1: Compile time optimization
  //
  
  namespace result_of
  {
    
    
    // general handling:
    template <typename ExpressionType>
    struct optimize_impl
    {
      //default: no optimization available, thus don't manipulate anything
      enum { value = 0 };
      typedef ExpressionType        type;
    };
    
    template <typename LHS, typename OP, typename RHS>
    struct optimize_impl< ct_binary_expr<LHS, OP, RHS> >
    {
      //default: no optimization available, thus don't manipulate anything
      enum { value = optimize_impl<LHS>::value + optimize_impl<RHS>::value };
      typedef ct_binary_expr<typename optimize_impl<LHS>::type,
                             OP,
                             typename optimize_impl<RHS>::type
                            >        type;
    };
    
    
    
    ///////// Multiplication by zero:
    
    // something times 0 is 0
    template <typename LHS, typename NumericT>
    struct optimize_impl < ct_binary_expr<LHS, op_mult<NumericT>, ct_constant<0> > >
    {
      enum { value = 1 };
      typedef ct_constant<0>          type;
    };
    
    // 0 times something is 0
    template <typename NumericT, typename RHS>
    struct optimize_impl < ct_binary_expr<ct_constant<0>, op_mult<NumericT>, RHS> >
    {
      enum { value = 1 };
      typedef ct_constant<0>          type;
    };

    // 0 times 0 is 0 (resolve ambiguity)
    template <typename NumericT>
    struct optimize_impl < ct_binary_expr<ct_constant<0>, op_mult<NumericT>, ct_constant<0> > >
    {
      enum { value = 1 };
      typedef ct_constant<0>          type;
    };
    
    
    ///////// Multiplication by one:
    
    // something times 1 is something
    template <typename LHS, typename NumericT>
    struct optimize_impl < ct_binary_expr<LHS, op_mult<NumericT>, ct_constant<1> > >
    {
      enum { value = 1 };
      typedef LHS          type;
    };
    
    // 1 times something is something
    template <typename NumericT, typename RHS>
    struct optimize_impl < ct_binary_expr<ct_constant<1>, op_mult<NumericT>, RHS> >
    {
      enum { value = 1 };
      typedef RHS          type;
    };
    
    // 1 times 1 is 1 (resolve ambiguity)
    template <typename NumericT>
    struct optimize_impl < ct_binary_expr<ct_constant<1>, op_mult<NumericT>, ct_constant<1> > >
    {
      enum { value = 1 };
      typedef ct_constant<1>          type;
    };
    
    // resolve amgibuity for 0 * 1:
    template <typename NumericT>
    struct optimize_impl < ct_binary_expr<ct_constant<1>, op_mult<NumericT>, ct_constant<0> > >
    {
      enum { value = 1 };
      typedef ct_constant<0>          type;
    };

    template <typename NumericT>
    struct optimize_impl < ct_binary_expr<ct_constant<0>, op_mult<NumericT>, ct_constant<1> > >
    {
      enum { value = 1 };
      typedef ct_constant<0>          type;
    };
    
    
    ////////// Addition of zero:
    
    // something plus 0 is something
    template <typename LHS, typename NumericT>
    struct optimize_impl < ct_binary_expr<LHS, op_plus<NumericT>, ct_constant<0> > >
    {
      enum { value = 1 };
      typedef LHS          type;
    };
    
    // 0 plus something is something
    template <typename NumericT, typename RHS>
    struct optimize_impl < ct_binary_expr<ct_constant<0>, op_plus<NumericT>, RHS> >
    {
      enum { value = 1 };
      typedef RHS          type;
    };

    // 0 plus 0 is 0 (resolve ambiguity)
    template <typename NumericT>
    struct optimize_impl < ct_binary_expr<ct_constant<0>, op_plus<NumericT>, ct_constant<0> > >
    {
      enum { value = 1 };
      typedef ct_constant<0>          type;
    };
    
    
    
    
    ////////// Subtraction of zero:
    
    // something minus 0 is something
    template <typename LHS, typename NumericT>
    struct optimize_impl < ct_binary_expr<LHS, op_minus<NumericT>, ct_constant<0> > >
    {
      enum { value = 1 };
      typedef LHS          type;
    };
    

    template <typename LHS1, typename NumericT, typename RHS2>
    struct optimize_impl < ct_binary_expr<LHS1,
                                          op_plus<NumericT>,
                                          ct_binary_expr<ct_constant<0>,
                                                         op_minus<NumericT>,
                                                         RHS2 >
                                          > >
    {
      enum { value = 1 };
      typedef ct_binary_expr<LHS1,
                             op_minus<NumericT>,
                             RHS2>                   type;
    };
    
    template <typename LHS1, typename NumericT, typename RHS2>
    struct optimize_impl < ct_binary_expr<LHS1,
                                          op_minus<NumericT>,
                                          ct_binary_expr<ct_constant<0>,
                                                         op_minus<NumericT>,
                                                         RHS2 >
                                          > >
    {
      enum { value = 1 };
      typedef ct_binary_expr<LHS1,
                             op_plus<NumericT>,
                             RHS2>                   type;
    };

    template <typename RHS1, typename NumericT, typename RHS2>
    struct optimize_impl < ct_binary_expr<ct_binary_expr< ct_constant<0>,
                                                          op_minus<NumericT>,
                                                          RHS1 >,
                                          op_plus<NumericT>,
                                          RHS2
                                          > >
    {
      enum { value = 1 };
      typedef ct_binary_expr<RHS2,
                             op_minus<NumericT>,
                             RHS1>                   type;
    };
    
    template <typename RHS1, typename NumericT, typename RHS2>
    struct optimize_impl < ct_binary_expr<ct_binary_expr< ct_constant<0>,
                                                          op_minus<NumericT>,
                                                          RHS1 >,
                                          op_minus<NumericT>,
                                          RHS2
                                          > >
    {
      enum { value = 1 };
      typedef ct_binary_expr< ct_constant<-1>,
                              op_mult<NumericT>,
                              ct_binary_expr<RHS1,
                                             op_plus<NumericT>,
                                             RHS2>
                            >                 type;
    };
    
    // resolve ambituity for plus:
    template <typename RHS1, typename NumericT, typename RHS2>
    struct optimize_impl < ct_binary_expr<ct_binary_expr< ct_constant<0>,
                                                          op_minus<NumericT>,
                                                          RHS1 >,
                                          op_plus<NumericT>,
                                          ct_binary_expr< ct_constant<0>,
                                                          op_minus<NumericT>,
                                                          RHS2 >                                          
                                          > >
    {
      enum { value = 1 };
      typedef ct_binary_expr< ct_constant<-1>,
                              op_mult<NumericT>,
                              ct_binary_expr<RHS1,
                                             op_plus<NumericT>,
                                             RHS2>
                            >                 type;
    };

    // resolve ambituity for minus:
    template <typename RHS1, typename NumericT, typename RHS2>
    struct optimize_impl < ct_binary_expr<ct_binary_expr< ct_constant<0>,
                                                          op_minus<NumericT>,
                                                          RHS1 >,
                                          op_minus<NumericT>,
                                          ct_binary_expr< ct_constant<0>,
                                                          op_minus<NumericT>,
                                                          RHS2 >                                          
                                          > >
    {
      enum { value = 1 };
      typedef ct_binary_expr<RHS2,
                             op_minus<NumericT>,
                             RHS1>                   type;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////
    
    
    //
    // interfacing metafunction: loops over optimization routines until no more optimization is possible
    //
    template <typename ExpressionType,
              bool optimization_possible = (optimize_impl<ExpressionType>::value != 0)
             >
    struct optimize {}; //provides SFINAE for the compile time interface function optimize()
    
    // binary expression
    template <typename LHS, typename OP, typename RHS>
    struct optimize < ct_binary_expr<LHS, OP, RHS>, true >
    {
      typedef typename optimize_impl< ct_binary_expr<LHS, OP, RHS> >::type    optimized_type;
      typedef typename optimize<optimized_type>::type       type;
      //typedef optimized_type          type;
    };

    template <typename LHS, typename OP, typename RHS>
    struct optimize < ct_binary_expr<LHS, OP, RHS>, false >
    {
      typedef ct_binary_expr<LHS, OP, RHS>          type;
    };

    // unary expression
    template <typename LHS, typename OP>
    struct optimize < ct_unary_expr<LHS, OP>, true >
    {
      typedef typename optimize_impl< ct_unary_expr<LHS, OP> >::type    optimized_type;
      typedef typename optimize<optimized_type>::type       type;
    };

    template <typename LHS, typename OP>
    struct optimize < ct_unary_expr<LHS, OP>, false >
    {
      typedef ct_unary_expr<LHS, OP>       type;
    };

    // constant
    template <long value>
    struct optimize < ct_constant<value>, true >
    {
      typedef typename optimize_impl< ct_constant<value> >::type    optimized_type;
      typedef typename optimize<optimized_type>::type       type;
    };

    template <long value>
    struct optimize < ct_constant<value>, false >
    {
      typedef ct_constant<value>       type;
    };

    // function symbol
    template <typename TAG>
    struct optimize < ct_function_symbol<TAG>, true >
    {
      typedef typename optimize_impl< ct_function_symbol<TAG> >::type    optimized_type;
      typedef typename optimize<optimized_type>::type       type;
    };

    template <typename TAG>
    struct optimize < ct_function_symbol<TAG>, false >
    {
      typedef ct_function_symbol<TAG>       type;
    };

    // variable
    template <id_type id>
    struct optimize < ct_variable<id>, true >
    {
      typedef typename optimize_impl< ct_variable<id> >::type    optimized_type;
      typedef typename optimize<optimized_type>::type       type;
    };
    
    template <id_type id>
    struct optimize < ct_variable<id>, false >
    {
      typedef ct_variable<id>       type;
    };
    
  } //namespace result_of
  
  
  template <typename ExpressionType>
  typename result_of::optimize<ExpressionType>::type
  optimize(ExpressionType const & e)
  {
    return typename result_of::optimize<ExpressionType>::type();
  } 
  
  
  //
  //   Section 1: Run time optimization
  //
  
  
  
  //public interface:
  /** @brief Optimizes an expression. */
  template <typename InterfaceType>
  void inplace_optimize(rt_expr<InterfaceType> & e)
  {
    while (e.get()->optimizable())
      e = e.get()->optimize();
  }

  /** @brief Optimizes an expression. */
  template <typename InterfaceType>
  void inplace_optimize(rt_unary_expr<InterfaceType> & e)
  {
    while (e->optimizable())
      e = e->optimize();
  }

  /** @brief Optimizes an expression. */
  template <typename InterfaceType>
  void inplace_optimize(rt_binary_expr<InterfaceType> & e)
  {
    while (e->optimizable())
      e = e->optimize();
  }

  /** @brief Optimizes an expression. */
  template <typename T>
  void inplace_optimize(T & e)
  {
    //do nothing, since primitive types cannot be simplified
  }

}

#endif