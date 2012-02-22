#ifndef VIENNAMATH_FORWARDS_H
#define VIENNAMATH_FORWARDS_H

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

/**
 @mainpage Source Code Documentation for ViennaMath 1.0.0

 Thank you for downloading ViennaMath!
 These pages provide the Doxygen-generated source code documentation with the many details on the functions implemented in ViennaMath.
 
 For a general overview over the types and functionality provided by ViennaMath, please refer to the file doc/viennamath.pdf. 
 
*/


#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <memory>

/** @file forwards.h
    @brief Contains forward declarations and definition of small classes that must be defined at an early stage
*/

namespace viennamath
{
  //basic numeric type (customize to your needs)
  /** @brief The underlying floating point type to be used in case of doubt (e.g. when new constants are created during manipulation) */
  typedef double              default_numeric_type;
  
  /** @brief Type used for any kind of IDs (variable, etc.) */
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
  

  /** @brief A proxy object which allows for the use of plain default_numeric_type with template operator+, operator-, operator*, operator/ without running into problems with ambiguity. With the proxy object, one additional conversion is required, thus resolving the ambiguity.
   * 
   * example:
   * operator+(expr e, numeric_t val);
   *
   * template <typename ScalarType>
   * operator+(expr e, ct_constant<value>); 
   *
   * lead to ambiguity for e + 4;
   */
  template <typename NumericT>
  class numeric_type_proxy
  {
    public:
      numeric_type_proxy(NumericT value) : value_(value) {}
      
      NumericT get() const { return value_; }
    private:
      NumericT value_;
  };

  //  
  /////// compile time expression types ///////
  //
  
  /** @brief Compiletime representation of an expression consisting of a binary operator and two operands
   * 
   * @tparam LHS    Left hand side operand
   * @tparam OP     The binary operator tag
   * @tparam RHS    Right hand side operand
   */
  template <typename LHS,
            typename OP,
            typename RHS>
  class ct_binary_expr;

  /** @brief Compiletime representation of an expression consisting of a unary operator (e.g. modulus, x^5) and an operand
   * 
   * @tparam LHS   The expression the unary operator is acting on
   * @tparam OP    The unary operator
   */
  template <typename LHS,
            typename OP>
  class ct_unary_expr;
  
  /** @brief Representation of a compiletime constant. Note that C++ does not allow floating point types as template arguments, thus a restriction to integer arithmetic is required 
   * 
   * @tparam value_    The (signed) integer value to be represented
   */
  template <long value_>
  class ct_constant;

  /** @brief Compiletime representation of a variable in the mathematical sense. If evaluated using a vector, returns the 'id'-th entry of the vector.
   * 
   * @tparam id     The index in the vector passed for evaluation of the expression.
   */
  template <id_type id = 0>
  struct ct_variable;

  /** @brief Compiletime representation of a generic placeholder for functions. Cannot be evaluated and is typically substituted by functions at some later stage.
   * 
   * @tparam TAG    A generic identifier tag for the function symbol.
   */
  template <typename Tag>
  class ct_function_symbol;

  /** @brief Compiletime representation of an equation.
   * 
   *  @tparam LHS   Left hand side of the equation
   *  @tparam RHS   Right hand side of the equation
   */
  template <typename LHS, typename RHS>
  class ct_equation;
  

  
  /** @brief Compiletime respresentation of a vector access index. 
   * 
   * @tparam i     The index to be represented at compile time
   */
  template <long i>
  struct ct_index {};
  
  /** @brief Compiletime representation of a vector with one entry
   * 
   * @tparam T0    The entry of the vector
   */
  template <typename T0>
  class ct_vector_1;
  
  /** @brief Compiletime representation of a vector with two entries
   * 
   * @tparam T0    The entry of the vector
   * @tparam T1    Second entry of the vector
   */
  template <typename T0, typename T1>
  class ct_vector_2;
  
  /** @brief Compiletime representation of a vector with three entries
   * 
   * @tparam T0    First entry of the vector
   * @tparam T1    Second entry of the vector
   * @tparam T2    Third entry of the vector
   */
  template <typename T0, typename T1, typename T2>
  class ct_vector_3;
 
  //
  /////// runtime expression types ///////
  //

  /** @brief The abstract expression interface, from which all runtime expression types inherit */
  template <typename NumericT>
  class rt_expression_interface;
  
