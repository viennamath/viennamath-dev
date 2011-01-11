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

namespace viennamath
{
  
  /////// run time expression ///////
  class expression_interface;
  class expr;
  
  /////// interface for op_tags: ///////
  class op_interface
  {
    public:
      virtual ~op_interface() {}
      
      virtual op_interface * clone() const = 0;
      virtual std::string print() const = 0;
  };
  
  struct op_plus;
  struct op_minus;
  struct op_mult;
  struct op_div;
  
  /////// unknown ///////
  template <typename ScalarType, 
            unsigned long id = 0>
  struct unknown;

  
  /////// constant ///////
  class run_time_constant {};
  template <long i>
  class compile_time_constant
  {
    enum { value = i }; 
  };
  
  template <typename ScalarType,
            typename compile_time_qualifier = run_time_constant>
  class constant;
  
  
}

#endif