#ifndef VIENNAMATH_EXCEPTION_HPP
#define VIENNAMATH_EXCEPTION_HPP

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


#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <memory>

/** @file exception.hpp
    @brief Defines all the exceptions thrown within ViennaMath.
*/

namespace viennamath
{
  
  /** @brief An exception which is thrown if an expression should be evaluated to a floating point number using eval(), but at least one of the leaves in the expression tree cannot be evaluated (e.g. is a function symbol).
   * 
   */
  class expression_not_unwrappable : public std::exception
  {
    const char * what() const throw() { return "Expression cannot be unwrapped!"; } 
  };
  
  
  
  /** @brief An exception which is thrown if a variable index is out of bounds. Similar to the C++ STL, index checks are performed on vectors using the .at() member function only.
   * 
   */
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
