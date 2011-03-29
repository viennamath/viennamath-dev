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
#include "viennamath/unary_op_tags.hpp"
#include "viennamath/unary_expression.hpp"
#include "viennamath/binary_expression.hpp"

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
    return new binary_expr<InterfaceType>( new unary_expr<InterfaceType>(e->clone(), new op_unary<op_exp<NumericT>, InterfaceType>()),
                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           e->diff(diff_var)); 
  }

  template <typename NumericT, typename InterfaceType>
  unary_expr<InterfaceType> exp(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> exp(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  unary_expr<InterfaceType> exp(binary_expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> exp(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_exp<default_numeric_type> >()); 
  }

  template <typename InterfaceType>
  unary_expr<InterfaceType> exp(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_exp<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  
  //
  // sinus
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_sin<NumericT>, const InterfaceType * diff_var)
  {
    return new binary_expr<InterfaceType>( new unary_expr<InterfaceType>(e->clone(), new op_unary<op_cos<NumericT>, InterfaceType>()),
                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           e->diff(diff_var) );
  }

  template <typename NumericT, typename InterfaceType>
  unary_expr<InterfaceType> sin(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> sin(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> sin(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_sin<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  unary_expr<InterfaceType> sin(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_sin<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  //
  // cosinus
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_cos<NumericT>, const InterfaceType * diff_var)
  {
    return new binary_expr<InterfaceType>( new unary_expr<InterfaceType>(e->clone(), new op_unary<op_sin<NumericT>, InterfaceType>()),
                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           new binary_expr<InterfaceType>( new constant<NumericT, InterfaceType>(-1),
                                                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                           e->diff(diff_var) )
                                          );
  }

  template <typename NumericT, typename InterfaceType>
  unary_expr<InterfaceType> cos(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> cos(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> cos(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_cos<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  unary_expr<InterfaceType> cos(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_cos<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  //
  // tangens
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_tan<NumericT>, const InterfaceType * diff_var)
  {
    return new binary_expr<InterfaceType>( e->diff(diff_var),
                                          new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                          new binary_expr<InterfaceType>( new unary_expr<InterfaceType>(e->clone(),
                                                                                                        new op_unary<op_cos<NumericT>, InterfaceType>()),
                                                                          new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                          new unary_expr<InterfaceType>(e->clone(),
                                                                                                        new op_unary<op_cos<NumericT>, InterfaceType>()) )
                          );
  }

  template <typename NumericT, typename InterfaceType>
  unary_expr<InterfaceType> tan(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> tan(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> tan(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_tan<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  unary_expr<InterfaceType> tan(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_tan<typename InterfaceType::numeric_type>, InterfaceType>()); 
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
  unary_expr<InterfaceType> fabs(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> fabs(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> fabs(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_fabs<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  unary_expr<InterfaceType> fabs(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_fabs<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }


  //
  // square root
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_sqrt<NumericT>, const InterfaceType * diff_var)
  {
      return new binary_expr<InterfaceType>( e->diff(diff_var),
                                             new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                             new binary_expr<InterfaceType>( new constant<NumericT>(2),
                                                                             new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                             new unary_expr<InterfaceType>(e->clone(),
                                                                                                           new op_unary<op_sqrt<NumericT>, InterfaceType>())
                                                                           )
                                            );
  }

  template <typename NumericT, typename InterfaceType>
  unary_expr<InterfaceType> sqrt(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> sqrt(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> sqrt(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_sqrt<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  unary_expr<InterfaceType> sqrt(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_sqrt<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  //
  // natural logarithm (aka ln())
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_log<NumericT>, const InterfaceType * diff_var)
  {
    return new binary_expr<InterfaceType>( e->diff(diff_var),
                                           new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           new unary_expr<InterfaceType>(e->clone())
                                         );
  }  

  template <typename NumericT, typename InterfaceType>
  unary_expr<InterfaceType> log(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> log(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> log(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_log<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  unary_expr<InterfaceType> log(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_log<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  
  //
  // logarithm, base 10
  //
  
  // (log10(f))' = f' / (ln(f) * ln(10))
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_log10<NumericT>, const InterfaceType * diff_var)
  {
    return new binary_expr<InterfaceType>( e->diff(diff_var),
                                           new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                           new binary_expr<InterfaceType>( new constant<NumericT, InterfaceType>( ::log(10) ),
                                                                           new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                                                           new unary_expr<InterfaceType>(e->clone())
                                                                         )
                                          );
  }  

  template <typename NumericT, typename InterfaceType>
  unary_expr<InterfaceType> log10(constant<NumericT, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <unsigned long id, typename InterfaceType>
  unary_expr<InterfaceType> log10(variable<id, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename LHS, typename OP, typename RHS>
  unary_expr<> log10(ct_expr<LHS, OP, RHS> const & other)
  {
    return unary_expr<>(new binary_expr<>(other),
                        new op_unary<op_log10<default_numeric_type> >()); 
  }


  template <typename InterfaceType>
  unary_expr<InterfaceType> log10(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_log10<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  
  //formal stuff:

  //
  // gradient
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_gradient<NumericT>, const InterfaceType * diff_var)
  {
    throw "Cannot differentiate gradient!";
    return NULL;
  }  
  
  template <typename T, typename InterfaceType>
  unary_expr<InterfaceType> grad(function_symbol<T, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_gradient<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  unary_expr<InterfaceType> grad(unary_expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_gradient<typename InterfaceType::numeric_type>, InterfaceType>()); 
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
  unary_expr<InterfaceType> div(expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.get()->clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  unary_expr<InterfaceType> div(unary_expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }

  template <typename InterfaceType>
  unary_expr<InterfaceType> div(binary_expr<InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
  }
  
  template <typename T, typename InterfaceType>
  unary_expr<InterfaceType> div(function_symbol<T, InterfaceType> const & other)
  {
    return unary_expr<InterfaceType>(other.clone(), new op_unary<op_divergence<typename InterfaceType::numeric_type>, InterfaceType>()); 
    
    //return unary_expr<typename T1::interface_type>(other.clone(), new op_unary<op_divergence<typename T1::numeric_type>, typename T1::interface_type>()); 
  }
  
  
  
  //  
  // Convenience Function: Laplace operator
  //
  template <typename InterfaceType>
  unary_expr<InterfaceType> laplace(expr<InterfaceType> const & other)
  {
    return div(grad(other));
  }
  
  template <typename T, typename InterfaceType>
  unary_expr<InterfaceType> laplace(function_symbol<T, InterfaceType> const & other)
  {
    return div(grad(other));
  }


  //
  // partial derivative with respect to variable<id>:
  //
  template <unsigned long id, typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_partial_deriv<id, NumericT>, const InterfaceType * diff_var)
  {
    throw "Cannot evaluate formal partial derivative. Use transformations first.";
    return NULL;
  }  
  
  //
  // integral:
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_symbolic_integration<NumericT>, const InterfaceType * diff_var)
  {
    throw "Cannot differentiate symbolic_integration!";
    return NULL;
  }  
  
}

#endif