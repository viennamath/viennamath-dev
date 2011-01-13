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
#include "viennamath/forwards.h"
#include "viennamath/expression_run_time.hpp"


namespace viennamath
{
  
  op_interface * op_unary::clone() const { return new op_unary(); }
  
  expr op_unary::apply(expression_interface * lhs,
                       expression_interface * rhs,
                       std::vector<double> const & v) const 
  { 
    return lhs->eval(v);
  }
  
  
  
  //helper: deduce return type:
  template <typename RHS, typename LHS>
  struct op_return_type
  {
    typedef numeric_type      return_type;
  };
    
  
  
  
  struct op_plus : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs + rhs; }
    
    //run time stuff:
    op_interface * clone() const { return new op_plus(); }
    expr apply(expression_interface * lhs, expression_interface * rhs, std::vector<double> const & v) const 
    { 
      return lhs->eval(v) + rhs->eval(v);      
    }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs + rhs; }
    std::string str() const { return "+"; }
    
  };
  
  
  struct op_minus : public op_interface
  {
    template <typename LHS, typename RHS>
    static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs - rhs; }
    
    
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
    static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs * rhs; }
    
    
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
    static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs / rhs; }
    
    
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