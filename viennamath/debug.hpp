/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at
               Josef Weinbub                      weinbub@iue.tuwien.ac.at
   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_DEBUG_HPP
#define VIENNAMATH_DEBUG_HPP

#ifdef __GNUC__
#include "cxxabi.h"
#endif

namespace viennamath
{
#ifdef __GNUC__
template<typename T>
std::string
type_to_string()     
{
   int          stat = 0;
   
   std::size_t  len = 0;
   char *demangled = abi::__cxa_demangle(typeid(T).name(), NULL, &len, &stat);
         
   std::string type_string("");
            
   if(stat ==  0) // all went fine ..
   { 
      type_string = std::string(demangled);
      if(demangled)                   
         free(demangled);           
      return type_string; 
   }
   if(stat == -1) 
      std::cout << "type_to_string: memory allocation failure!" << std::endl;
   
   if(stat == -2)
      std::cout << "type_to_string: the requested name is not valid under the C++ ABI mangling rules!" << std::endl;
   
   if(stat == -3)
      std::cout << "type_to_string: one of the arguments is invalid!" << std::endl;
   return type_string;
}
#else
template<typename T>
std::string
type_to_string()     
{
   return "NA";
}
#endif

}

#endif

