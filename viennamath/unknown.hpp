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
  
  template <typename ScalarType, typename VectorType, long id>
  struct unknown_traits
  {
    //per default, access id-th element;
    static ScalarType get(VectorType const & v)
    {
      return v[id];
    }
  };
  
  //specialize unknown_traits::get() here as required.
  
  
  
  /** @brief Representation of an unknown (a variable). If the supplied argument is some vector type,
   *  a traits system accesses the id-th component
   * 
   * @tparam ScalarType        the underlying numerical type (typically float, double)
   * @tparam id                the component of the vector for which 'unknown' is evaluated
   */
  template <typename ScalarType, unsigned long id = 0>
  struct unknown
  {
    unknown() {};

    void print() const
    {
      std::cout << "unknown<" << id << ">";
    }

    //Basic evaluation:
    ScalarType operator()(ScalarType value) const
    {
      return value;
    }

    //Vector argument:
    template <typename VectorType>
    ScalarType operator()(VectorType const & v) const
    {
      return unknown_traits<ScalarType, VectorType, id>::get(v);
    }
  };



}

#endif