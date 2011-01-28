/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_OP_TAGS_HPP
#define VIENNAMATH_OP_TAGS_HPP

#include <string>
#include <vector>
#include <math.h>
#include "viennamath/forwards.h"
#include "viennamath/binary_expression.hpp"
#include "viennamath/unary_expression.hpp"

namespace viennamath
{
  
  
  
  
  
  
  
  //////////////////////////////////////// binary operators ////////////////////////////////////////
  
  
  struct op_plus : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs + rhs; }
    
    //run time stuff:
    op_interface * clone() const { return new op_plus(); }
    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       std::vector<double> const & v) const 
    { 
      return lhs->eval(v) + rhs->eval(v);      
    }

    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       numeric_type v) const 
    { 
      return lhs->eval(v) + rhs->eval(v);      
    }

    numeric_type apply(numeric_type lhs,
                       numeric_type rhs) const
    {
      return lhs + rhs;
    }
    std::string str() const { return "+"; }
    
    expression_interface * diff(const expression_interface * lhs,
                                const expression_interface * rhs,
                                const expr & diff_var) const
    {
      return new binary_expr( lhs->diff(diff_var),
                              new op_plus(),
                              rhs->diff(diff_var) );
    }
  };
  
  
  struct op_minus : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs - rhs; }
    
    
    //run time stuff:
    op_interface * clone() const { return new op_minus(); }
    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       std::vector<double> const & v) const 
    { 
      return lhs->eval(v) - rhs->eval(v);      
    }

    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       numeric_type v) const 
    { 
      return lhs->eval(v) - rhs->eval(v);      
    }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs - rhs; }
    std::string str() const { return "-"; }
    
    expression_interface * diff(const expression_interface * lhs,
                                const expression_interface * rhs,
                                const expr & diff_var) const
    {
      return new binary_expr( lhs->diff(diff_var),
                              new op_minus(),
                              rhs->diff(diff_var) );
    }
  };

  
  struct op_mult : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs * rhs; }
    
    
    //run time stuff:
    op_interface * clone() const { return new op_mult(); }
    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       std::vector<double> const & v) const 
    { 
      return lhs->eval(v) * rhs->eval(v);      
    }

    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       numeric_type v) const 
    { 
      return lhs->eval(v) * rhs->eval(v);      
    }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs * rhs; }
    std::string str() const { return "*"; }

    expression_interface * diff(const expression_interface * lhs,
                                const expression_interface * rhs,
                                const expr & diff_var) const
    {
      return new binary_expr( new binary_expr(lhs->diff(diff_var),
                                              new op_mult(),
                                              rhs->clone()),
                              new op_plus(),
                              new binary_expr(lhs->clone(),
                                              new op_mult(),
                                              rhs->diff(diff_var) )
                            );
    }

  };

  
  struct op_div : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs / rhs; }
    
    
    //run time stuff:
    op_interface * clone() const { return new op_div(); }
    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       std::vector<double> const & v) const 
    { 
      return lhs->eval(v) / rhs->eval(v);      
    }

    numeric_type apply(expression_interface * lhs,
                       expression_interface * rhs,
                       numeric_type v) const 
    { 
      return lhs->eval(v) / rhs->eval(v);      
    }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs / rhs; }
    std::string str() const { return "/"; }


    expression_interface * diff(const expression_interface * lhs,
                                const expression_interface * rhs,
                                const expr &  diff_var) const
    {
      return new binary_expr( new binary_expr( new binary_expr(lhs->diff(diff_var),
                                                               new op_mult(),
                                                               rhs->clone()),
                                               new op_minus(),
                                               new binary_expr(lhs->clone(),
                                                               new op_mult(),
                                                               rhs->diff(diff_var))
                                             ),
                              new op_div(),
                              new binary_expr(rhs->clone(),
                                              new op_mult(),
                                              rhs->clone())
                            );
    }

  };
  
  
  
  ////////////////////////////////////////////// unary operators/functions //////////////////////////////////////

  
  //special case: identity
  //template <>
  op_interface * op_unary<op_id>::clone() const { return new op_unary<op_id>(); }
  
  //
  // exponential
  //
  struct op_exp
  {
    static std::string str() { return "exp"; }
    numeric_type apply(numeric_type value) const { return exp(value); }
    
    static expression_interface * diff(const expression_interface * e,
                                       const expr &  diff_var)
    {
      return new binary_expr( new unary_expr(e->clone(), new op_unary<op_exp>()),
                              new op_mult(),
                              e->diff(diff_var)); 
    }
  };
  
  unary_expr exp(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_exp>()); 
  }

  unary_expr exp(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_exp>()); 
  }

  unary_expr exp(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_exp>()); 
  }

  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr exp(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_exp>()); 
  }

  template <typename ScalarType>
  expr exp(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::exp(other()))); 
  }

  template <long value>
  expr exp(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::exp(value))); 
  }

  
  //
  // sinus
  //
  struct op_sin
  {
    static std::string str() { return "sin"; }
    numeric_type apply(numeric_type value) const { return sin(value); }
    
    static expression_interface * diff(const expression_interface * e,
                                       const expr &  diff_var); //defined after cosinus
  };
  
  unary_expr sin(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_sin>()); 
  }
  
  unary_expr sin(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_sin>()); 
  }

  unary_expr sin(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_sin>()); 
  }

  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr sin(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_sin>()); 
  }

  template <typename ScalarType>
  expr sin(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::sin(other()))); 
  }

  template <long value>
  expr sin(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::sin(value))); 
  }
  
  
  //
  // cosinus
  //
  struct op_cos
  {
    static std::string str() { return "cos"; }
    numeric_type apply(numeric_type value) const { return cos(value); }

    static expression_interface * diff(const expression_interface * e,
                                       const expr &  diff_var)
    {
      return new binary_expr( new unary_expr(e->clone(), new op_unary<op_sin>()),
                              new op_mult(),
                              new binary_expr( new constant<numeric_type>(-1),
                                               new op_mult(),
                                               e->diff(diff_var) )
                            );
    }
    
  };
  
  expression_interface * op_sin::diff(const expression_interface * e,
                                      const expr &  diff_var)
  {
    return new binary_expr( new unary_expr(e->clone(), new op_unary<op_cos>()),
                            new op_mult(),
                            e->diff(diff_var) );
  }


  unary_expr cos(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_cos>()); 
  }
  
  unary_expr cos(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_cos>()); 
  }

  unary_expr cos(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_cos>()); 
  }

  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr cos(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_cos>()); 
  }

  template <typename ScalarType>
  expr cos(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::cos(other()))); 
  }

  template <long value>
  expr cos(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::cos(value))); 
  }
  

  //
  // tangens
  //
  struct op_tan
  {
    static std::string str() { return "tan"; }
    numeric_type apply(numeric_type value) const { return tan(value); }
    
    static expression_interface * diff(const expression_interface * e,
                                       const expr & diff_var)
    {
      return new binary_expr( e->diff(diff_var),
                              new op_div(),
                              new binary_expr( new unary_expr(e->clone(),
                                                              new op_unary<op_cos>()),
                                               new op_mult(),
                                               new unary_expr(e->clone(),
                                                              new op_unary<op_cos>()) )
                            );
    }
    
  };
  
  unary_expr tan(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_tan>()); 
  }
  
  unary_expr tan(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_tan>()); 
  }

  unary_expr tan(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_tan>()); 
  }
  
  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr tan(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_tan>()); 
  }

  template <typename ScalarType>
  expr tan(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::tan(other()))); 
  }

  template <long value>
  expr tan(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::tan(value))); 
  }
  

  //
  // absolute value
  //
  struct op_fabs
  {
    static std::string str() { return "fabs"; }
    numeric_type apply(numeric_type value) const { return fabs(value); }

    static expression_interface * diff(const expression_interface * e,
                                       const expr & diff_var)
    {
      throw "absolute value not differentiable!";
      return NULL;  //TODO: Think about returning a piecewise function here?
    }

  };
  
  unary_expr fabs(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_fabs>()); 
  }
  
  unary_expr fabs(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_fabs>()); 
  }

  unary_expr fabs(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_fabs>()); 
  }

  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr fabs(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_fabs>()); 
  }

  template <typename ScalarType>
  expr fabs(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::fabs(other()))); 
  }

  template <long value>
  expr fabs(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::fabs(value))); 
  }

  //
  // square root
  //
  struct op_sqrt
  {
    static std::string str() { return "sqrt"; }
    numeric_type apply(numeric_type value) const { return sqrt(value); }

    static expression_interface * diff(const expression_interface * e,
                                       const expr & diff_var)
    {
      return new binary_expr( e->diff(diff_var),
                              new op_div(),
                              new binary_expr( new constant<numeric_type>(2),
                                               new op_mult(),
                                               new unary_expr(e->clone(),
                                                              new op_unary<op_sqrt>())
                                              )
                            );
    }
    
  };

  unary_expr sqrt(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_sqrt>()); 
  }
  
  unary_expr sqrt(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_sqrt>()); 
  }
  
  unary_expr sqrt(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_sqrt>()); 
  }
  
  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr sqrt(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_sqrt>()); 
  }

  template <typename ScalarType>
  expr sqrt(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::sqrt(other()))); 
  }

  template <long value>
  expr sqrt(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::sqrt(value))); 
  }
  
  //
  // natural logarithm (aka ln())
  //
  struct op_log //natural logarithm
  {
    static std::string str() { return "log"; }
    numeric_type apply(numeric_type value) const { return log(value); }

    static expression_interface * diff(const expression_interface * e,
                                       const expr & diff_var)
    {
      return new binary_expr( e->diff(diff_var),
                              new op_div(),
                              new unary_expr(e->clone())
                        );
    }
    
  };

  unary_expr log(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_log>()); 
  }
  
  unary_expr log(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_log>()); 
  }
  
  unary_expr log(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_log>()); 
  }
  
  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr log(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_log>()); 
  }

  template <typename ScalarType>
  expr log(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::log(other()))); 
  }

  template <long value>
  expr log(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::log(value))); 
  }
  
  
  
  //
  // logarithm, base 10
  //
  struct op_log10
  {
    static std::string str() { return "log10"; }
    numeric_type apply(numeric_type value) const { return log10(value); }

    // (log10(f))' = f' / (ln(f) * ln(10))
    static expression_interface * diff(const expression_interface * e,
                                       const expr & diff_var)
    {
      return new binary_expr( e->diff(diff_var),
                              new op_div(),
                              new binary_expr( new constant<numeric_type>( ::log(10) ),
                                               new op_mult(),
                                               new unary_expr(e->clone())
                                             )
                        );
    }

  };
  
  unary_expr log10(binary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_log10>()); 
  }
  
  unary_expr log10(unary_expr const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_log10>()); 
  }
  
  unary_expr log10(expr const & other)
  {
    return unary_expr(other.get()->clone(), new op_unary<op_log10>()); 
  }
  
  //NOTE: No compile-time expression supported at this point yet
  template <unsigned long id>
  unary_expr log10(variable<id> const & other)
  {
    return unary_expr(other.clone(), new op_unary<op_log10>()); 
  }

  template <typename ScalarType>
  expr log10(constant<ScalarType> const & other)
  {
    return expr(new constant<numeric_type>(::log10(other()))); 
  }

  template <long value>
  expr log10(ct_constant<value> const & other)
  {
    return expr(new constant<numeric_type>(::log10(value))); 
  }
  
  
  
  
}

#endif