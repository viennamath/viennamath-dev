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
    bool optimizable() const { return true; }
  };

  //
  // exponential
  //
  template <typename NumericT>
  struct op_exp
  {
    static std::string str() { return "exp"; }
    NumericT apply(NumericT value) const { return exp(value); }
    bool optimizable() const { return true; }
  };

  //
  // sinus
  //
  template <typename NumericT>
  struct op_sin
  {
    static std::string str() { return "sin"; }
    NumericT apply(NumericT value) const { return sin(value); }
    bool optimizable() const { return true; }
  };
  
  //
  // cosinus
  //
  template <typename NumericT>
  struct op_cos
  {
    static std::string str() { return "cos"; }
    NumericT apply(NumericT value) const { return cos(value); }
    bool optimizable() const { return true; }
  };
  

  //
  // tangens
  //
  template <typename NumericT>
  struct op_tan
  {
    static std::string str() { return "tan"; }
    NumericT apply(NumericT value) const { return tan(value); }
    bool optimizable() const { return true; }
  };
  
  //
  // absolute value
  //
  template <typename NumericT>
  struct op_fabs
  {
    static std::string str() { return "fabs"; }
    NumericT apply(NumericT value) const { return fabs(value); }
    bool optimizable() const { return true; }
  };

  //
  // square root
  //
  template <typename NumericT>
  struct op_sqrt
  {
    static std::string str() { return "sqrt"; }
    NumericT apply(NumericT value) const { return sqrt(value); }
    bool optimizable() const { return true; }
  };

  
  //
  // natural logarithm (aka ln())
  //
  template <typename NumericT>
  struct op_log //natural logarithm
  {
    static std::string str() { return "log"; }
    NumericT apply(NumericT value) const { return log(value); }
    bool optimizable() const { return true; }
  };
  
  //
  // logarithm, base 10
  //
  template <typename NumericT>
  struct op_log10
  {
    static std::string str() { return "log10"; }
    NumericT apply(NumericT value) const { return log10(value); }
    bool optimizable() const { return true; }
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
    bool optimizable() const { return true; }
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
    bool optimizable() const { return true; }
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
      
      bool optimizable() const { return false; }
      
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
  template <typename IntervalType, unsigned long integration_variable>
  class op_ct_integral
  {
      typedef typename IntervalType::numeric_type    NumericT;
    
    public:
      typedef IntervalType         interval_type;
      
      
      
      static std::string str() { return "symb_int"; }
      
      NumericT apply(NumericT value) const
      {
        throw "Cannot evaluate symbolic_integration. Use transformations first.";
        return value;
      }

      bool optimizable() const { return false; }

    private:
      IntervalType const & interval;
      
  };
  
}

#endif

