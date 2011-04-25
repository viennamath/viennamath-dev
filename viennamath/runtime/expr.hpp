/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPR_HPP
#define VIENNAMATH_EXPR_HPP

#include <ostream>
#include <sstream>
#include <memory>
#include "viennamath/forwards.h"
#include "viennamath/runtime/constant.hpp"
#include "viennamath/compiletime/ct_constant.hpp"
#include "viennamath/compiletime/ct_expr.hpp"

namespace viennamath
{

  /** @brief An tweaked auto_ptr for run time expressions. 
   * 
   * Additionally provides the basic user-interface for evaluation using operator().
   */ 
  template <typename InterfaceType /* see forwards.h for default argument */>
  class expr 
  {
    public:
      typedef typename InterfaceType::numeric_type       numeric_type;
      typedef InterfaceType                              interface_type;
      
      expr() {}

      explicit expr(const InterfaceType * e) : expr_(e) {}
      
      expr(binary_expr<InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
      }

      expr(unary_expr<InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
      }

      template <typename LHS, typename OP, typename RHS>
      expr(ct_expr<LHS, OP, RHS> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other));
      }

      expr<InterfaceType>(variable<InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
      }

      template <typename T>
      expr(constant<T, InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
      }
      
      expr(function_symbol<InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
      }

      template <long value>
      expr(ct_constant<value> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(new constant<numeric_type>(value));
      }

      expr(numeric_type const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(other));
      }
      
      //Copy CTOR:
      expr(expr const & other)
      {
        if (other.get() != NULL)
        expr_ = std::auto_ptr<InterfaceType>(other.get()->clone());
      }

      //assignments:    
      expr & operator=(InterfaceType * other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other);
        return *this;
      }
      
      expr & operator=(expr const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.get()->clone()); 
        return *this;
      }
      
      template <typename LHS, typename OP, typename RHS>
      expr & operator=(ct_expr<LHS, OP, RHS> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other));
        return *this;
      }

      expr & operator=(binary_expr<InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
        return *this;
      }
      
      expr & operator=(variable<InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
        return *this;
      }

      template <typename ScalarType>
      expr & operator=(constant<ScalarType, InterfaceType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
        return *this;
      }

      template <long value>
      expr & operator=(ct_constant<value> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(new constant<numeric_type>(value));
        return *this;
      }

      expr & operator=(numeric_type value)
      {
        expr_ = std::auto_ptr<InterfaceType>(new constant<numeric_type>(value));
        return *this;
      }

      const InterfaceType   * get() const  { return expr_.get(); }
      
      ///////////////// evaluation: ///////////////////////////////
      
      //operator() is a convenience layer:
      numeric_type operator()(numeric_type val) const
      {
        return expr_.get()->eval(val);
      }

      template <typename ScalarType>
      numeric_type operator()(constant<ScalarType, InterfaceType> val) const
      {
        return expr_.get()->eval(static_cast<numeric_type>(val));
      }
      
      template <long value>
      numeric_type operator()(ct_constant<value> val) const
      {
        return expr_.get()->eval(value);
      }

      template <typename VectorType>
      numeric_type operator()(VectorType const & v) const
      {
        std::vector<double> stl_v(v.size());
        for (size_t i=0; i<v.size(); ++i)
          stl_v[i] = v[i];
        
        return expr_.get()->eval(stl_v);
      }

      numeric_type operator()(std::vector<numeric_type> const & stl_v) const
      {
        //std::cout << "operator() with STL vector!" << std::endl;
        return expr_.get()->eval(stl_v);
      }

      template <typename T0>
      numeric_type operator()(viennamath::ct_vector_1<T0> const & v) const
      {
        std::vector<double> stl_v(1);
        stl_v[0] = v[ct_index<0>()];
        return expr_.get()->eval(stl_v);
      }

      template <typename T0, typename T1>
      numeric_type operator()(viennamath::ct_vector_2<T0, T1> const & v) const
      {
        std::vector<double> stl_v(2);
        stl_v[0] = v[ct_index<0>()];
        stl_v[1] = v[ct_index<1>()];
        return expr_.get()->eval(stl_v);
      }
      
      template <typename T0, typename T1, typename T2>
      numeric_type operator()(viennamath::ct_vector_3<T0, T1, T2> const & v) const
      {
        std::vector<double> stl_v(3);
        stl_v[0] = v[ct_index<0>()];
        stl_v[1] = v[ct_index<1>()];
        stl_v[2] = v[ct_index<2>()];
        return expr_.get()->eval(stl_v);
      }
      
    private:
      std::auto_ptr<const InterfaceType>  expr_;
  };
  
  
  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, expr<InterfaceType> const & e)
  {
    if (e.get()->is_unary())
    {
      stream << "expr" 
            << "("
            << e.get()->deep_str()
            << ")";
    }
    else
    {
      stream << "expr" 
            << e.get()->deep_str();
    }
      
    return stream;
  }
  
}

#endif