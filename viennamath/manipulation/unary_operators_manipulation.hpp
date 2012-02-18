/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_UNARY_OPERATORS_MANIPULATION_HPP
#define VIENNAMATH_UNARY_OPERATORS_MANIPULATION_HPP

#include <string>
#include <vector>
#include <math.h>
#include "viennamath/forwards.h"
#include "viennamath/compiletime/unary_op_tags.hpp"
#include "viennamath/runtime/unary_expression.hpp"
#include "viennamath/runtime/binary_expression.hpp"
#include "viennamath/runtime/integral.hpp"

namespace viennamath
{
  
  //
  // identity
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_id<NumericT>, const InterfaceType * diff_var)
  {
    return e->diff(diff_var); 
  }
  
  //
  // exponential
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_exp<NumericT>, const InterfaceType * diff_var)
  {
    return new rt_binary_expr<InterfaceType>( new rt_unary_expr<InterfaceType>(e->clone(), new op_unary<op_exp<NumericT>, InterfaceType>()),
                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           e->diff(diff_var)); 
  }

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> exp(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> exp(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> exp(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_exp<default_numeric_type> >()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> exp(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> exp(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                        new op_unary<op_exp<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> exp(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                           new op_unary<op_exp<default_numeric_type> >()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> exp(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  
  //
  // sinus
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_sin<NumericT>, const InterfaceType * diff_var)
  {
    return new rt_binary_expr<InterfaceType>( new rt_unary_expr<InterfaceType>(e->clone(), new op_unary<op_cos<NumericT>, InterfaceType>()),
                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           e->diff(diff_var) );
  }

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> sin(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sin(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> sin(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_sin<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> sin(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                           new op_unary<op_sin<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> sin(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                           new op_unary<op_sin<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sin(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sin(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sin(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  
  
  //
  // cosinus
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_cos<NumericT>, const InterfaceType * diff_var)
  {
    return new rt_binary_expr<InterfaceType>( new rt_unary_expr<InterfaceType>(e->clone(), new op_unary<op_sin<NumericT>, InterfaceType>()),
                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           new rt_binary_expr<InterfaceType>( new rt_constant<NumericT, InterfaceType>(-1),
                                                                              new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                              e->diff(diff_var) )
                                          );
  }

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> cos(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> cos(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> cos(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_cos<default_numeric_type> >()); 
  }
  
  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> cos(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                        new op_unary<op_cos<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> cos(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                           new op_unary<op_cos<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> cos(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> cos(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> cos(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  //
  // tangens
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_tan<NumericT>, const InterfaceType * diff_var)
  {
    return new rt_binary_expr<InterfaceType>( e->diff(diff_var),
                                          new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                          new rt_binary_expr<InterfaceType>( new rt_unary_expr<InterfaceType>(e->clone(),
                                                                                                        new op_unary<op_cos<NumericT>, InterfaceType>()),
                                                                          new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                          new rt_unary_expr<InterfaceType>(e->clone(),
                                                                                                        new op_unary<op_cos<NumericT>, InterfaceType>()) )
                          );
  }

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> tan(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> tan(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> tan(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_tan<default_numeric_type> >()); 
  }
  
  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> tan(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                        new op_unary<op_tan<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> tan(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                        new op_unary<op_tan<default_numeric_type> >()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> tan(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> tan(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> tan(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  

  //
  // absolute value
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_fabs<NumericT>, const InterfaceType * diff_var)
  {
    throw "absolute value not differentiable!";
    return NULL;  //TODO: Think about returning a piecewise function here?
  }

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> fabs(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> fabs(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> fabs(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_fabs<default_numeric_type> >()); 
  }
  
  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> fabs(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                           new op_unary<op_fabs<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> fabs(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                           new op_unary<op_fabs<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> fabs(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> fabs(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> fabs(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }


  //
  // square root
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_sqrt<NumericT>, const InterfaceType * diff_var)
  {
      return new rt_binary_expr<InterfaceType>( e->diff(diff_var),
                                             new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                             new rt_binary_expr<InterfaceType>( new rt_constant<NumericT>(2),
                                                                             new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                             new rt_unary_expr<InterfaceType>(e->clone(),
                                                                                                           new op_unary<op_sqrt<NumericT>, InterfaceType>())
                                                                           )
                                            );
  }

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> sqrt(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sqrt(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> sqrt(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_sqrt<default_numeric_type> >()); 
  }
  
  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> sqrt(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                           new op_unary<op_sqrt<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> sqrt(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                           new op_unary<op_sqrt<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sqrt(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sqrt(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> sqrt(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  //
  // natural logarithm (aka ln())
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_log<NumericT>, const InterfaceType * diff_var)
  {
    return new rt_binary_expr<InterfaceType>( e->diff(diff_var),
                                           new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           new rt_unary_expr<InterfaceType>(e->clone())
                                         );
  }  

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> log(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> log(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_log<default_numeric_type> >()); 
  }
  
  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> log(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                           new op_unary<op_log<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> log(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                           new op_unary<op_log<default_numeric_type> >()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  
  //
  // logarithm, base 10
  //
  
  // (log10(f))' = f' / (ln(f) * ln(10))
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_log10<NumericT>, const InterfaceType * diff_var)
  {
    return new rt_binary_expr<InterfaceType>( e->diff(diff_var),
                                           new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           new rt_binary_expr<InterfaceType>( new rt_constant<NumericT, InterfaceType>( ::log(10) ),
                                                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                           new rt_unary_expr<InterfaceType>(e->clone())
                                                                         )
                                          );
  }  

  template <typename NumericT, typename InterfaceType>
  rt_unary_expr<InterfaceType> log10(rt_constant<NumericT, InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log10(rt_variable<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <id_type id>
  rt_unary_expr<> log10(ct_variable<id> const & other)
  {
    return rt_unary_expr<>(new rt_variable<>(id), new op_unary<op_log10<default_numeric_type> >()); 
  }
  
  template <typename LHS, typename OP, typename RHS>
  rt_unary_expr<> log10(ct_binary_expr<LHS, OP, RHS> const & other)
  {
    return rt_unary_expr<>(new rt_binary_expr<>(other),
                           new op_unary<op_log10<default_numeric_type> >()); 
  }

  template <typename LHS, typename OP>
  rt_unary_expr<> log10(ct_unary_expr<LHS, OP> const & other)
  {
    return rt_unary_expr<>(new rt_unary_expr<>(other),
                           new op_unary<op_log10<default_numeric_type> >()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log10(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log10(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> log10(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  
  ///////////////////  formal (symbolic) stuff ////////////////////////////////

  //
  // gradient
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_gradient<NumericT>, const InterfaceType * diff_var)
  {
    throw "Cannot differentiate gradient!";
    return NULL;
  }  
  
  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> grad(rt_function_symbol<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_gradient<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> grad(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_gradient<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }


  //
  // divergence 
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_divergence<NumericT>, const InterfaceType * diff_var)
  {
    throw "Cannot differentiate gradient!";
    return NULL;
  }  
  
  
  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> div(rt_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> div(rt_unary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> div(rt_binary_expr<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> div(rt_function_symbol<InterfaceType> const & other)
  {
    return rt_unary_expr<InterfaceType>(other.clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
    
    //return rt_unary_expr<typename T1::interface_type>(other.clone(), new op_unary<op_divergence<typename T1::numeric_type>, typename T1::interface_type>()); 
  }
  
  
  
  //  
  // Convenience Function: Laplace operator
  //
  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> laplace(rt_expr<InterfaceType> const & other)
  {
    return div(grad(other));
  }
  
  template <typename InterfaceType>
  rt_unary_expr<InterfaceType> laplace(rt_function_symbol<InterfaceType> const & other)
  {
    return div(grad(other));
  }


  //
  // partial derivative with respect to variable<id>:
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_partial_deriv<NumericT>, const InterfaceType * diff_var)
  {
    throw "Cannot evaluate formal partial derivative. Use transformations first.";
    return NULL;
  }  
  
  //
  // integral:
  //

  template <typename InterfaceType>
  InterfaceType * diff_impl(const InterfaceType * e, op_rt_integral<InterfaceType>, const InterfaceType * diff_var)
  {
    throw "Cannot differentiate runtime integration (yet)!";
    return NULL;
  }  

  template <typename InterfaceType>
  InterfaceType * diff_impl(const InterfaceType * e, op_rt_symbolic_integral<InterfaceType>, const InterfaceType * diff_var)
  {
    throw "Cannot differentiate runtime integration (yet)!";
    return NULL;
  }  

}

#endif
