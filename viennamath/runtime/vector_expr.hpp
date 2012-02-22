#ifndef VIENNAMATH_RUNTIME_VECTOR_EXPR_HPP
#define VIENNAMATH_RUNTIME_VECTOR_EXPR_HPP

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




#include <ostream>
#include <sstream>
#include <memory>
#include <assert.h>
#include "viennamath/forwards.h"
#include "viennamath/runtime/expr.hpp"

namespace viennamath
{

  /** @brief An tweaked auto_ptr for run time rt_expressions. 
   * 
   * Additionally provides the basic user-interface for evaluation using operator().
   */ 
  template <typename InterfaceType /* see forwards.h for default argument */>
  class rt_vector_expr : public InterfaceType, public std::vector< viennamath::rt_expr<InterfaceType> >
  {
      typedef std::vector< viennamath::rt_expr<InterfaceType> >    BaseType;
      typedef rt_vector_expr<InterfaceType>              self_type;
    
    public:
      typedef typename InterfaceType::numeric_type       numeric_type;
      typedef InterfaceType                              interface_type;
      typedef typename BaseType::size_type               size_type;
      
      explicit rt_vector_expr(size_type num) : BaseType(num)
      {
        //initialize all zeros:
        for (std::size_t i=0; i<num; ++i)
          BaseType::operator[](i) = viennamath::rt_constant<numeric_type, interface_type>(0);
      }
      
      self_type operator+(self_type const & other) const
      {
        assert(BaseType::size() == other.size() && "Expression vector dimensions mismatch");
        
        self_type result(other.size());
        for (std::size_t i=0; i<other.size(); ++i)
          result[i] = (*this)[i] + other[i];
        
        return result;
      }

      self_type operator-(self_type const & other) const
      {
        assert(BaseType::size() == other.size() && "Expression vector dimensions mismatch");
        
        self_type result(other.size());
        for (std::size_t i=0; i<other.size(); ++i)
          result[i] = (*this)[i] - other[i];
        
        return result;
      }
      
      //
      // Interface requirements:
      //
      InterfaceType * clone() const 
      {
        self_type * result = new self_type(BaseType::size());
        
        for (std::size_t i=0; i<result->size(); ++i)
          //(*result)[i] = viennamath::rt_expr<InterfaceType>((*this)[i].get()->clone());
          (*result)[i] = (*this)[i];
        
        return result; 
      }

      std::string deep_str() const
      {
        std::stringstream ss;
        ss << *this;
        return ss.str();
      }
      
      std::string shallow_str() const
      {
        return std::string("vector_expr");
      }
      
      //virtual functions for evaluations
      numeric_type eval(std::vector<double> const & v) const
      {
        throw "Cannot evaluate vector expression!";
        return 0;
      }

      numeric_type eval(numeric_type val) const
      {
        throw "Cannot evaluate vector expression!";
        return 0;
      }

      numeric_type unwrap() const
      {
        throw "cannot unwrap vector expression!";
        return 0;
      }

      bool deep_equal(const InterfaceType * other) const
      {
        if (dynamic_cast< const self_type * >(other) != NULL)
        {
          const self_type * temp = dynamic_cast< const self_type * >(other);
          bool is_equal = true;
          
          for (std::size_t i=0; i<temp->size(); ++i)
            is_equal = is_equal && (*this)[i].get()->deep_equal( (*temp)[i].get() );
            
          
          return is_equal;
        }
        return false;
      }

      bool shallow_equal(const InterfaceType * other) const
      {
        return dynamic_cast< const self_type * >(other) != NULL;
      }
      
      
      InterfaceType * substitute(const InterfaceType * e,
                                 const InterfaceType * repl) const
      {
        if (deep_equal(e))
          return repl->clone();
        
        self_type * result = new self_type(BaseType::size());
        
        for (std::size_t i=0; i<result->size(); ++i)
          (*result)[i] = viennamath::rt_expr<InterfaceType>((*this)[i].get()->substitute(e, repl));
        
        return result; 
      };

