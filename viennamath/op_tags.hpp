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
    
    const expression_interface * diff(const expression_interface * lhs,
                                      const expression_interface * rhs,
                                      const expression_interface * diff_var) const
    {
      return binary_expr( lhs->diff(diff_var),
                          op_plus().clone(),
                          rhs->diff(diff_var) ).clone();
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
    
    const expression_interface * diff(const expression_interface * lhs,
                                      const expression_interface * rhs,
                                      const expression_interface * diff_var) const
    {
      return binary_expr( lhs->diff(diff_var),
                          op_minus().clone(),
                          rhs->diff(diff_var) ).clone();
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

    const expression_interface * diff(const expression_interface * lhs,
                                      const expression_interface * rhs,
                                      const expression_interface * diff_var) const
    {
      return binary_expr( binary_expr(lhs->diff(diff_var),
                                      op_mult().clone(),
                                      rhs).clone(),
                          op_plus().clone(),
                          binary_expr(lhs,
                                      op_mult().clone(),
                                      rhs->diff(diff_var)).clone()
                         ).clone();
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


    const expression_interface * diff(const expression_interface * lhs,
                                      const expression_interface * rhs,
                                      const expression_interface * diff_var) const
    {
      return binary_expr( binary_expr( binary_expr(lhs->diff(diff_var),
                                                    op_mult().clone(),
                                                    rhs).clone(),
                                        op_minus().clone(),
                                        binary_expr(lhs,
                                                    op_mult().clone(),
                                                    rhs->diff(diff_var)).clone()
                                      ).clone(),
                          op_div().clone(),
                          binary_expr(rhs->clone(),
                                      op_mult().clone(),
                                      rhs->clone()).clone() ).clone();
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
    
    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var)
    {
      return binary_expr( unary_expr(expr->clone(), op_unary<op_exp>().clone()).clone(),
                          op_mult().clone(),
                          expr->diff(diff_var) ).clone(); 
      //return NULL;  //TODO: Insert correct formula here
    }
  };
  
  binary_expr exp(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_exp>().clone(), other.clone()); 
  }



  
  //
  // sinus
  //
  struct op_sin
  {
    static std::string str() { return "sin"; }
    numeric_type apply(numeric_type value) const { return sin(value); }
    
    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var); //defined after cosinus
  };
  
  binary_expr sin(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_sin>().clone(), other.clone()); 
  }
  
  
  
  
  //
  // cosinus
  //
  struct op_cos
  {
    static std::string str() { return "cos"; }
    numeric_type apply(numeric_type value) const { return cos(value); }

    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var)
    {
      return binary_expr( unary_expr(expr->clone(), op_unary<op_sin>().clone()).clone(),
                          op_mult().clone(),
                          binary_expr( constant<numeric_type>(-1).clone(),
                                       op_mult().clone(),
                                       expr->diff(diff_var) ).clone()
                         ).clone();
    }
    
  };
  
  const expression_interface * op_sin::diff(const expression_interface * expr,
                                            const expression_interface * diff_var)
  {
    return binary_expr( unary_expr(expr->clone(), op_unary<op_cos>().clone()).clone(),
                        op_mult().clone(),
                        expr->diff(diff_var) ).clone();
  }


  binary_expr cos(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_cos>().clone(), other.clone()); 
  }
  

  //
  // tangens
  //
  struct op_tan
  {
    static std::string str() { return "tan"; }
    numeric_type apply(numeric_type value) const { return tan(value); }
    
    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var)
    {
      return binary_expr( expr->diff(diff_var),
                          op_div().clone(),
                          binary_expr( unary_expr(expr->clone(), op_unary<op_cos>().clone()).clone(),
                                       op_mult().clone(),
                                       unary_expr(expr->clone(), op_unary<op_cos>().clone()).clone() ).clone()
                        ).clone();
    }
    
  };
  
  binary_expr tan(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_tan>().clone(), other.clone()); 
  }
  
  
  //
  // absolute value
  //
  struct op_fabs
  {
    static std::string str() { return "fabs"; }
    numeric_type apply(numeric_type value) const { return fabs(value); }

    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var)
    {
      throw "absolute value not differentiable!";
      return NULL;  //TODO: Think about returning a piecewise function here?
    }

  };
  
  binary_expr fabs(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_fabs>().clone(), other.clone()); 
  }
  

  //
  // square root
  //
  struct op_sqrt
  {
    static std::string str() { return "sqrt"; }
    numeric_type apply(numeric_type value) const { return sqrt(value); }

    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var)
    {
      return NULL;  //TODO: Insert correct formula here
    }
    
  };

  binary_expr sqrt(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_sqrt>().clone(), other.clone()); 
  }
  
  
  
  //
  // natural logarithm (aka ln())
  //
  struct op_log //natural logarithm
  {
    static std::string str() { return "log"; }
    numeric_type apply(numeric_type value) const { return log(value); }

    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var)
    {
      return NULL;  //TODO: Insert correct formula here
    }
    
  };

  binary_expr log(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_log>().clone(), other.clone()); 
  }
  
  
  //
  // logarithm, base 10
  //
  struct op_log10
  {
    static std::string str() { return "log10"; }
    numeric_type apply(numeric_type value) const { return log10(value); }

    static const expression_interface * diff(const expression_interface * expr,
                                             const expression_interface * diff_var)
    {
      return NULL;  //TODO: Insert correct formula here
    }

  };
  
  binary_expr log10(binary_expr const & other)
  {
    return binary_expr(other.clone(), op_unary<op_log10>().clone(), other.clone()); 
  }
  
  
  
  
  
  
  
  
  
}

#endif