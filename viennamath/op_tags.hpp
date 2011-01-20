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
#include "viennamath/expression_run_time.hpp"


namespace viennamath
{
  
  
  
  ////////////////////////////////////////////// unary operators/functions //////////////////////////////////////

  template <typename unary_operation>
  expr op_unary<unary_operation>::apply(expression_interface * lhs,
                                        expression_interface * rhs,
                                        std::vector<numeric_type> const & v) const
  {
    return constant<numeric_type>(unary_op_.apply(lhs->eval(v).unwrap()));
  }
  
  
  //special case: identity
  //template <>
  op_interface * op_unary<op_id>::clone() const { return new op_unary<op_id>(); }
  
  //template <>
  expr op_unary<op_id>::apply(expression_interface * lhs,
                              expression_interface * rhs,
                              std::vector<double> const & v) const 
  { 
    return lhs->eval(v);
  }
  


  //
  // exponential
  //
  struct op_exp
  {
    static std::string str() { return "exp"; }
    numeric_type apply(numeric_type value) const { return exp(value); }
  };
  
  expr exp(expr const & other)
  {
    return expr(other.clone(), op_unary<op_exp>().clone(), other.clone()); 
  }



  
  //
  // sinus
  //
  struct op_sin
  {
    static std::string str() { return "sin"; }
    numeric_type apply(numeric_type value) const { return sin(value); }
  };
  
  expr sin(expr const & other)
  {
    return expr(other.clone(), op_unary<op_sin>().clone(), other.clone()); 
  }
  
  
  
  
  //
  // cosinus
  //
  struct op_cos
  {
    static std::string str() { return "cos"; }
    numeric_type apply(numeric_type value) const { return cos(value); }
  };

  expr cos(expr const & other)
  {
    return expr(other.clone(), op_unary<op_cos>().clone(), other.clone()); 
  }
  

  //
  // tangens
  //
  struct op_tan
  {
    static std::string str() { return "tan"; }
    numeric_type apply(numeric_type value) const { return tan(value); }
  };
  
  expr tan(expr const & other)
  {
    return expr(other.clone(), op_unary<op_tan>().clone(), other.clone()); 
  }
  
  
  //
  // absolute value
  //
  struct op_fabs
  {
    static std::string str() { return "fabs"; }
    numeric_type apply(numeric_type value) const { return fabs(value); }
  };
  
  expr fabs(expr const & other)
  {
    return expr(other.clone(), op_unary<op_fabs>().clone(), other.clone()); 
  }
  

  //
  // square root
  //
  struct op_sqrt
  {
    static std::string str() { return "sqrt"; }
    numeric_type apply(numeric_type value) const { return sqrt(value); }
  };

  expr sqrt(expr const & other)
  {
    return expr(other.clone(), op_unary<op_sqrt>().clone(), other.clone()); 
  }
  
  
  
  //
  // natural logarithm (aka ln())
  //
  struct op_log //natural logarithm
  {
    static std::string str() { return "log"; }
    numeric_type apply(numeric_type value) const { return log(value); }
  };

  expr log(expr const & other)
  {
    return expr(other.clone(), op_unary<op_log>().clone(), other.clone()); 
  }
  
  
  //
  // logarithm, base 10
  //
  struct op_log10
  {
    static std::string str() { return "log10"; }
    numeric_type apply(numeric_type value) const { return log10(value); }
  };
  
  expr log10(expr const & other)
  {
    return expr(other.clone(), op_unary<op_log10>().clone(), other.clone()); 
  }
  
  
  
  
  
  
  
  
  
  
  //////////////////////////////////////// binary operators ////////////////////////////////////////
  
  
  struct op_plus : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs + rhs; }
    
    //run time stuff:
    op_interface * clone() const { return new op_plus(); }
    expr apply(expression_interface * lhs,
               expression_interface * rhs,
               std::vector<double> const & v) const 
    { 
      return lhs->eval(v) + rhs->eval(v);      
    }
    
    numeric_type apply(numeric_type lhs,
                       numeric_type rhs) const
    {
      return lhs + rhs;
    }
    std::string str() const { return "+"; }
    
  };
  
  
  struct op_minus : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs - rhs; }
    
    
    //run time stuff:
    op_interface * clone() const { return new op_minus(); }
    expr apply(expression_interface * lhs, expression_interface * rhs, std::vector<double> const & v) const 
    { 
      return lhs->eval(v) - rhs->eval(v);      
    }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs - rhs; }
    std::string str() const { return "-"; }
    
  };

  
  struct op_mult : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs * rhs; }
    
    
    //run time stuff:
    op_interface * clone() const { return new op_mult(); }
    expr apply(expression_interface * lhs, expression_interface * rhs, std::vector<double> const & v) const 
    { 
      return lhs->eval(v) * rhs->eval(v);      
    }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs * rhs; }
    std::string str() const { return "*"; }
    
  };

  
  struct op_div : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type static_apply(LHS const & lhs, RHS const & rhs) { return lhs / rhs; }
    
    
    //run time stuff:
    op_interface * clone() const { return new op_div(); }
    expr apply(expression_interface * lhs, expression_interface * rhs, std::vector<double> const & v) const 
    { 
      return lhs->eval(v) / rhs->eval(v);      
    }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs / rhs; }
    std::string str() const { return "/"; }
    
  };
  
  
  
  
  
  
}

#endif