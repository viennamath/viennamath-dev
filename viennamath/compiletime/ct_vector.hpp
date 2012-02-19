/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_VECTOR_HPP
#define VIENNAMATH_CT_VECTOR_HPP

#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  //compile time vector with one element
  template <typename T0>
  class ct_vector_1
  {
    public:
      typedef T0   type_0;
      
      ct_vector_1(T0 const & t0) : t0_(t0) {};
    
      T0 const & operator[](ct_index<0>) const { return t0_; }
      
      //compile time index out of bounds:
      template <long i>
      void operator[](ct_index<i>) const
      {
        typedef typename ct_index<i>::ERROR_VECTOR_1_INDEX_OUT_OF_BOUNDS  error_message; 
      }
      
      size_t size() const { return 1; }

    private:
      T0 const & t0_;
  };
  
  template <typename T0>
  std::ostream& operator<<(std::ostream & stream, ct_vector_1<T0> const & v)
  {
    stream << "vector<" << v[ct_index<0>()] << ">";
    return stream;
  }
  
  
  
  //compile time vector with two elements
  template <typename T0, typename T1>
  class ct_vector_2
  {
    public:
      typedef T0   type_0;
      typedef T1   type_1;
      
      ct_vector_2(T0 const & t0, T1 const & t1) : t0_(t0), t1_(t1) {};
    
      T0 const & operator[](ct_index<0>) const { return t0_; }
      T1 const & operator[](ct_index<1>) const { return t1_; }

      //compile time index out of bounds:
      template <long i>
      void operator[](ct_index<i>) const
      {
        typedef typename ct_index<i>::ERROR_VECTOR_2_INDEX_OUT_OF_BOUNDS  error_message; 
      }

      std::size_t size() const { return 2; }

    private:
      T0 const & t0_;
      T1 const & t1_;
  };

  template <typename T0, typename T1>
  std::ostream& operator<<(std::ostream & stream, ct_vector_2<T0, T1> const & v)
  {
    stream << "vector<" << v[ct_index<0>()] << ", " << v[ct_index<1>()] << ">";
    return stream;
  }
  
  
  //compile time vector with three elements
  template <typename T0, typename T1, typename T2>
  class ct_vector_3
  {
    public:
      typedef T0   type_0;
      typedef T1   type_1;
      typedef T2   type_2;
      //typedef typename type_0::numeric_type  numeric_type;
      
      ct_vector_3(T0 const & t0, T1 const & t1, T2 const & t2) : t0_(t0), t1_(t1), t2_(t2) {};
      
      ct_vector_3(const ct_vector_3 & other) : t0_(other.t0_), t1_(other.t1_), t2_(other.t2_) {}
    
      T0 const & operator[](ct_index<0>) const { return t0_; }
      T1 const & operator[](ct_index<1>) const { return t1_; }
      T2 const & operator[](ct_index<2>) const { return t2_; }

      //compile time index out of bounds:
      template <long i>
      void operator[](ct_index<i>) const
      {
        typedef typename ct_index<i>::ERROR_VECTOR_3_INDEX_OUT_OF_BOUNDS  error_message; 
      }

      std::size_t size() const { return 3; }

    private:
      T0 t0_;
      T1 t1_;
      T2 t2_;
  };
  
  template <typename T0, typename T1, typename T2>
  std::ostream& operator<<(std::ostream & stream, ct_vector_3<T0, T1, T2> const & v)
  {
    stream << "vector<" << v[ct_index<0>()] << ", "
                        << v[ct_index<1>()] << ", "                            
                        << v[ct_index<2>()] << ">";
    return stream;
  }
  
  
  /***************** make_vector() - A helper function for creation vector_X types */
  template <typename T0>
  ct_vector_1<T0> make_vector(T0 const & t0)
  {
    return ct_vector_1<T0>(t0);
  }
  
  template <typename T0, typename T1>
  ct_vector_2<T0, T1> make_vector(T0 const & t0, T1 const & t1)
  {
    return ct_vector_2<T0, T1>(t0, t1);
  }
  
  template <typename T0, typename T1, typename T2>
  ct_vector_3<T0, T1, T2> make_vector(T0 const & t0, T1 const & t1, T2 const & t2)
  {
    return ct_vector_3<T0, T1, T2>(t0, t1, t2);
  }
  
} //namespace viennamath

#endif