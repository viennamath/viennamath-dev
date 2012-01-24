/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_SUBSTITUTE_HPP
#define VIENNAMATH_SUBSTITUTE_HPP

#include "viennamath/forwards.h"
#include <assert.h>

namespace viennamath
{
  
  
  //TODO: compile time substitution
  
  
  
  
  
  //public interface:
  /** @brief Replaces all occurances of the variable u in the expression 'e' with 'u'. */
  template <typename InterfaceType, typename ReplacementType, typename ExpressionType>
  rt_expr<InterfaceType> substitute(rt_variable<InterfaceType> const & u,
                                    ReplacementType const & repl,
                                    ExpressionType const & e)
  {
    rt_expr<InterfaceType> temp(e.substitute(&u, &repl));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }

  /** @brief Replaces all occurances of the variable u in the expression 'e' with 'u'. */
  template <typename InterfaceType, typename ReplacementType>
  rt_expr<InterfaceType> substitute(rt_variable<InterfaceType> const & u,
                                    ReplacementType const & repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_expr<InterfaceType> temp(e.get()->substitute(&u, &repl));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }

  /** @brief Replaces all occurances of the variable u in the expression 'e' with 'u'. */
  template <typename InterfaceType>
  rt_expr<InterfaceType> substitute(rt_variable<InterfaceType> const & u,
                                    default_numeric_type repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_constant<default_numeric_type, InterfaceType> c(repl);
    rt_expr<InterfaceType> temp(e.get()->substitute(&u, &c));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }

  /** @brief Replaces all occurances of the variable u in the expression 'e' with 'repl'. */
  template <typename InterfaceType>
  rt_expr<InterfaceType> substitute(rt_function_symbol<InterfaceType> const & u,
                                    default_numeric_type repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_constant<default_numeric_type, InterfaceType> c(repl);
    rt_expr<InterfaceType> temp(e.get()->substitute(&u, &c));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> substitute(rt_function_symbol<InterfaceType> const & u,
                                    rt_expr<InterfaceType> const & repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_expr<InterfaceType> temp(e.get()->substitute(&u, repl.get()));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }


  //substitute binary_expressions (for fem):
  template <typename InterfaceType, typename ReplacementType>
  rt_expr<InterfaceType> substitute(rt_unary_expr<InterfaceType> const & search,
                                    ReplacementType const & repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_expr<InterfaceType> temp(e.get()->substitute(&search, &repl));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> substitute(rt_unary_expr<InterfaceType> const & search,
                                    rt_expr<InterfaceType> const & repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_expr<InterfaceType> temp(e.get()->substitute(&search, repl.get()));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }

  template <typename InterfaceType, typename ReplacementType>
  rt_expr<InterfaceType> substitute(rt_binary_expr<InterfaceType> const & search,
                                    ReplacementType const & repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_expr<InterfaceType> temp(e.get()->substitute(&search, &repl));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> substitute(rt_expr<InterfaceType> const & search,
                                    rt_expr<InterfaceType> const & repl,
                                    rt_expr<InterfaceType> const & e)
  {
    rt_expr<InterfaceType> temp(e.get()->substitute(search.get(), repl.get()));
    while (temp.get()->optimizable())
      temp = temp.get()->optimize();
    
    return temp;
  }


  template <typename InterfaceType>
  rt_expr<InterfaceType> substitute(std::vector<rt_expr<InterfaceType> > const & search,
                                    std::vector<rt_expr<InterfaceType> > const & repl,
                                    rt_expr<InterfaceType> const & e)
  {
    assert(search.size() == repl.size() && "Search and replace array must have the same length!");
    
    std::vector<const InterfaceType *> search_ptrs(search.size());
    for (size_t i=0; i<search_ptrs.size(); ++i)
      search_ptrs[i] = search[i].get();
    
    std::vector<const InterfaceType *> repl_ptrs(repl.size());
    for (size_t i=0; i<repl_ptrs.size(); ++i)
      repl_ptrs[i] = repl[i].get();
    
    rt_expr<InterfaceType> temp(e.get()->substitute(search_ptrs, repl_ptrs));
    
    while (temp.get()->optimizable())
    {
      //std::cout << "Optimizing " << temp << std::endl;
      temp = temp.get()->optimize();
    }
    //std::cout << "Optimization end" << std::endl;
    
    return temp;
  }

}

#endif