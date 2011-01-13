/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_FORWARDS_H
#define VIENNAMATH_FORWARDS_H

#include <string>
#include <vector>
#include <exception>

namespace viennamath
{
  //basic numeric type (customize to your needs)
  typedef double              numeric_type;

  //allows to use plain numeric_type with template operator+, operator-, operator*, operator/ without running into problems with ambiguity
  //
  // example:
  // operator+(expr e, numeric_t val);
  //
  // template <typename ScalarType>
  // operator+(expr e, ct_constant<value>); 
  //
  // lead to ambiguity for e + 4;
  class numeric_type_proxy
  {
    public:
      numeric_type_proxy(numeric_type value) : value_(value) {}
      
      numeric_type get() const { return value_; }
    private:
      numeric_type value_;
  };

  
  
  /////// compile time expression ///////
  template <typename LHS,
            typename OP,
            typename RHS>
  class expression;
  
  /////// run time expression ///////
    
  class expr;

  //class expression_interface;
  //interface for dispatches:
  class expression_interface
  {
    public:
      virtual ~expression_interface() {}
      
      virtual expression_interface * clone() const = 0;
      virtual std::string str() const = 0;
      virtual expr eval(std::vector<double> const & v) const = 0;
      virtual bool is_unary() const { return true; }
      virtual numeric_type unwrap() const = 0;
  };
 

  expr operator+(expr const & lhs, expr const & rhs);
  expr operator-(expr const & lhs, expr const & rhs);
  expr operator*(expr const & lhs, expr const & rhs);
  expr operator/(expr const & lhs, expr const & rhs);
  
  
  
  
  
  /////// interface for op_tags: ///////
  class op_interface
  {
    public:
      virtual ~op_interface() {}
      
      virtual op_interface * clone() const = 0;
      virtual std::string str() const = 0;
      virtual expr apply(expression_interface * lhs,
                         expression_interface * rhs,
                         std::vector<numeric_type> const & v) const  = 0;
      virtual numeric_type apply(numeric_type lhs, numeric_type rhs) const = 0;                   
      virtual bool is_unary() const { return false; }
  };
  
  struct op_unary : public op_interface
  {
    //TODO: deduce return type
    template <typename LHS, typename RHS>
    static void apply(LHS const & lhs, RHS const & rhs) { return lhs; }
    
    
    //run time stuff:
    std::string str() const { return "UNARY"; }
    op_interface * clone() const;
    expr apply(expression_interface * lhs,
               expression_interface * rhs,
               std::vector<numeric_type> const & v) const;
    bool is_unary() const { return true; }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs; }
  };
  
  struct op_plus;
  struct op_minus;
  struct op_mult;
  struct op_div;
  
  
  
  
  
  
  
  
  /////// unknown ///////
  template <typename ScalarType, 
            unsigned long id = 0>
  struct unknown;

  
  
  
  
  
  /////// constant ///////
  template <typename ScalarType>
  class constant;

  template <long value_>
  class ct_constant;

  
  
  /////// vector ////////
  template <long i>
  struct ct_index {};
  
  template <typename T0>
  class vector_1;
  
  template <typename T0, typename T1>
  class vector_2;
  
  template <typename T0, typename T1, typename T2>
  class vector_3;
 
  
  /////// exceptions ///////
  
  class expression_not_unwrappable : public std::exception
  {
    const char * what() const throw() { return "Expression cannot be unwrapped!"; } 
  };
}

#endif