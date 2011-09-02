/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_UNARY_OP_TAGS_HPP
#define VIENNAMATH_UNARY_OP_TAGS_HPP

#include <string>
#include <vector>
#include <math.h>
#include "viennamath/forwards.h"
#include "viennamath/debug.hpp"

namespace viennamath
{
  //
  // identity
  //
  template <typename NumericT>
  struct op_id
  {
    static std::string str() { return "id"; }
    NumericT apply(NumericT value) const { return value; }
    
  };

  //
  // exponential
  //
  template <typename NumericT>
  struct op_exp
  {
    static std::string str() { return "exp"; }
    NumericT apply(NumericT value) const { return exp(value); }
    
  };

  //
  // sinus
  //
  template <typename NumericT>
  struct op_sin
  {
    static std::string str() { return "sin"; }
    NumericT apply(NumericT value) const { return sin(value); }
  };
  
  //
  // cosinus
  //
  template <typename NumericT>
  struct op_cos
  {
    static std::string str() { return "cos"; }
    NumericT apply(NumericT value) const { return cos(value); }
  };
  

  //
  // tangens
  //
  template <typename NumericT>
  struct op_tan
  {
    static std::string str() { return "tan"; }
    NumericT apply(NumericT value) const { return tan(value); }
  };
  
  //
  // absolute value
  //
  template <typename NumericT>
  struct op_fabs
  {
    static std::string str() { return "fabs"; }
    NumericT apply(NumericT value) const { return fabs(value); }
  };

  //
  // square root
  //
  template <typename NumericT>
  struct op_sqrt
  {
    static std::string str() { return "sqrt"; }
    NumericT apply(NumericT value) const { return sqrt(value); }
  };

  
  //
  // natural logarithm (aka ln())
  //
  template <typename NumericT>
  struct op_log //natural logarithm
  {
    static std::string str() { return "log"; }
    NumericT apply(NumericT value) const { return log(value); }
  };
  
  //
  // logarithm, base 10
  //
  template <typename NumericT>
  struct op_log10
  {
    static std::string str() { return "log10"; }
    NumericT apply(NumericT value) const { return log10(value); }

  };
  
  ////////////     formal stuff //////////////

  //
  // gradient:
  //
  template <typename NumericT>
  struct op_gradient
  {
    static std::string str() { return "grad"; }
    
    NumericT apply(NumericT value) const
    {
      throw "Cannot evaluate formal gradient. Use transformations first.";
      return 0;
    }
  };
  
  
  //
  // divergence
  //
  template <typename NumericT>
  struct op_divergence
  {
    static std::string str() { return "div"; }
    
    NumericT apply(NumericT value) const
    {
      throw "Cannot evaluate formal divergence. Use transformations first.";
      return 0;
    }
  };

  
  //
  // symbolic partial derivative with respect to variable<id>:
  //
  template <typename NumericT>
  class op_partial_deriv
  {
    public:
      op_partial_deriv() : id_(0) {}
      op_partial_deriv(id_type i) : id_(i) {}
      
      std::string str() const
      {
        std::stringstream ss;
        ss << "partial_deriv<" << id_ << ">";
        return ss.str();
      }
      
      NumericT apply(NumericT value) const
      {
        throw "Cannot evaluate formal partial derivative. Use transformations first.";
        return 0;
      }
      
      id_type id() const { return id_; }
      
    private:
      id_type id_;
  };

  //needed for comparison of unary expressions:
  template <typename T>
  bool unary_op_equal(op_partial_deriv<T> const & lhs, op_partial_deriv<T> const & rhs) { return lhs.id() == rhs.id(); }
  
  
  
  //
  // integral:
  //
  template <typename NumericT, typename BoundaryTag = viennamath::void_>
  struct op_symbolic_integration
  {
    typedef BoundaryTag boundary_tag;
  
    static std::string str() 
    { 
      std::string id = "symb_integral";
      
      // get string for the type
      std::string type_string = viennamath::type_to_string<boundary_tag>();
      // remove the namespaces
      std::size_t found = type_string.find_last_of(":");
      type_string = type_string.substr(found+1);
      // only add a bundary part if there is one ...
      if(type_string != "void_") id += "_{"+type_string+"}";
      
      return id;
    }
    
    NumericT apply(NumericT value) const
    {
      //throw "Cannot evaluate symbolic_integration. Use transformations first.";
      return value;
    }
  };
  
}

#endif