      InterfaceType * substitute(std::vector<const InterfaceType *> const &  e,
                                 std::vector<const InterfaceType *> const &  repl) const
      {
        for (size_t i=0; i<e.size(); ++i)
          if (deep_equal(e[i]))
            return repl[i]->clone();
        
        self_type * result = new self_type(BaseType::size());
        
        for (std::size_t i=0; i<result->size(); ++i)
          (*result)[i] = viennamath::rt_expr<InterfaceType>((*this)[i].get()->substitute(e, repl));
        
        return result; 
      };
      
      InterfaceType * optimize() const
      {
        self_type * result = new self_type(BaseType::size());
        
        for (std::size_t i=0; i<result->size(); ++i)
          (*result)[i] = viennamath::rt_expr<InterfaceType>((*this)[i].get()->optimize());
        
        return result;
      }
      
      bool optimizable() const
      {
        for (std::size_t i=0; i<BaseType::size(); ++i)
          if ( (*this)[i].get()->optimizable() == true )
            return true;
          
        return false;
      }
      
      
      InterfaceType * diff(const InterfaceType * diff_var) const
      {
        self_type * result = new self_type(BaseType::size());
        
        for (std::size_t i=0; i<result->size(); ++i)
          (*result)[i] = viennamath::rt_expr<InterfaceType>((*this)[i].get()->diff(diff_var));
        
        return result;
      }
      

  };
  
  //
  // Operator overloads
  //
  
  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, rt_vector_expr<InterfaceType> const & e)
  {
    stream << "[" << e.size() << "](";
    for (std::size_t i=0; i<e.size(); ++i)
    {
      stream << e[i];
      if (i+1 < e.size())
        stream << ", ";
    }
    stream << ")";
    
    return stream;
  }
  
  //operator*
  template <typename InterfaceType, typename T>
  rt_vector_expr<InterfaceType> operator*(rt_vector_expr<InterfaceType> const & lhs, T const & rhs)
  {
    rt_vector_expr<InterfaceType> result(lhs.size());
    for (std::size_t i=0; i<lhs.size(); ++i)
      result[i] = lhs[i] * rhs;
    
    return result;
  }
  
  template <typename T, typename InterfaceType>
  rt_vector_expr<InterfaceType> operator*(T const & lhs, rt_vector_expr<InterfaceType> const & rhs)
  {
    rt_vector_expr<InterfaceType> result(rhs.size());
    for (std::size_t i=0; i<rhs.size(); ++i)
      result[i] = lhs * rhs[i];
    
    return result;
  }

  //special case: dot product:
  template <typename InterfaceType>
  rt_expr<InterfaceType> operator*(rt_vector_expr<InterfaceType> const & lhs, rt_vector_expr<InterfaceType> const & rhs)
  {
    assert(lhs.size() == rhs.size() && lhs.size() > 0 && "Invalid or nonmatching size in expression vectors");
    
    rt_expr<InterfaceType> result = lhs[0] * rhs[0];
    for (std::size_t i=1; i<rhs.size(); ++i)
      result = result + lhs[i] * rhs[i];
    
    return result;
  }
  
  //
  // operator/
  template <typename InterfaceType, typename T>
  rt_vector_expr<InterfaceType> operator/(rt_vector_expr<InterfaceType> const & lhs, T const & rhs)
  {
    rt_vector_expr<InterfaceType> result(lhs.size());
    for (std::size_t i=0; i<lhs.size(); ++i)
      result[i] = lhs[i] / rhs;
    
    return result;
  }
  
  template <typename T, typename InterfaceType>
  rt_vector_expr<InterfaceType> operator/(T const & lhs, rt_vector_expr<InterfaceType> const & rhs)
  {
    rt_vector_expr<InterfaceType> result(rhs.size());
    for (std::size_t i=0; i<rhs.size(); ++i)
      result[i] = lhs / rhs[i];
    
    return result;
  }
  
  
  //
  // Other functionality (inner_prod, etc.)
  //
  
}

#endif