/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_RUNTIME_OPERATIONS_RT_RT_HPP
#define VIENNAMATH_RUNTIME_OPERATIONS_RT_RT_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/runtime/binary_expression.hpp"

namespace viennamath
{
  
  namespace traits
  {
    template <typename InterfaceType, typename NumericT>
    InterfaceType * clone(rt_constant<NumericT, InterfaceType> const & c) { return c.clone(); }    

    template <typename InterfaceType>
    InterfaceType * clone(default_numeric_type d) { return new rt_constant<default_numeric_type, InterfaceType>(d); }    

    template <typename InterfaceType, long value>
    InterfaceType * clone(ct_constant<value> const & c) { return new rt_constant<default_numeric_type, InterfaceType>(value); }    

    template <typename InterfaceType>
    InterfaceType * clone(rt_variable<InterfaceType> const & v) { return v.clone(); }    

    template <typename InterfaceType, id_type id>
    InterfaceType * clone(ct_variable<id> const & v) { return new rt_variable<InterfaceType>(id); }    

    template <typename InterfaceType>
    InterfaceType * clone(rt_unary_expr<InterfaceType> const & e) { return e.clone(); }    

    template <typename InterfaceType>
    InterfaceType * clone(rt_binary_expr<InterfaceType> const & e) { return e.clone(); }    

    template <typename InterfaceType>
    InterfaceType * clone(rt_expr<InterfaceType> const & e) { return e.get()->clone(); }    

    template <typename InterfaceType, typename LHS, typename OP, typename RHS>
    InterfaceType * clone(ct_expr<LHS, OP, RHS> const & e) { return new rt_binary_expr<InterfaceType>(e); } 

  }
  
  
  namespace result_of
  {
    
    template <typename LHS, typename RHS, bool b1, bool b2>
    struct add
    {
      typedef typename interface<LHS, RHS>::type     iface_type;
      typedef typename iface_type::numeric_type      numeric_type;
      typedef rt_binary_expr<iface_type>             type;
      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(traits::clone<iface_type>(lhs), new op_binary<op_plus<numeric_type>, iface_type>(), traits::clone<iface_type>(rhs)); }
    };

    template <typename LHS, typename RHS, bool b1, bool b2>
    struct subtract
    {
      typedef typename interface<LHS, RHS>::type     iface_type;
      typedef typename iface_type::numeric_type      numeric_type;
      typedef rt_binary_expr<iface_type>             type;
      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(traits::clone<iface_type>(lhs), new op_binary<op_minus<numeric_type>, iface_type>(), traits::clone<iface_type>(rhs)); }
    };

    template <typename LHS, typename RHS, bool b1, bool b2>
    struct mult
    {
      typedef typename interface<LHS, RHS>::type     iface_type;
      typedef typename iface_type::numeric_type      numeric_type;
      typedef rt_binary_expr<iface_type>             type;
      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(traits::clone<iface_type>(lhs), new op_binary<op_mult<numeric_type>, iface_type>(), traits::clone<iface_type>(rhs)); }
    };

    template <typename LHS, typename RHS, bool b1, bool b2>
    struct div
    {
      typedef typename interface<LHS, RHS>::type     iface_type;
      typedef typename iface_type::numeric_type      numeric_type;
      typedef rt_binary_expr<iface_type>             type;
      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(traits::clone<iface_type>(lhs), new op_binary<op_div<numeric_type>, iface_type>(), traits::clone<iface_type>(rhs)); }
    };
    
  }
  
  
  
  
}

#endif