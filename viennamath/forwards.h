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
#include <memory>

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
  class ct_expr;
  
  /////// variable ///////
  template <unsigned long id = 0>
  struct variable;

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
 
  template <unsigned long id>
  class unknown_func;

  template <unsigned long id>
  class test_func;
  
  /////// run time expression ///////
    
  class expression_interface;
  class binary_expr;
  class unary_expr;

  /** @brief An tweaked auto_ptr for run time expressions. 
   * 
   * Additionally provides the basic user-interface for evaluation using operator().
   */ 
  class expr
  {
    public:
      expr() {}

      explicit expr(const expression_interface * e) : expr_(e) {}
      
      expr(binary_expr const & other);

      expr(unary_expr const & other);

      template <typename LHS, typename OP, typename RHS>
      expr(ct_expr<LHS, OP, RHS> const & other)
      {
        expr_ = std::auto_ptr<expression_interface>(new binary_expr(other));
      }

      template <unsigned long id>
      expr(variable<id> const & other)
      {
        expr_ = std::auto_ptr<expression_interface>(other.clone());
      }

      template <typename T>
      expr(constant<T> const & other)
      {
        expr_ = std::auto_ptr<expression_interface>(other.clone());
      }
      
      template <unsigned long id>
      expr(test_func<id> const & other)
      {
        expr_ = std::auto_ptr<expression_interface>(other.clone());
      }

      template <long value>
      expr(ct_constant<value> const & other);

      expr(numeric_type_proxy const & other);
      
      //Copy CTOR:
      expr(expr const & other);

      //assignments:    
      expr & operator=(expression_interface * other);
      
      expr & operator=(expr const & other);
      
      template <typename LHS, typename OP, typename RHS>
      expr & operator=(ct_expr<LHS, OP, RHS> const & other); 

      expr & operator=(binary_expr const & other);
      
      template <unsigned long id>
      expr & operator=(variable<id> const & other);

      template <typename ScalarType>
      expr & operator=(constant<ScalarType> const & other);

      template <long value>
      expr & operator=(ct_constant<value> const & other);

      expr & operator=(numeric_type value);

      const expression_interface   * get() const;
      
      ///////////////// evaluation: ///////////////////////////////
      
      //operator() is a convenience layer:
      numeric_type operator()(numeric_type val) const;

      template <typename ScalarType>
      numeric_type operator()(constant<ScalarType> val) const;
      
      template <long value>
      numeric_type operator()(ct_constant<value> val) const;

      template <typename VectorType>
      numeric_type operator()(VectorType const & v) const;

      numeric_type operator()(std::vector<numeric_type> const & stl_v) const;

      template <typename T0>
      numeric_type operator()(viennamath::vector_1<T0> const & v) const;

      template <typename T0, typename T1>
      numeric_type operator()(viennamath::vector_2<T0, T1> const & v) const;
      
      template <typename T0, typename T1, typename T2>
      numeric_type operator()(viennamath::vector_3<T0, T1, T2> const & v) const;
      
    private:
      std::auto_ptr<const expression_interface>  expr_;
  };
  
  class op_interface;

  //class expression_interface;
  //interface for dispatches:
  class expression_interface
  {
    public:
      virtual ~expression_interface() {}
      
      virtual expression_interface * clone() const = 0;  //receiver owns pointer!
      virtual std::string str() const = 0;
      virtual numeric_type eval(std::vector<double> const & v) const = 0;
      virtual numeric_type eval(numeric_type val) const = 0;
      virtual expression_interface * optimize() const { return clone(); }  //receiver owns pointer!
      virtual bool optimizable() const { return false; }      
      
      virtual bool is_unary() const { return true; }
      
      /** @brief Returns true, if the expression can be evaluated without providing values for variables (i.e. the expression is a constant) */
      virtual bool is_constant() const { return false; }
      
      virtual numeric_type unwrap() const = 0;
      virtual expression_interface * substitute(const expr & e,
                                                const expr & repl) const = 0;  //receiver owns pointer!
                                                
      virtual bool equal(const expression_interface * other) const = 0;
      
      virtual const expression_interface * lhs() const { return this; };
      virtual const op_interface * op() { return NULL; }  //primitives do not have an operator
      virtual const expression_interface * rhs() const { return NULL; } //unary expressions do not have a right-hand side


      virtual expression_interface * diff(const expr & diff_var) const = 0;   //receiver owns pointer!
  };
 
  
  
  
  
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
      virtual bool is_unary() const { return true; }
      
      virtual expression_interface * diff(const expression_interface * lhs,
                                          const expression_interface * rhs,
                                          const expr & diff_var) const  = 0;
                                          
      //optimization for binary operators:
      virtual expression_interface * optimize(const expression_interface * lhs,
                                              const expression_interface * rhs) const;  //default defined in binary_expression.hpp

      //optimization for unary operators:
      //virtual expression_interface * optimize(const expression_interface * lhs) const { return lhs->optimize(); }
      virtual bool optimizable(const expression_interface * lhs,
                               const expression_interface * rhs) const { return false; }    
                               
      virtual bool equal(const op_interface * other) const = 0;
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
      
      expression_interface * diff(const expression_interface * lhs,
                                  const expression_interface * rhs,
                                  const expr & diff_var) const
      {
        return unary_operation::diff(lhs, diff_var);
      }
      
      bool equal(const op_interface * other) const
      {
        return (dynamic_cast<const op_unary<unary_operation> *>(other) != NULL); 
      }
      
    
    private:
      //We use an unary_operation member, because the unary_operation tag might have a state -> pure static tag dispatch not enough.
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
    
    expression_interface * diff(const expression_interface * lhs,
                                const expression_interface * rhs,
                                const expr & diff_var) const { return lhs->diff(diff_var); }
                                
    bool equal(const op_interface * other) const
    {
      return (dynamic_cast<const op_unary<op_id> *>(other) != NULL); 
    }
                                
  };

  
  struct op_exp;
  struct op_sin;
  struct op_cos;
  struct op_tan;
  struct op_fabs;
  struct op_sqrt;
  struct op_log; //natural logarithm
  struct op_log10;

  template <unsigned long id>
  struct op_partial_deriv;
  
  //helper: deduce return type:
  template <typename RHS, typename LHS>
  struct op_return_type
  {
    typedef numeric_type      return_type;
  };
    
  
  
  
  /////// equation types /////////
  template <typename LHS, typename RHS>
  class ct_equation;
  
  
  class equation;
  
  
  
  /////// exceptions ///////
  
  class expression_not_unwrappable : public std::exception
  {
    const char * what() const throw() { return "Expression cannot be unwrapped!"; } 
  };
  
  class variable_index_out_of_bounds : public std::exception
  {
    const char * what() const throw()
    {
      std::stringstream ss;
      ss << "Encountered an variable<> type with id larger or equal to the size of the supplied vector of values. id=" << id_ << ", vector_size=" << vector_size_ << std::endl;
      return ss.str().c_str(); } 
    
    public:
      variable_index_out_of_bounds(long id, long vector_size) : id_(id), vector_size_(vector_size) {}
      
    private:
      long id_;
      long vector_size_;
  };
  
}

#endif