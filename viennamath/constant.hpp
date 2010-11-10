/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */


#ifndef VIENNAMATH_UNKNOWN_CPP
#define VIENNAMATH_UNKNOWN_CPP

namespace viennamath
{
  
  //per default, we assume floating point constants, which cannot be tackled with template arguments
  template <typename ScalarType, long value_ = 0>
  class constant
  {
    
    public:
      ScalarExpression(ScalarType s_) : s(s_) {};

      ScalarType operator() () const
      {
        return s;
      }

      template <typename VectorType>
      ScalarType operator() (const VectorType & p) const
      {
        return s;
      }

    private:
      ScalarType s;
  };

  //specialization: for long, we use compile-time magic :-)
  template <long value_ = 0>
  class constant<long, value_>
  {    
    public:
      long operator() () const
      {
        return value_;
      }

      template <typename VectorType>
      long operator() (const VectorType & p) const
      {
        return value_;
      }
  };

}

#endif