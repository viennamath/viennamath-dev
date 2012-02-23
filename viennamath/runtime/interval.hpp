#ifndef VIENNAMATH_RUNTIME_INTERVAL_HPP
#define VIENNAMATH_RUNTIME_INTERVAL_HPP

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




#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  /** @brief A runtime rt_interval */
  template <typename InterfaceType>
  class rt_interval
  {

    public:
      typedef rt_expr<InterfaceType>                  value_type;
      typedef InterfaceType                           interface_type;
      typedef typename InterfaceType::numeric_type    numeric_type;
      
      explicit rt_interval() : lower_(new rt_constant<numeric_type, InterfaceType>(0)),
                               upper_(new rt_constant<numeric_type, InterfaceType>(1)) {} 
      
      explicit rt_interval(const rt_expr<InterfaceType> & a,
                           const rt_expr<InterfaceType> & b) : lower_(a.get()->clone()),
                                                               upper_(b.get()->clone()) {}
                           
      rt_interval(rt_interval const & other) : lower_(other.lower_.get()->clone()),
                                               upper_(other.upper_.get()->clone()) {}
      
      rt_expr<InterfaceType> const & lower() const { return lower_; }
      rt_expr<InterfaceType> const & upper() const { return upper_; }

      rt_interval const & operator=(rt_interval const & other)
      {
        lower_ = other.lower().get()->clone();
        upper_ = other.upper().get()->clone();
      };
      
    private:
      rt_expr<InterfaceType> lower_;
      rt_expr<InterfaceType> upper_;
  };

  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, rt_interval<InterfaceType> const & e)
  {
    stream << "interval(" << e.lower() << ", " << e.upper() << ")";
    return stream;
  }
  
  
  
  
  //////// helper functions for creating equations (uniform interface for compile time and run time: ///////////
  
  
  //
  // run time
  //
  
  ////// scalar is first argument:
  inline rt_interval<> make_interval(default_numeric_type lhs, default_numeric_type rhs)
  {
    rt_expr<> a = rt_constant<>(lhs);
    rt_expr<> b = rt_constant<>(rhs);
    return rt_interval<>(a, b); 
  }
  
  template <typename NumericT, typename InterfaceType, typename RHSType>
  rt_interval<InterfaceType> make_interval(typename InterfaceType::numeric_type lhs, rt_constant<NumericT, InterfaceType> const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }
  
  template <typename InterfaceType>
  rt_interval<InterfaceType> make_interval(typename InterfaceType::numeric_type lhs, rt_variable<InterfaceType> const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  template <id_type id>
  rt_interval<> make_interval(default_numeric_type lhs, ct_variable<id> const & rhs)
  {
    return rt_interval<>(lhs, rhs); 
  }

  template <typename InterfaceType>
  rt_interval<InterfaceType> make_interval(typename InterfaceType::numeric_type lhs, rt_unary_expr<InterfaceType> const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  rt_interval<InterfaceType> make_interval(typename InterfaceType::numeric_type lhs, rt_binary_expr<InterfaceType> const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  rt_interval<InterfaceType> make_interval(typename InterfaceType::numeric_type lhs, rt_expr<InterfaceType> const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  
  //constant:
  template <typename NumericT, typename InterfaceType, typename RHSType>
  rt_interval<InterfaceType> make_interval(rt_constant<NumericT, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  //variable:
  template <typename InterfaceType, typename RHSType>
  rt_interval<InterfaceType> make_interval(rt_variable<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  template <id_type id, typename RHSType>
  rt_interval<> make_interval(ct_variable<id> const & lhs, RHSType const & rhs)
  {
    rt_variable<> temp(id);
    return rt_interval<>(temp, rhs); 
  }

  //function_symbol:
  template <typename InterfaceType, typename RHSType>
  rt_interval<InterfaceType> make_interval(rt_function_symbol<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  //unary:
  template <typename InterfaceType, typename RHSType>
  rt_interval<InterfaceType> make_interval(rt_unary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }


  //binary
  template <typename InterfaceType, typename RHSType>
  rt_interval<InterfaceType> make_interval(rt_binary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  //expr
  template <typename InterfaceType, typename RHSType>
  rt_interval<InterfaceType> make_interval(rt_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return rt_interval<InterfaceType>(lhs, rhs); 
  }

  //compile time with run time stuff also possible:
  template <typename LHS, typename OP, typename RHS, typename RHSType>
  rt_interval<typename RHSType::interface_type>
  make_interval(ct_binary_expr<LHS, OP, RHS> const & lhs, RHSType const & rhs)
  {
    return rt_interval<typename RHSType::interface_type>(lhs, rhs); 
  }

  template <typename LHS, typename OP, typename RHSType>
  rt_interval<typename RHSType::interface_type>
  make_interval(ct_unary_expr<LHS, OP> const & lhs, RHSType const & rhs)
  {
    return rt_interval<typename RHSType::interface_type>(lhs, rhs); 
  }

  template <long val, typename RHSType>
  rt_interval<typename RHSType::interface_type>
  make_interval(ct_constant<val> const & lhs, RHSType const & rhs)
  {
    return rt_interval<typename RHSType::interface_type>(lhs, rhs); 
  }

  template <typename TAG, typename RHSType>
  rt_interval<typename RHSType::interface_type>
  make_interval(ct_function_symbol<TAG> const & lhs, RHSType const & rhs)
  {
    return rt_interval<typename RHSType::interface_type>(lhs, rhs); 
  }

  template <id_type id, typename RHSType>
  rt_interval<typename RHSType::interface_type>
  make_interval(ct_variable<id> const & lhs, RHSType const & rhs)
  {
    return rt_interval<typename RHSType::interface_type>(lhs, rhs); 
  }
  
}

#endif