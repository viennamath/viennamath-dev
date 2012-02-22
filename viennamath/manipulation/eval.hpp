#ifndef VIENNAMATH_MANIPULATION_EVAL_HPP
#define VIENNAMATH_MANIPULATION_EVAL_HPP

/* =======================================================================
   Copyright (c) 2012, Institute for Microelectronics,
                       Institute for Analysis and Scientific Computing,
                       TU Wien.
                             -----------------
               ViennaMath - Symbolic and Numerical Math in C++
                             -----------------

   Author:     Karl Rupp                          rupp@iue.tuwien.ac.at

   License:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */




#include "viennamath/forwards.h"
#include "viennamath/compiletime/ct_variable.hpp"
#include "viennamath/manipulation/optimize.hpp"

namespace viennamath
{
  ///////////// compile time ///////////////////////////////

  namespace result_of
  {
    /** @brief Returns nonzero if supplied expression can be evaluated at compile time */
    template <typename E>
    struct is_ct_evaluable
    {
      enum { value = 0 };
    };
    
    
    template <typename LHS, typename OP, typename RHS>
    struct is_ct_evaluable< ct_binary_expr<LHS, OP, RHS> >
    {
      enum { value = is_ct_evaluable<LHS>::value * is_ct_evaluable<RHS>::value };
    };
    
    template <long val>
    struct is_ct_evaluable< ct_constant<val> >
    {
      enum { value = 1 };
    };
    
    template <id_type id>
    struct is_ct_evaluable< ct_variable<id> >
    {
      enum { value = 1 };
    };
    
    /** @brief Returns nonzero if the supplied vector type is a compile-time vector */
    template <typename VectorType>
    struct is_ct_vector
    {
      enum { value = 0 };
    };

    template <typename T0>
    struct is_ct_vector< ct_vector_1<T0> > 
    {
      enum { value = is_compiletime<T0>::val };
    };

    template <typename T0, typename T1>
    struct is_ct_vector< ct_vector_2<T0, T1> >
    {
      enum { value = is_compiletime<T0>::val && is_compiletime<T1>::val };
    };

    template <typename T0, typename T1, typename T2>
    struct is_ct_vector< ct_vector_3<T0, T1, T2> > 
    {
      enum { value = is_compiletime<T0>::val && is_compiletime<T1>::val && is_compiletime<T2>::val };
    };
    
    
    //
    // compile time evaluation metafunction
    template <typename ExpressionType,
              typename VectorType,
              bool ct_evaluable = (is_ct_evaluable<ExpressionType>::value != 0)>
    struct eval
    {
      typedef typename ExpressionType::ERROR_INVALID_EXPRESSION_TYPE_FOR_COMPILETIME_EVALUATION  error_type;
    };
    
    //valid arguments:
    template <typename LHS, typename OP, typename RHS, typename VectorType>
    struct eval< ct_binary_expr<LHS, OP, RHS>, VectorType, true>
    {
      typedef ct_binary_expr< typename eval<LHS, VectorType>::type,
                              OP,
                              typename eval<RHS, VectorType>::type >  intermediate_type;
      
      // run two rational evaluations in the following (the second ensures a resolution of a/1 and 0/b cases)
      typedef typename result_of::optimize<intermediate_type>::type   type;
    };
    
    template <long value, typename VectorType>
    struct eval< ct_constant<value>, VectorType, true>
    {
      typedef ct_constant<value>    type;
    };
    
    template <id_type id, typename VectorType>
    struct eval< ct_variable<id>, VectorType, true>
    {
      typedef typename type_by_index<VectorType, id>::type  type;
    };
    
    template <long value>
    struct eval< ct_variable<0>, ct_constant<value>, true>
    {
      typedef ct_constant<value>  type;
    };
    
  } //namespace result_of
  
  //the public interface function:
  template <typename ExpressionType, typename VectorType>
  //typename result_of::eval<ExpressionType, VectorType>::type
  typename enable_if<result_of::is_ct_evaluable<ExpressionType>::value && result_of::is_ct_vector<VectorType>::value,
                     default_numeric_type>::type 
  eval(ExpressionType const & e, VectorType const & v)
  {
    return typename result_of::eval<ExpressionType, VectorType>::type();
  }
  

  
  ///////////// run time ///////////////////////////////
  
  /*template <typename ExpressionType, typename VectorType>
  typename ExpressionType::numeric_type eval(ExpressionType const & e, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return e(v);
  }*/

  template <typename VectorType>
  default_numeric_type eval(default_numeric_type value, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return value;
  }

  template <typename VectorType>
  long eval(long value, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return value;
  }

  template <typename T, typename InterfaceType, typename VectorType>
  typename InterfaceType::numeric_type
  eval(rt_constant<T, InterfaceType> c, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return c();
  }

  template <typename InterfaceType, typename VectorType>
  typename InterfaceType::numeric_type
  eval(rt_expr< InterfaceType> e, VectorType const & v)
  {
    return e(v);
  }

  template <typename InterfaceType, typename VectorType>
  typename InterfaceType::numeric_type
  eval(rt_binary_expr< InterfaceType> e, VectorType const & v)
  {
    return e(v);
  }

  template <typename InterfaceType, typename VectorType>
  typename InterfaceType::numeric_type
  eval(rt_unary_expr< InterfaceType> e, VectorType const & v)
  {
    return e(v);
  }

  template <typename InterfaceType, typename VectorType>
  typename InterfaceType::numeric_type
  eval(rt_variable< InterfaceType> e, VectorType const & v)
  {
    return e(v);
  }



  template <typename LHS, typename OP, typename RHS, typename VectorType>
  default_numeric_type eval(ct_binary_expr<LHS, OP, RHS> ex, VectorType const & v)
  {
    return ex(v);
  }
  
  template <typename LHS, typename OP, typename VectorType>
  default_numeric_type eval(ct_unary_expr<LHS, OP> ex, VectorType const & v)
  {
    return ex(v);
  }

  template <long value, typename VectorType>
  default_numeric_type eval(ct_constant<value> c, VectorType const & v)
  {
    return value;
  }

  template <id_type id, typename VectorType>
  default_numeric_type eval(ct_variable<id> c, VectorType const & v)
  {
    return v[id];
  }

  template <id_type id, typename T0>
  default_numeric_type eval(ct_variable<id> c, ct_vector_1<T0> const & v)
  {
    return v[ct_index<id>()];
  }

  template <id_type id, typename T0, typename T1>
  default_numeric_type eval(ct_variable<id> c, ct_vector_2<T0, T1> const & v)
  {
    return v[ct_index<id>()];
  }

  template <id_type id, typename T0, typename T1, typename T2>
  default_numeric_type eval(ct_variable<id> c, ct_vector_3<T0, T1, T2> const & v)
  {
    return v[ct_index<id>()];
  }

}

#endif