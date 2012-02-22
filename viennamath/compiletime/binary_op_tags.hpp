#ifndef VIENNAMATH_COMPILETIME_BINARY_OP_TAGS_HPP
#define VIENNAMATH_COMPILETIME_BINARY_OP_TAGS_HPP

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




#include <string>
#include <vector>
#include <math.h>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  //
  // addition
  //
  template <typename NumericT>
  struct op_plus
  {
    typedef NumericT        numeric_type;
    
    //template <typename LHS, typename RHS>
    //static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs + rhs; }
    
    static NumericT apply(NumericT lhs, NumericT rhs) { return lhs + rhs; }
    
    static std::string str() { return "+"; }
  };
  
  
  //
  // subtraction
  //
  template <typename NumericT>
  struct op_minus
  {
    typedef NumericT        numeric_type;
    
    //template <typename LHS, typename RHS>
    //static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs - rhs; }
    
    static NumericT apply(NumericT lhs, NumericT rhs) { return lhs - rhs; }
    
    static std::string str() { return "-"; }
  };
  
  
  //
  // multiplication
  //
  template <typename NumericT>
  struct op_mult
  {
    typedef NumericT        numeric_type;
    
    //template <typename LHS, typename RHS>
    //static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs * rhs; }
    
    static NumericT apply(NumericT lhs, NumericT rhs) { return lhs * rhs; }
    
    static std::string str() { return "*"; }
  };
  
  
  //
  // division
  //
  template <typename NumericT>
  struct op_div
  {
    typedef NumericT        numeric_type;
    
    //template <typename LHS, typename RHS>
    //static typename op_return_type<LHS, RHS>::return_type apply(LHS const & lhs, RHS const & rhs) { return lhs / rhs; }
    
    static NumericT apply(NumericT lhs, NumericT rhs) { return lhs / rhs; }
    
    static std::string str() { return "/"; }
  };
  
  
  
  
}

#endif