  /** @brief Convenience type definition for the default expression interface */
  typedef rt_expression_interface<default_numeric_type>     default_interface_type;
  
  /** @brief Runtime representation of a variable in the mathematical sense. Represents the 'i'-th coordinate in the Euclidian space, where 'i'
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  struct rt_variable;
  typedef rt_variable<>                variable;

  /** @brief Runtime representation of a constant value expression
   *
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */ 
  template <typename ScalarType = default_numeric_type, typename InterfaceType = default_interface_type>
  class rt_constant;
  typedef rt_constant<>                constant;

  /** @brief Runtime representation of an expression consisting of a binary operator and two operands. Usually not instantiated by the library user.
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_binary_expr;  
  typedef rt_binary_expr<>             binary_expr;
  
  /** @brief Runtime representation of an expression consisting of a unary operator and one operand. Usually not instantiated by the library user.
   *
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_unary_expr;
  typedef rt_unary_expr<>              unary_expr;
  
  /** @brief Generic runtime expression class. Can hold any other runtime expression type and simplifies the handling of ViennaMath expressions for the library user.
   * 
   * Can be seen as a smart-pointer for objects which inherit from InterfaceType.
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_expr;
  typedef rt_expr<>                    expr;
  
  /** @brief 
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_vector_expr; 
  typedef rt_vector_expr<>             vector_expr;
  
  /** @brief Runtime representation of a generic placeholder for functions. Cannot be evaluated and is typically substituted by functions at some later stage.
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_function_symbol;
  typedef rt_function_symbol<>         function_symbol;

  /** @brief Runtime representation of an equation.
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_equation;
  typedef rt_equation<>                equation;

  /** @brief Runtime representation of an interval [a,b].
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_interval;
  typedef rt_interval<>                interval;

  /** @brief Runtime representation of a symbolic interval. Similar to function symbols, symbolic intervals are later on replaced by rt_interval objects.
   * 
   * @tparam InterfaceType    The interface to inherit from. Usually rt_expression_interface, but extensions are possible.
   */
  template <typename InterfaceType = default_interface_type>
  class rt_symbolic_interval;
  typedef rt_symbolic_interval<>       symbolic_interval;
  
  
  
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

  template <typename InterfaceType>
  class op_rt_symbolic_integral;
  

  //
  // LaTeX processing
  //
  template <typename InterfaceType = default_interface_type>
  class rt_latex_translator;
  
  template <typename InterfaceType = default_interface_type>
  class rt_latex_binary_expr_processor;

  template <typename InterfaceType = default_interface_type>
  class rt_latex_unary_expr_processor;

  template <typename InterfaceType = default_interface_type>
  class rt_latex_constant_processor;

  template <typename InterfaceType = default_interface_type>
  class rt_latex_variable_processor;

  template <typename InterfaceType = default_interface_type>
  class rt_latex_function_symbol_processor;


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
    struct is_viennamath<ct_binary_expr<LHS, OP, RHS> >
    {
      enum { val = true };
    };

    template <typename LHS, typename OP>
    struct is_viennamath<ct_unary_expr<LHS, OP> >
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
    struct is_viennamath<rt_function_symbol<InterfaceType> >
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
    struct is_compiletime<ct_binary_expr<LHS, OP, RHS> >
    {
      enum { val = true };
    };

    template <typename LHS, typename OP>
    struct is_compiletime<ct_unary_expr<LHS, OP> >
    {
      enum { val = true };
    };

    template <typename TAG>
    struct is_compiletime<ct_function_symbol<TAG> >
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
    
    
    // greatest common divisor:
    template <long a, long b>
    struct gcd
    {
      enum { value = gcd<b, a % b>::value };
    };
    
    template <long a>
    struct gcd <a, 0>
    {
      enum { value = a};
    };

    template <>
    struct gcd <0, 0>
    {
      enum { value = 1};
    };
    
    
  } //namespace result_of
  
  
    
  template <typename T>
  struct expression_traits
  {
    typedef T   const_reference_type; 
  };
  
  //for compile time constants, we have to copy in order to circumvent problems with temporaries
  template <long value>
  struct expression_traits < ct_constant<value> >
  {
     typedef ct_constant<value>    const_reference_type;
  };

  template <typename T, typename InterfaceType>
  struct expression_traits < rt_constant<T, InterfaceType> >
  {
     typedef rt_constant<T, InterfaceType>    const_reference_type;
  };
  

  
  
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
