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
      
      std::string str() const
      {
        std::stringstream ss;
        
        ss << "rt_integral[" << interval_ << ", " << integration_variable_ << "]";
        return ss.str();
      }
      
      NumericT apply(NumericT value) const
      {
        std::cout << "TODO: Call integration here!" << std::endl;
        return value;
      }
      
      viennamath::rt_interval<InterfaceType> const & interval() const { return interval_; }
      viennamath::rt_variable<InterfaceType> const & variable() const { return integration_variable_; }
      
    private:
      viennamath::rt_interval<InterfaceType> interval_;
      viennamath::rt_variable<InterfaceType> integration_variable_;
  };
  
  
  //
  // With interval:
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

  template <typename InterfaceType, unsigned long id>
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

}

#endif

