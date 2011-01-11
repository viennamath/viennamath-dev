/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CONSTANT_HPP
#define VIENNAMATH_CONSTANT_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/expression_run_time.hpp"
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  
  //per default, we assume floating point constants, which cannot be tackled with template arguments
  template <typename ScalarType, typename compile_time_qualifier /* see forwards.h for default argument */>
  class constant : public expression_interface
  {
      typedef constant<ScalarType, compile_time_qualifier>     self_type;
    public:
      explicit constant(ScalarType s_) : s(s_) {};

      self_type operator() () const
      {
        return *this;
      }

      template <typename VectorType>
      self_type operator() (const VectorType & p) const
      {
        return *this;
      }

      std::ostream & operator<<(std::ostream & stream) const
      {
        stream << "constant<" << s << ">";
        return stream;
      }
      
      operator ScalarType() const { return s; }
      
      //interface requirements:
      expression_interface * clone() const { return new constant(s); }
      std::string print() const
      {
        std::stringstream ss;
        ss << "constant<runtime>(" << s << ")";
        return ss.str();      
      }
      bool is_primitive() const { return true; }
      
    private:
      ScalarType s;
  };

  template <typename ScalarType>
  std::ostream& operator<<(std::ostream & stream, constant<ScalarType, run_time_constant > const & c)
  {
    stream << "constant<runtime>(" << static_cast<ScalarType>(c) << ")";
    return stream;
  }

  //specialization: for long, we use compile-time magic :-)
  template <long value_>
  class constant<long, compile_time_constant<value_> > : public expression_interface
  {    
      typedef constant<long, compile_time_constant<value_> >     self_type;
    public:
      explicit constant() {};
      
      self_type operator() () const
      {
        return *this;
      }

      template <typename VectorType>
      self_type operator() (const VectorType & p) const
      {
        return *this;
      }
      
      operator long() const { return value_; }
      
      //interface requirements:
      expression_interface * clone() const { return new constant(); }
      std::string print() const
      {
        std::stringstream ss;
        ss << "constant<" << value_ << ">";
        return ss.str();      
      }
      bool is_primitive() const { return true; }
      
  };

  template <long value_>
  std::ostream& operator<<(std::ostream & stream,
                           constant<long, compile_time_constant<value_> > const & c)
  {
    stream << "constant<" << value_ << ">";
    return stream;
  }
  
  
  
  
  ////////////////////////////// Operators ///////////////////////////////////
    template <typename ScalarType, typename U,
              typename OtherScalarType, typename V>
    expression<constant<ScalarType, U>,
               op_plus,
               constant<OtherScalarType, V> >
    operator+(constant<ScalarType, U> const & lhs,
              constant<OtherScalarType, V> const & rhs)
    {
      return expression<constant<ScalarType, U>,
                        op_plus,
                        constant<OtherScalarType, V> >(lhs, rhs);
    }
  
}

#endif