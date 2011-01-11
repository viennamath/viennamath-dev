/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */

#ifndef ELFEM_TRAITS_GUARD
#define ELFEM_TRAITS_GUARD

#include <iostream>
#include "typelist.h"
#include "expression_header.h"
#include "mappingkeytype.h"
#include "boundarykeytype.h"
#include "idhandler.h"

namespace elfem{

  using namespace elfem::expressions;

  //forward declaration of DomainTypes:
  template <typename Configuration>
  struct DomainTypes;

  template <typename Domain>
  struct DomainTraits;

  //integration policies:
  struct AnalyticIntegrationTag {};

  struct LinearIntegrationTag {};
  struct QuadraticIntegrationTag {};
  struct CubicIntegrationTag {};

  struct QuinticIntegrationTag {};

  struct OrderSevenIntegrationTag {};


  struct CellIntegrationTag {};

  //Dimension Tags:
  struct ThreeDimensionsTag{
      enum{ dim = 3 };
  };
  
  struct TwoDimensionsTag{
      enum{ dim = 2 };
  };

  struct OneDimensionTag{
      enum{ dim = 1 };
  };

  //Basisfunction-Treatment:
  struct TypeListTag {};      //use typelists
  struct TypeErasureTag {};   //use type erasure

  //Topological Handling Tag
  struct TopoLevelFullHandling {};
  struct TopoLevelNoHandling {};

  //Tag for handling of functional determinant
  struct DtDxStoreAll{ };   //all elements of functional determinant are stored. Usually fastest, but high memory consumption.
  struct DtDxStoreDetOnly {}; //only determinant is stored, other elements computed on-the-fly. Needs less memory, but usually increases runtime a little bit
  struct DtDxOnAccess {};   //All values are (repeatedly) computed on-the-fly. Use only in situations where every bit of memory is important.
  struct DtDxStoreStatically {}; //computes the functional determinant at the point of first access to a cell in static variables. Must not be used together with multi-threading!

  //multigrid:
  struct FullMultigridTag {};
  struct NoMultigridTag {};

  //segment connection:
  template <long id>
  struct SegmentConnectionKey
  {
    bool operator<(SegmentConnectionKey const & sck2) const
    {
      return false;     // a < b is false AND b < a is false, hence a == b
    }
  };


  struct NoBoundaryRead {};                     //do not read boundary from file

  //Dimension of Result scalar or vector:
  struct ScalarTag {
    enum { dim = 1 };
  };

  template <typename DimensionTag>
  struct VectorTag {
    enum { dim = DimensionTag::dim };
  };


  //Continuity-Tag:
  struct C0_Tag {};   //ordinary H1-basisfunctions
  struct C1_Tag {};   //Hermite

  template <typename CellTag>
  struct BFDistributor;

  //Mapping Tags:
  struct FullMappingTag             //Create the 'full' mapping, including boundary vertices
  {
    template <typename Iterator, typename BoundaryKey>
    static bool apply(Iterator & it, BoundaryKey const & bk) { return false; }
  };

  struct NoBoundaryMappingTag       //exclude boundary vertices from mapping.
  {
    template <typename Iterator, typename BoundaryKey>
    static bool apply(Iterator & it, BoundaryKey const & bk)
    {
      return it->template retrieveQuantity<bool>(bk);
    }
  };


  //Basis function tags
  struct LinearBasisfunctionTag
  {
    enum{ degree = 1 };
    //enum { onVertex = 1, onEdge = 0, onFacet = 0, onCell = 0};
    //enum { num = TopologyLevel<CellTag, 0>::ElementNum * onVertex };
    //typedef C0_Tag                ContinuityTag;
  };

  struct QuadraticBasisfunctionTag
  {
    enum{ degree = 2 };
/*    enum { onVertex = 1, onEdge = 1, onFacet = 0, onCell = 0 };
    enum { num = CellTag::vertices * onVertex +
                  CellTag::edges * onEdge + 
                  CellTag::facets * onFacet + onCell };
    typedef C0_Tag                ContinuityTag;*/
  };

  struct CubicBasisfunctionTag
  {
    enum{ degree = 3 };
  };

//   template <>
//   struct CubicBasisfunctionTag<TriangleTag>
//   {
//     enum { onVertex = 1, onEdge = 2, onFacet = 0, onCell = 1 };
//     enum { num = TriangleTag::vertices * onVertex +
//                   TriangleTag::edges * onEdge + 
//                   TriangleTag::facets * onFacet + onCell };
//     typedef C0_Tag                ContinuityTag;
//   };
// 
//   template <>
//   struct CubicBasisfunctionTag<TetrahedraTag>
//   {
//     enum { onVertex = 1, onEdge = 2, onFacet = 1, onCell = 0 };
//     enum { num = TetrahedraTag::vertices * onVertex +
//                   TetrahedraTag::edges * onEdge + 
//                   TetrahedraTag::facets * onFacet + onCell };
//     typedef C0_Tag                ContinuityTag;
//   };

  struct QuarticBasisfunctionTag
  {
    enum{ degree = 4 };
  };

  struct QuinticBasisfunctionTag
  {
    enum{ degree = 5 };
  };

//   template <>
//   struct QuarticBasisfunctionTag<TriangleTag>
//   {
//     enum { onVertex = 1, onEdge = 3, onFacet = 0, onCell = 3 };
//     enum { num = TriangleTag::vertices * onVertex +
//                   TriangleTag::edges * onEdge + 
//                   TriangleTag::facets * onFacet + onCell };
//     typedef C0_Tag                ContinuityTag;
//   };
// 
//   template <>
//   struct QuarticBasisfunctionTag<TetrahedraTag>
//   {
//     enum { onVertex = 1, onEdge = 3, onFacet = 3, onCell = 1 };   //TODO: Check numbers!
//     enum { num = TetrahedraTag::vertices * onVertex +
//                   TetrahedraTag::edges * onEdge + 
//                   TetrahedraTag::facets * onFacet + onCell };
//     typedef C0_Tag                ContinuityTag;
//   };

/*
  template <typename Domain_Config>
  struct GlobalTraitsSample
  {
    typedef Domain_Config                     DomainConfiguration;

    //typedef VectorTag<typename Domain_Config::DimensionTag>           ResultDimension;
    typedef ScalarTag                         ResultDimension;
    typedef TypeListTag                       BaseFunTreatmentTag;
    typedef NoBoundaryMappingTag              MappingTag;
    typedef LinearBasisfunctionTag<typename Domain_Config::CellTag>    BasisfunctionTag;

    typedef MappingKeyType<0>                 MappingKey;
    typedef BoundaryKeyType<0>                BoundaryKey;

    typedef BoundaryKeyType<11>                BoundaryData;
    typedef BoundaryKeyType<12>                BoundaryData2;
    typedef BoundaryKeyType<13>                BoundaryData3;
  };
*/

  #include "celltags.h"  


} 
#endif
