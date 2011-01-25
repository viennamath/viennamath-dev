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
#include <sstream>

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
    
  class binary_expr;

  class op_interface;

  //class expression_interface;
  //interface for dispatches:
  class expression_interface
  {
    public:
      virtual ~expression_interface() {}
      
      virtual expression_interface * clone() const = 0;
      virtual std::string str() const = 0;
      virtual numeric_type eval(std::vector<double> const & v) const = 0;
      virtual numeric_type eval(numeric_type val) const = 0;
      virtual expression_interface * optimize() { return this; }
      virtual bool is_unary() const { return true; }
      
      /** @brief Returns true, if the expression can be evaluated without providing values for variables (i.e. the expression is a constant) */
      virtual bool is_constant() const { return false; }
      
      virtual numeric_type unwrap() const = 0;
      virtual expression_interface * substitute(const expression_interface * e,
                                                const expression_interface * repl) const = 0;
                                                
      virtual bool equal(const expression_interface *) const = 0;
      
      virtual const expression_interface * lhs() const { return this; };
      virtual const op_interface * op() { return NULL; }  //primitives do not have an operator
      virtual const expression_interface * rhs() const { return NULL; } //unary expressions do not have a right-hand side


      virtual const expression_interface * diff(const expression_interface * diff_var) const = 0;
  };
 
/*
  expr operator+(expr const & lhs, expr const & rhs);
  expr operator-(expr const & lhs, expr const & rhs);
  expr operator*(expr const & lhs, expr const & rhs);
  expr operator/(expr const & lhs, expr const & rhs); */
  
  
  
  
  
  /////// interface for op_tags: ///////
  class op_interface
  {
    public:
      virtual ~op_interface() {}
      
      virtual op_interface * clone() const = 0;
      virtual std::string str() const = 0;
      virtual numeric_type apply(expression_interface * lhs,
                                 expression_interface * rhs,
                                 std::vector<numeric_type> const & v) const  = 0;
      virtual numeric_type apply(expression_interface * lhs,
                                 expression_interface * rhs,
                                 numeric_type val) const  = 0;
                         
      virtual numeric_type apply(numeric_type lhs, numeric_type rhs) const = 0;                   
      virtual bool is_unary() const { return false; }
      
      virtual const expression_interface * diff(const expression_interface * lhs,
                                                const expression_interface * rhs,
                                                const expression_interface * diff_var) const  = 0;
  };
  
  //binary operator tags:  
  struct op_plus;
  struct op_minus;
  struct op_mult;
  struct op_div;
  struct op_pow;

  //unary operator tags
  template <typename unary_operation>
  class op_unary : public op_interface
  {
    public: 
      //TODO: deduce return type
      //template <typename LHS, typename RHS>
      //static void apply(LHS const & lhs, RHS const & rhs) { return lhs; }
      
      
      //run time stuff:
      std::string str() const { return unary_operation::str(); }
      op_interface * clone() const { return new op_unary<unary_operation>(); }
      virtual numeric_type apply(expression_interface * lhs,
                                 expression_interface * rhs,
                                 std::vector<numeric_type> const & v) const  { return unary_op_.apply(lhs->eval(v)); }
      virtual numeric_type apply(expression_interface * lhs,
                                 expression_interface * rhs,
                                 numeric_type val) const   { return unary_op_.apply(lhs->eval(val)); }
      numeric_type apply(numeric_type lhs, numeric_type rhs) const { return unary_op_.apply(lhs); }
      bool is_unary() const { return true; }
      
      const expression_interface * diff(const expression_interface * lhs,
                                        const expression_interface * rhs,
                                        const expression_interface * diff_var) const { return unary_operation::diff(lhs, diff_var); }
    
    private:
      //We use a unary_operation member, because the unary_operation tag might have a state -> pure static tag dispatch not enough.
      unary_operation unary_op_;
  };

  struct op_id {};
  
  //separate treatment of identity:
  template <>
  struct op_unary<op_id> : public op_interface
  {
    //TODO: deduce return type
    //template <typename LHS, typename RHS>
    //static void apply(LHS const & lhs, RHS const & rhs) { return lhs; }
    
    
    //run time stuff:
    std::string str() const { return "id"; }
    op_interface * clone() const;
    virtual numeric_type apply(expression_interface * lhs,
                               expression_interface * rhs,
                               std::vector<numeric_type> const & v) const  { return lhs->eval(v); }
    virtual numeric_type apply(expression_interface * lhs,
                               expression_interface * rhs,
                               numeric_type val) const   { return lhs->eval(val); }
    numeric_type apply(numeric_type lhs, numeric_type rhs) const { return lhs; }
    bool is_unary() const { return true; }
    
    const expression_interface * diff(const expression_interface * lhs,
                                      const expression_interface * rhs,
                                      const expression_interface * diff_var) const { return lhs->diff(diff_var); }
  };

  
  struct op_exp;
  struct op_sin;
  struct op_cos;
  struct op_tan;
  struct op_fabs;
  struct op_sqrt;
  struct op_log; //natural logarithm
  struct op_log10;

  
  //helper: deduce return type:
  template <typename RHS, typename LHS>
  struct op_return_type
  {
    typedef numeric_type      return_type;
  };
    
  
  
  
  
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
  
  class unknown_index_out_of_bounds : public std::exception
  {
    const char * what() const throw()
    {
      std::stringstream ss;
      ss << "Encountered an unknown<> type with id larger or equal to the size of the supplied vector of values. id=" << id_ << ", vector_size=" << vector_size_ << std::endl;
      return ss.str().c_str(); } 
    
    public:
      unknown_index_out_of_bounds(long id, long vector_size) : id_(id), vector_size_(vector_size) {}
      
    private:
      long id_;
      long vector_size_;
  };
  
}

#endif