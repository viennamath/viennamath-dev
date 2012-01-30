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
  typedef double              default_numeric_type;
  typedef unsigned long       id_type;
  
  //////// utils /////
  /** @brief Simple enable-if variant that uses the SFINAE pattern */
  template <bool b, class T = void> 
  struct enable_if
  {
    typedef T   type;
  };

  template <class T> 
  struct enable_if<false, T> {};
  

  //allows to use plain numeric_type with template operator+, operator-, operator*, operator/ without running into problems with ambiguity
  //
  // example:
  // operator+(expr e, numeric_t val);
  //
  // template <typename ScalarType>
  // operator+(expr e, ct_constant<value>); 
  //
  // lead to ambiguity for e + 4;
  template <typename NumericT>
  class numeric_type_proxy
  {
    public:
      numeric_type_proxy(NumericT value) : value_(value) {}
      
      NumericT get() const { return value_; }
    private:
      NumericT value_;
  };

  // integral tags
  struct symbolic_interval {};
  struct symbolic_tag {};
  
  
  /////// compile time expression stuff ///////
  template <typename LHS,
            typename OP,
            typename RHS>
  class ct_expr;
  
  template <long value_>
  class ct_constant;

  template <unsigned long id = 0>
  struct ct_variable;

  template <typename Tag>
  class ct_function_symbol;

  // compile time vector
  template <long i>
  struct ct_index {};
  
  template <typename T0>
  class ct_vector_1;
  
  template <typename T0, typename T1>
  class ct_vector_2;
  
  template <typename T0, typename T1, typename T2>
  class ct_vector_3;
 
  
  /////// run time expression stuff ///////

  template <typename NumericT>
  class rt_expression_interface;
  
  typedef rt_expression_interface<default_numeric_type>     default_interface_type;
  
  template <typename InterfaceType = default_interface_type>
  struct rt_variable;
  typedef rt_variable<>                variable;

  template <typename ScalarType = default_numeric_type, typename InterfaceType = default_interface_type>
  class rt_constant;
  typedef rt_constant<>                constant;
  
  template <typename InterfaceType = default_interface_type>
  class rt_binary_expr;  
  typedef rt_binary_expr<>             binary_expr;
  
  template <typename InterfaceType = default_interface_type>
  class rt_unary_expr;
  typedef rt_unary_expr<>              unary_expr;
  
  template <typename InterfaceType = default_interface_type>
  class rt_expr;
  typedef rt_expr<>                    expr;
  
  template <typename InterfaceType = default_interface_type>
  class rt_function_symbol;
  typedef rt_function_symbol<>         function_symbol;

  /////// equation types /////////
  template <typename LHS, typename RHS>
  class ct_equation;
  
  template <typename InterfaceType = default_interface_type>
  class rt_equation;
  typedef rt_equation<>                equation;

  template <typename InterfaceType = default_interface_type>
  class rt_interval;
  typedef rt_interval<>                interval;
  
  
  
  
  template <typename InterfaceType = default_interface_type>   //Note: No convenience typedef needed here
  class rt_manipulation_interface;

  template <typename InterfaceType = default_interface_type>   //Note: No convenience typedef needed here
  class rt_manipulation_wrapper;
  
  template <typename InterfaceType = default_interface_type>   //Note: No convenience typedef needed here
  class rt_traversal_interface;
  
  template <typename InterfaceType = default_interface_type>   //Note: No convenience typedef needed here
  class rt_traversal_wrapper;
  
  
  /////// interface for op_tags: ///////
  template <typename InterfaceType = default_interface_type>
  class rt_op_interface;

  //binary operator tags:  
  template <typename BinaryOperation, typename InterfaceType = default_interface_type>
  class op_binary;
  
  template <typename NumericT>
  struct op_plus;
  
  template <typename NumericT>
  struct op_minus;
  
  template <typename NumericT>
  struct op_mult;
  
  template <typename NumericT>
  struct op_div;
  
  template <typename NumericT>
  struct op_pow;

  
  
  
  ////// unary operator tags:
  template <typename unary_operation, typename InterfaceType = default_interface_type>
  class op_unary;

  
  template <typename NumericT>
  struct op_id;
  
  template <typename NumericT>
  struct op_exp;
  
  template <typename NumericT>
  struct op_sin;
  
  template <typename NumericT>
  struct op_cos;
  
  template <typename NumericT>
  struct op_tan;
  
  template <typename NumericT>
  struct op_fabs;
  
  template <typename NumericT>
  struct op_sqrt;
  
  template <typename NumericT>
  struct op_log; //natural logarithm
  
  template <typename NumericT>
  struct op_log10;

  template <typename NumericT>
  struct op_partial_deriv;
  
  template <typename InterfaceType>
  class op_rt_integral;
  
  namespace result_of
  {
    template <typename T>
    struct is_viennamath
    {
      enum { val = false };
    };
    
    template <long value>
    struct is_viennamath<ct_constant<value> >
    {
      enum { val = true };
    };
    
    template <id_type id>
    struct is_viennamath<ct_variable<id> >
    {
      enum { val = true };
    };

    template <typename LHS, typename OP, typename RHS>
    struct is_viennamath<ct_expr<LHS, OP, RHS> >
    {
      enum { val = true };
    };

    template <typename NumericType, typename InterfaceType>
    struct is_viennamath<rt_constant<NumericType, InterfaceType> >
    {
      enum { val = true };
    };
    
    template <typename InterfaceType>
    struct is_viennamath<rt_variable<InterfaceType> >
    {
      enum { val = true };
    };

    template <typename InterfaceType>
    struct is_viennamath<rt_unary_expr<InterfaceType> >
    {
      enum { val = true };
    };
    
    template <typename InterfaceType>
    struct is_viennamath<rt_binary_expr<InterfaceType> >
    {
      enum { val = true };
    };
    
    template <typename InterfaceType>
    struct is_viennamath<rt_expr<InterfaceType> >
    {
      enum { val = true };
    };
    
    
    
    template <typename T>
    struct is_compiletime
    {
      enum { val = false };
    };
    
    template <long value>
    struct is_compiletime<ct_constant<value> >
    {
      enum { val = true };
    };
    
    template <id_type id>
    struct is_compiletime<ct_variable<id> >
    {
      enum { val = true };
    };

    template <typename LHS, typename OP, typename RHS>
    struct is_compiletime<ct_expr<LHS, OP, RHS> >
    {
      enum { val = true };
    };

    
    template <typename LHS, typename RHS>
    struct interface
    {
      typedef default_interface_type  type; //for compatibility with enable_if
    };

    template <typename T, typename U, typename RHS>
    struct interface< rt_constant<T, U>, RHS >
    {
      typedef U    type;
    };

    template <typename T, typename RHS>
    struct interface< rt_variable<T>, RHS >
    {
      typedef T    type;
    };

    template <typename T>
    struct interface< double, rt_variable<T> >
    {
      typedef T    type;
    };

    template <typename T, typename RHS>
    struct interface< rt_binary_expr<T>, RHS >
    {
      typedef T    type;
    };

    template <typename T>
    struct interface< double, rt_binary_expr<T> >
    {
      typedef T    type;
    };

    template <typename T, typename RHS>
    struct interface< rt_unary_expr<T>, RHS >
    {
      typedef T    type;
    };
    
    template <typename T, typename RHS>
    struct interface< rt_expr<T>, RHS >
    {
      typedef T    type;
    };

    template <typename T>
    struct interface< double,  rt_expr<T> >
    {
      typedef T    type;
    };
    
    template <typename LHS,
              typename RHS,
              bool lhs_is_ct = is_compiletime<LHS>::val,
              bool rhs_is_ct = is_compiletime<RHS>::val>
    struct add;
    
    template <typename LHS,
              typename RHS,
              bool lhs_is_ct = is_compiletime<LHS>::val,
              bool rhs_is_ct = is_compiletime<RHS>::val>
    struct subtract;
    
    template <typename LHS,
              typename RHS,
              bool lhs_is_ct = is_compiletime<LHS>::val,
              bool rhs_is_ct = is_compiletime<RHS>::val>
    struct mult;

    template <typename LHS,
              typename RHS,
              bool lhs_is_ct = is_compiletime<LHS>::val,
              bool rhs_is_ct = is_compiletime<RHS>::val>
    struct div;
    
  } //namespace result_of
  
  template <typename LHS, typename RHS>
  typename enable_if< result_of::is_viennamath<LHS>::val || result_of::is_viennamath<RHS>::val,
                      typename result_of::add<LHS, RHS>::type >::type
  operator+(LHS const & lhs, RHS const & rhs)
  {
    return result_of::add<LHS, RHS>::instance(lhs, rhs); 
  }
  
  template <typename LHS, typename RHS>
  typename enable_if< result_of::is_viennamath<LHS>::val || result_of::is_viennamath<RHS>::val,
                      typename result_of::subtract<LHS, RHS>::type >::type
  operator-(LHS const & lhs, RHS const & rhs)
  {
    return result_of::subtract<LHS, RHS>::instance(lhs, rhs); 
  }

  template <typename LHS, typename RHS>
  typename enable_if< result_of::is_viennamath<LHS>::val || result_of::is_viennamath<RHS>::val,
                      typename result_of::mult<LHS, RHS>::type >::type
  operator*(LHS const & lhs, RHS const & rhs)
  {
    return result_of::mult<LHS, RHS>::instance(lhs, rhs); 
  }
  
  template <typename LHS, typename RHS>
  typename enable_if< result_of::is_viennamath<LHS>::val || result_of::is_viennamath<RHS>::val,
                      typename result_of::div<LHS, RHS>::type >::type
  operator/(LHS const & lhs, RHS const & rhs)
  {
    return result_of::div<LHS, RHS>::instance(lhs, rhs); 
  }

  /////// exceptions ///////
  
  //TODO: Is this needed here? Maybe collect exceptions in a separate file.
  
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
