/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPR_CPP
#define VIENNAMATH_EXPR_CPP

#include <ostream>
#include <sstream>
#include <memory>
#include "viennamath/forwards.h"
#include "viennamath/constant.hpp"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/expression.hpp"

namespace viennamath
{
  
  expr::expr(binary_expr const & other)
  {
    expr_ = std::auto_ptr<expression_interface>(other.clone());
  }

  expr::expr(unary_expr const & other)
  {
    expr_ = std::auto_ptr<expression_interface>(other.clone());
  }
  
  //Copy CTOR
  expr::expr(expr const & other)
  {
    expr_ = std::auto_ptr<expression_interface>(other.get()->clone());
  }

  //assignments:                           
  template <typename LHS, typename OP, typename RHS>
  expr & expr::operator=(expression<LHS, OP, RHS> const & other) 
  {
    expr_ = std::auto_ptr<expression_interface>(new binary_expr(other));
    return *this;
  }

  expr & expr::operator=(binary_expr const & other) 
  {
    expr_ = std::auto_ptr<expression_interface>(other.clone());
    return *this;
  }

  template <typename ScalarType>
  expr & expr::operator=(constant<ScalarType> const & other)
  {
    expr_ = std::auto_ptr<expression_interface>(new unary_expr(other));
    return *this;
  }

  template <long value>
  expr & expr::operator=(ct_constant<value> const & other)
  {
    expr_ = std::auto_ptr<expression_interface>(new unary_expr(other));
    return *this;
  }

  expr & expr::operator=(numeric_type value)
  {
    expr_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
    return *this;
  }

  const expression_interface * expr::get() const { return expr_.get(); }



  //operator() is a convenience layer:
  numeric_type expr::operator()(numeric_type val) const
  {
    return expr_.get()->eval(val);
  }

  template <typename ScalarType>
  numeric_type expr::operator()(constant<ScalarType> val) const
  {
    return expr_.get()->eval(static_cast<numeric_type>(val));
  }
  
  template <long value>
  numeric_type expr::operator()(ct_constant<value> val) const
  {
    return expr_.get()->eval(value);
  }

  template <typename VectorType>
  numeric_type expr::operator()(VectorType const & v) const
  {
    std::vector<double> stl_v(v.size());
    for (size_t i=0; i<v.size(); ++i)
      stl_v[i] = v[i];
    
    return expr_.get()->eval(stl_v);
  }

  numeric_type expr::operator()(std::vector<numeric_type> const & stl_v) const
  {
    return expr_.get()->eval(stl_v);
  }

  template <typename T0>
  numeric_type expr::operator()(viennamath::vector_1<T0> const & v) const
  {
    std::vector<double> stl_v(1);
    stl_v[0] = v[ct_index<0>()];
    return expr_.get()->eval(stl_v);
  }

  template <typename T0, typename T1>
  numeric_type expr::operator()(viennamath::vector_2<T0, T1> const & v) const
  {
    std::vector<double> stl_v(2);
    stl_v[0] = v[ct_index<0>()];
    stl_v[1] = v[ct_index<1>()];
    return expr_.get()->eval(stl_v);
  }
  
  template <typename T0, typename T1, typename T2>
  numeric_type expr::operator()(viennamath::vector_3<T0, T1, T2> const & v) const
  {
    std::vector<double> stl_v(3);
    stl_v[0] = v[ct_index<0>()];
    stl_v[1] = v[ct_index<1>()];
    stl_v[2] = v[ct_index<2>()];
    return expr_.get()->eval(stl_v);
  }


  
  std::ostream& operator<<(std::ostream & stream, expr const & e)
  {
    stream << "expr" 
           << e.get()->str()
           << "";
    return stream;
  }
  
}

#endif