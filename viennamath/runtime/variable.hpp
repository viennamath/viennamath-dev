/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_RUNTIME_VARIABLE_HPP
#define VIENNAMATH_RUNTIME_VARIABLE_HPP

#include "viennamath/compiletime/ct_vector.hpp"

#include "viennamath/runtime/constant.hpp"
#include "viennamath/runtime/expression_interface.hpp"

#include <assert.h>

namespace viennamath
{

  /*********** evaluation of a run time constant: *****************/
  template <typename ScalarType>
  struct variable_traits <constant<ScalarType>,
                          0>
  {
    typedef viennamath::constant<ScalarType>   return_type;
    
    //per default, access id-th element;
    static return_type get(viennamath::constant<ScalarType> const & v)
    {
      return v;
    }
  };

  //guard: something like (x*y - z)(constant<double>(4)) is not allowed
  template <typename ScalarType, long id>
  struct variable_traits <constant<ScalarType>,
                          id>
  {
    //try to provide a good compiler error message:
    typedef typename viennamath::constant<ScalarType>::ERROR_PROVIDED_NOT_ENOUGH_ARGUMENTS_TO_EXPRESSION   error_type;
    
    //providing a non-vector type is bogus -> force linker error!
  };
  
  template <typename VectorType>
  typename VectorType::value_type get_from_vector(VectorType const & vec, unsigned long i)
  {
    return vec[i];
  }
  
  template <typename T1>
  default_numeric_type get_from_vector(ct_vector_1<T1> const & vec, unsigned long i)
  {
    return vec[ct_index<0>()]; 
  }
  
  template <typename T1, typename T2>
  default_numeric_type get_from_vector(ct_vector_2<T1, T2> const & vec, unsigned long i)
  {
    if (i == 0)
      return vec[ct_index<0>()];
    else if (i == 1)
      return vec[ct_index<1>()];
    return 0;
  }

  template <typename T1, typename T2, typename T3>
  default_numeric_type get_from_vector(ct_vector_3<T1, T2, T3> const & vec, unsigned long i)
  {
    if (i == 0)
      return vec[ct_index<0>()];
    else if (i == 1)
      return vec[ct_index<1>()];
    else if (i == 2)
      return vec[ct_index<2>()];
    return 0;
  }

  
  /** @brief Representation of an variable (a variable). If the supplied argument is some vector type,
   *  a traits system accesses the id-th component
   * 
   * @tparam ScalarType        the underlying numerical type (typically float, double)
   */
  template <typename InterfaceType /* see forwards.h for default argument */>
  class variable : public InterfaceType
  {
    public:
      typedef typename InterfaceType::numeric_type    numeric_type;
      
      explicit variable(unsigned long my_id) : id_(my_id) {};

      unsigned long id() const { return id_; }
      
      /////////////////   Basic evaluation: //////////////////////////////////
      numeric_type operator()(numeric_type value) const
      {
        return value;
      }

      template <typename ScalarType>
      constant<ScalarType> operator()(constant<ScalarType> const & other) const
      {
        if (id_ > 0)
          throw variable_index_out_of_bounds(id_, 0);
        return constant<ScalarType>(static_cast<ScalarType>(other));
      }

      template <long value>
      long operator()(ct_constant<value> const & other) const
      {
        if (id_ > 0)
          throw variable_index_out_of_bounds(id_, 0);
        return value;
      }

      //Vector argument (can be of type std::vector)
      template <typename VectorType>
      //typename variable_traits<VectorType, id_>::return_type 
      numeric_type 
      operator()(VectorType const & v) const
      {
        if(id_ >= v.size())
          throw variable_index_out_of_bounds(id_, v.size());
        return get_from_vector(v, id_);
      }
      
      //interface requirements:
      InterfaceType * clone() const { return new variable(id_); }
      numeric_type eval(std::vector<double> const & v) const
      {
        if (id_ >= v.size())
          throw variable_index_out_of_bounds(id_, v.size());
        
        return (*this)(v);
      }
      
      numeric_type eval(numeric_type val) const
      {
        if (id_ >= 1)
          throw variable_index_out_of_bounds(id_, 1);
        
        return val;
      }
      
      std::string str() const
      {
        std::stringstream ss;
        ss << "variable(" << id_ << ")";
        return ss.str();      
      }
      numeric_type unwrap() const
      {
        throw expression_not_unwrappable();
        return 0;
      }
        
      //protected:
      InterfaceType * substitute(const InterfaceType * e,
                                const InterfaceType * repl) const
      {
        //std::cout << "Comparing variable<" << id << "> with " << e->str() << ", result: ";
        const variable<InterfaceType> * ptr = dynamic_cast< const variable<InterfaceType> *>(e);
        if (ptr != NULL)
        {
          //std::cout << "TRUE, replacing with " << repl->str() << std::endl;
          if (ptr->id() == id_)
            return repl->clone();
        }
        //std::cout << "FALSE" << std::endl;
        return clone();
      };    
      
      bool equal(const InterfaceType * other) const
      {
        const variable<InterfaceType> * ptr = dynamic_cast< const variable<InterfaceType> *>(other);
        if (ptr != NULL)
        {
          return ptr->id() == id_;
        }
        return false;
      }
      
      InterfaceType * diff(const InterfaceType * diff_var) const
      {
        const variable<InterfaceType> * ptr = dynamic_cast< const variable<InterfaceType> *>(diff_var);
        if (ptr != NULL)
        {
          //std::cout << "diff variable<" << id << ">: TRUE" << std::endl;
          if (ptr->id() == id_)
            return new constant<numeric_type, InterfaceType>(1);
        }
        //std::cout << "diff variable<" << id << ">: FALSE, is: " << diff_var.get()->str() << std::endl;
        return new constant<numeric_type, InterfaceType>(0);
      }
    
    private: 
      unsigned long id_;
  }; //variable

  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, variable<InterfaceType> const & u)
  {
    stream << "variable(" << u.id() << ")";
    return stream;
  }


}

#endif