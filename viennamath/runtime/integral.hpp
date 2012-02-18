/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_RUNTIME_INTEGRAL_HPP
#define VIENNAMATH_RUNTIME_INTEGRAL_HPP

#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  //
  // Part 1: Concrete intervals
  //
  
  
  template <typename InterfaceType>
  class op_rt_integral
  {
      typedef typename InterfaceType::numeric_type    NumericT;
    
    public:
      typedef InterfaceType         interface_type;

      op_rt_integral() : integration_variable_(0) {}

      op_rt_integral(viennamath::rt_interval<InterfaceType> const & interv,
                     viennamath::rt_variable<InterfaceType> const & var) : interval_(interv),
                                                                           integration_variable_(var) {}

      template <id_type id>
      op_rt_integral(viennamath::rt_interval<InterfaceType> const & interv,
                     viennamath::ct_variable<id> const & var) : interval_(interv),
                                                                integration_variable_(id) {}

      std::string str() const
      {
        std::stringstream ss;
        
        ss << "rt_integral[" << interval_ << ", " << integration_variable_ << "]";
        return ss.str();
      }
      
      NumericT apply(NumericT value) const
      {
        //std::cout << "TODO: Call integration here!" << std::endl;
        throw "Must not reach this point!";
        return value;
      }
      
      bool optimizable() const { return false; }
      
      viennamath::rt_interval<InterfaceType> const & interval() const { return interval_; }
      viennamath::rt_variable<InterfaceType> const & variable() const { return integration_variable_; }
      
    private:
      viennamath::rt_interval<InterfaceType> interval_;
      viennamath::rt_variable<InterfaceType> integration_variable_;
  };
  
  
  
  //
  // Convenience functions with rt_interval:
  //
  template <typename InterfaceType>
  rt_expr<InterfaceType> integral(rt_interval<InterfaceType> const & interv,
                                  rt_expr<InterfaceType> const & integrand,
                                  rt_variable<InterfaceType> const & var)
  {
    typedef op_rt_integral<InterfaceType>    OperatorT;
    OperatorT op(interv, var);
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.get()->clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(op))
                                 );
  }

  template <typename InterfaceType, id_type id>
  rt_expr<InterfaceType> integral(rt_interval<InterfaceType> const & interv,
                                  rt_expr<InterfaceType> const & integrand,
                                  ct_variable<id> const & var)
  {
    typedef op_rt_integral<InterfaceType>    OperatorT;
    OperatorT op(interv, rt_variable<InterfaceType>(id));
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.get()->clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(op))
                                 );
  }

  template <typename InterfaceType, id_type id>
  rt_expr<InterfaceType> integral(rt_interval<InterfaceType> const & interv,
                                  rt_binary_expr<InterfaceType> const & integrand,
                                  ct_variable<id> const & var)
  {
    typedef op_rt_integral<InterfaceType>    OperatorT;
    OperatorT op(interv, rt_variable<InterfaceType>(id));
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(op))
                                 );
  }
  
  
  //
  // Part 2: Symbolic integrals
  //
  
  
  template <typename InterfaceType>
  class op_rt_symbolic_integral
  {
      typedef typename InterfaceType::numeric_type    NumericT;
    
    public:
      typedef InterfaceType         interface_type;

      op_rt_symbolic_integral() {}

      op_rt_symbolic_integral(viennamath::rt_symbolic_interval<InterfaceType> const & interv) : interval_(interv) {}
      
      std::string str() const
      {
        std::stringstream ss;
        
        ss << "symbolic_integral[" << interval_ << "]";
        return ss.str();
      }
      
      NumericT apply(NumericT value) const
      {
        //std::cout << "TODO: Call integration here!" << std::endl;
        throw "Must not reach this point!";
        return value;
      }
      
      bool optimizable() const { return false; }
      
      viennamath::rt_symbolic_interval<InterfaceType> const & interval() const { return interval_; }
      
    private:
      viennamath::rt_symbolic_interval<InterfaceType> interval_;
  };
  
  
  //
  // Convenience functions with symbolic integrals
  //
  template <typename InterfaceType>
  rt_expr<InterfaceType> integral(rt_symbolic_interval<InterfaceType> const & interv,
                                  rt_expr<InterfaceType> const & integrand)
  {
    typedef op_rt_symbolic_integral<InterfaceType>    OperatorT;
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.get()->clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(OperatorT(interv)))
                                 );
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> integral(rt_symbolic_interval<InterfaceType> const & interv,
                                  rt_binary_expr<InterfaceType> const & integrand)
  {
    typedef op_rt_symbolic_integral<InterfaceType>    OperatorT;
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(OperatorT(interv)))
                                 );
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> integral(rt_symbolic_interval<InterfaceType> const & interv,
                                  rt_unary_expr<InterfaceType> const & integrand)
  {
    typedef op_rt_symbolic_integral<InterfaceType>    OperatorT;
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(OperatorT(interv)))
                                 );
  }

  template <typename InterfaceType, typename T>
  rt_expr<InterfaceType> integral(rt_symbolic_interval<InterfaceType> const & interv,
                                  rt_constant<T, InterfaceType> const & integrand)
  {
    typedef op_rt_symbolic_integral<InterfaceType>    OperatorT;
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(OperatorT(interv)))
                                 );
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> integral(rt_symbolic_interval<InterfaceType> const & interv,
                                  rt_variable<InterfaceType> const & integrand)
  {
    typedef op_rt_symbolic_integral<InterfaceType>    OperatorT;
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(OperatorT(interv)))
                                 );
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> integral(rt_symbolic_interval<InterfaceType> const & interv,
                                  rt_function_symbol<InterfaceType> const & integrand)
  {
    typedef op_rt_symbolic_integral<InterfaceType>    OperatorT;
    
    return rt_expr<InterfaceType>(new rt_unary_expr<InterfaceType>(integrand.clone(),
                                                                   new op_unary<OperatorT, InterfaceType>(OperatorT(interv)))
                                 );
  }

}

#endif

