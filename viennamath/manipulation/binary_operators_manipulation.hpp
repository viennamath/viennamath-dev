/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_BINARY_OPERATORS_MANIPULATION_HPP
#define VIENNAMATH_BINARY_OPERATORS_MANIPULATION_HPP

#include <string>
#include <vector>
#include <math.h>
#include "viennamath/forwards.h"
#include "viennamath/compiletime/binary_op_tags.hpp"
#include "viennamath/runtime/binary_expression.hpp"
#include "viennamath/runtime/unary_expression.hpp"

namespace viennamath
{

  
  //
  // addition
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_plus<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var)
  {
      return new binary_expr<InterfaceType>( lhs->diff(diff_var),
                                             new op_binary<op_plus<NumericT>, InterfaceType>(),
                                             rhs->diff(diff_var) );
  }
  
  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_plus<NumericT>, const InterfaceType * rhs)
  {
        if (lhs->is_constant())
        {
          NumericT val = lhs->unwrap();
          if (val == 0.0)
            return rhs->optimize();
          
          return new binary_expr<InterfaceType>(new constant<NumericT, InterfaceType>(val),
                                                new op_binary<op_plus<NumericT>, InterfaceType>(),
                                                rhs->optimize());
        }
        else if (rhs->is_constant())
        {
          NumericT val = rhs->unwrap();
          if (val == 0.0)
            return lhs->optimize();
          
          return new binary_expr<InterfaceType>(lhs->optimize(),
                                                new op_binary<op_plus<NumericT>, InterfaceType>(),
                                                new constant<NumericT, InterfaceType>(val));
        }
        
        return new binary_expr<InterfaceType>(lhs->optimize(),
                                              new op_binary<op_plus<NumericT>, InterfaceType>(),
                                              rhs->optimize());
  }
  
  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_plus<NumericT>, const InterfaceType * rhs)
  {
      if (lhs->is_constant())
      {
        if (lhs->unwrap() == 0.0)
        {
          //std::cout << "optimizable: true in op_plus" << std::endl;
          return true;
        }
      }
      if (rhs->is_constant())
      {
        if (rhs->unwrap() == 0.0)
        {
          //std::cout << "optimizable: true in op_plus" << std::endl;
          return true;
        }
      }
      return lhs->optimizable() || rhs->optimizable();
  }
  
  
  
  
  //
  // subtraction
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_minus<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var)
  {
      return new binary_expr<InterfaceType>( lhs->diff(diff_var),
                                             new op_binary<op_minus<NumericT>, InterfaceType>(),
                                             rhs->diff(diff_var) );
  }
  
  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_minus<NumericT>, const InterfaceType * rhs)
  {
        if (lhs->is_constant())
        {
          NumericT val = lhs->unwrap();
          if (val == 0.0)
          {
            return new binary_expr<InterfaceType>(new constant<NumericT, InterfaceType>(-1),
                                                  new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                  rhs->optimize());
          }
          
          return new binary_expr<InterfaceType>(new constant<NumericT, InterfaceType>(val),
                                                new op_binary<op_minus<NumericT>, InterfaceType>(),
                                                rhs->optimize());
        }
        else if (rhs->is_constant())
        {
          NumericT val = rhs->unwrap();
          if (val == 0.0)
            return lhs->optimize();
          
          return new binary_expr<InterfaceType>(lhs->optimize(),
                                                new op_binary<op_minus<NumericT>, InterfaceType>(),
                                                new constant<NumericT, InterfaceType>(val));
        }
        
        return new binary_expr<InterfaceType>(lhs->optimize(),
                                              new op_binary<op_minus<NumericT>, InterfaceType>(),
                                              rhs->optimize());
  }
  
  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_minus<NumericT>, const InterfaceType * rhs)
  {
      if (lhs->is_constant())
      {
        if (lhs->unwrap() == 0.0)
        {
          //std::cout << "optimizable: true in op_minus" << std::endl;
          return true;
        }
      }
      
      if (rhs->is_constant())
      {
        if (rhs->unwrap() == 0.0)
        {
          //std::cout << "optimizable: true in op_minus" << std::endl;
          return true;
        }
      }
      
      return lhs->optimizable() || rhs->optimizable();
  }
  
  
  
  
  //
  // multiplication
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_mult<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var)
  {
      return new binary_expr<InterfaceType>( new binary_expr<InterfaceType>(lhs->diff(diff_var),
                                                                            new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                                            rhs->clone()),
                                             new op_binary<op_plus<NumericT>, InterfaceType>(),
                                             new binary_expr<InterfaceType>(lhs->clone(),
                                                                            new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                                            rhs->diff(diff_var) )
                            );
  }
  
  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_mult<NumericT>, const InterfaceType * rhs)
  {
        if (lhs->is_constant())
        {
          NumericT val = lhs->unwrap();
          if (val == 0.0)
            return new constant<NumericT, InterfaceType>(0.0);
          if (val == 1.0)
            return rhs->optimize();
          
          return new binary_expr<InterfaceType>(new constant<NumericT, InterfaceType>(val),
                                                new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                rhs->optimize());
        }
        else if (rhs->is_constant())
        {
          NumericT val = rhs->unwrap();
          if (val == 0.0)
            return new constant<NumericT, InterfaceType>(0.0);
          if (val == 1.0)
            return lhs->optimize();
          
          return new binary_expr<InterfaceType>(lhs->optimize(),
                                                new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                new constant<NumericT, InterfaceType>(val));
        }
        
        return new binary_expr<InterfaceType>(lhs->optimize(),
                                              new op_binary<op_mult<NumericT>, InterfaceType>(),
                                              rhs->optimize());
  }
  
  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_mult<NumericT>, const InterfaceType * rhs)
  {
      if (lhs->is_constant())
      {
        NumericT val = lhs->unwrap();
        if (val == 0.0)
        {
          //std::cout << "optimizable: true in op_mult" << std::endl;
          return true;
        }
        if (val == 1.0)
        {
          //std::cout << "optimizable: true in op_mult" << std::endl;
          return true;
        }
      }
      if (rhs->is_constant())
      {
        NumericT val = rhs->unwrap();
        if (val == 0.0)
        {
          //std::cout << "optimizable: true in op_mult" << std::endl;
          return true;
        }
        if (val == 1.0)
        {
          //std::cout << "optimizable: true in op_mult" << std::endl;
          return true;
        }
      }
      
      return lhs->optimizable() || rhs->optimizable();
  }
  
  
  
  
  //
  // division
  //
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_div<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var)
  {
    return new binary_expr<InterfaceType>( new binary_expr<InterfaceType>( new binary_expr<InterfaceType>(lhs->diff(diff_var),
                                                                                                          new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                                                                          rhs->clone()),
                                                                           new op_binary<op_minus<NumericT>, InterfaceType>(),
                                                                           new binary_expr<InterfaceType>(lhs->clone(),
                                                                                                          new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                                                                          rhs->diff(diff_var))
                                                                         ),
                                           new op_binary<op_div<NumericT>, InterfaceType>(),
                                           new binary_expr<InterfaceType>(rhs->clone(),
                                                                          new op_binary<op_mult<NumericT>, InterfaceType>(),
                                                                          rhs->clone())
                                         );
  }
  
  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_div<NumericT>, const InterfaceType * rhs)
  {
    if (lhs->is_constant())
    {
      NumericT val = lhs->unwrap();
      if (val == 0.0)
        return new constant<NumericT, InterfaceType>(0.0);
      
      return new binary_expr<InterfaceType>(new constant<NumericT, InterfaceType>(val),
                                            new op_binary<op_div<NumericT>, InterfaceType>(),
                                            rhs->optimize());
    }
    else if (rhs->is_constant())
    {
      NumericT val = rhs->unwrap();
      if (val == 1.0)
        return lhs->optimize();
      
      return new binary_expr<InterfaceType>(lhs->optimize(),
                                            new op_binary<op_div<NumericT>, InterfaceType>(),
                                            new constant<NumericT, InterfaceType>(val));
    }
    
    return new binary_expr<InterfaceType>(lhs->optimize(),
                                          new op_binary<op_div<NumericT>, InterfaceType>(),
                                          rhs->optimize());
  }
  
  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_div<NumericT>, const InterfaceType * rhs)
  {
    if (lhs->is_constant())
    {
      if (lhs->unwrap() == 0.0)
      {
        //std::cout << "optimizable: true in op_div" << std::endl;
        return true;
      }
    }
    if (rhs->is_constant())
    {
      if (rhs->unwrap() == 1.0)
      {
        //std::cout << "optimizable: true in op_div" << std::endl;
        return true;
      }
    }
    return lhs->optimizable() || rhs->optimizable();
  }
  
  
  
}

#endif