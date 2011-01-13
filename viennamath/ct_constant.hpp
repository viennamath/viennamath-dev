/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_CONSTANT_HPP
#define VIENNAMATH_CT_CONSTANT_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/expression_run_time.hpp"
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  
  //A compile time constant using C++ template magic :-)
  template <long value_>
  class ct_constant : public expression_interface
  {    
      typedef ct_constant<value_>     self_type;
    public:
      explicit ct_constant() {};
      
      self_type operator() () const { return *this; }

      template <typename VectorType>
      self_type operator() (const VectorType & p) const { return *this; }
      
      operator long() const { return value_; }
      
      //interface requirements:
      expression_interface * clone() const { return new ct_constant<value_>(); }
      expr eval(std::vector<double> const & v) const { return (*this)(v); }
      std::string str() const
      {
        std::stringstream ss;
        ss << "ct_constant<" << value_ << ">";
        return ss.str();      
      }
      numeric_type unwrap() const { return value_; }
      
      
    ////////////////// Operations //////////////////////////////
    
    //operator+
    template <typename LHS, typename OP, typename RHS>
    expression<ct_constant<value_>,
               op_plus,
               expression<LHS, OP, RHS> >
    operator+(expression<LHS, OP, RHS> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_plus,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<ct_constant<value_>,
               op_plus,
               unknown<OtherScalarType, other_id> >
    operator+(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_plus,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    constant<OtherScalarType>
    operator+(constant<OtherScalarType> const & other) const
    {
      return constant<OtherScalarType>(value_ + other());
    }

    template <long other_value>
    ct_constant<value_ + other_value>
    operator+(ct_constant<other_value> const & other) const
    {
      return ct_constant<value_ + other_value>();
    }


    //operator-
    template <typename LHS, typename OP, typename RHS>
    expression<ct_constant<value_>,
               op_minus,
               expression<LHS, OP, RHS> >
    operator-(expression<LHS, OP, RHS> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_minus,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<ct_constant<value_>,
               op_minus,
               unknown<OtherScalarType, other_id> >
    operator-(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_minus,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    constant<OtherScalarType>
    operator-(constant<OtherScalarType> const & other) const
    {
      return constant<OtherScalarType>(value_ - other());
    }
    
    template <long other_value>
    ct_constant<value_ - other_value>
    operator-(ct_constant<other_value> const & other) const
    {
      return ct_constant<value_ - other_value>();
    }


    //operator*
    template <typename LHS, typename OP, typename RHS>
    expression<ct_constant<value_>,
               op_mult,
               expression<LHS, OP, RHS> >
    operator*(expression<LHS, OP, RHS> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_mult,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<ct_constant<value_>,
               op_mult,
               unknown<OtherScalarType, other_id> >
    operator*(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_mult,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    constant<OtherScalarType>
    operator*(constant<OtherScalarType> const & other) const
    {
      return constant<OtherScalarType>(value_ * other());
    }

    template <long other_value>
    ct_constant<value_ * other_value>
    operator*(ct_constant<other_value> const & other) const
    {
      return ct_constant<value_ * other_value>();
    }


    //operator/
    template <typename LHS, typename OP, typename RHS>
    expression<ct_constant<value_>,
               op_div,
               expression<LHS, OP, RHS> >
    operator/(expression<LHS, OP, RHS> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_div,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<ct_constant<value_>,
               op_div,
               unknown<OtherScalarType, other_id> >
    operator/(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_div,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    constant<numeric_type>           
    operator/(constant<OtherScalarType> const & other) const
    {
      //TODO: Use traits class for return type deduction (specify handling of integer divisions)
      typedef numeric_type   result_type;
      
      return constant<result_type>(value_ / static_cast<result_type>(other()));
    }
    
    template <long other_value>
    expression<ct_constant<value_>,
               op_div,
               ct_constant<other_value> >
    operator/(ct_constant<other_value> const & other) const
    {
      return expression<ct_constant<value_>,
                        op_div,
                        ct_constant<other_value> >(*this, other);
    }
    
      
      
  };

  template <long value_>
  std::ostream& operator<<(std::ostream & stream,
                           ct_constant<value_> const & c)
  {
    stream << c.str();
    return stream;
  }
  
  
  
  
  
}

#endif