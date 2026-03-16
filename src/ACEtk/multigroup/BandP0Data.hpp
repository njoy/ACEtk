#ifndef NJOY_ACETK_MULTIGROUP_BANDP0DATA
#define NJOY_ACETK_MULTIGROUP_BANDP0DATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/SquareBandMatrixData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief P0 Block for the incident particle
 *
 *  The BandP0Data class contains the P0 block for the outgoing
 *  particle when it is the same as the incident particle. It is 
 *  stored as a Square Band Matrix. Down-scatter groups are the
 *  super-diagonals in the matrix and up-scatter groups are the
 *  sub-diagonals in the matrix because the energy groups are
 *  sorted in descending order.
 *
 */
class BandP0Data : protected base::SquareBandMatrixData {

  /* fields */
  base::SquareBandMatrixData matrix_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/multigroup/BandP0Data/src/ctor.hpp"

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int NGRP() const {

    return static_cast< unsigned int >( this->size() );
  }

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int numberEnergyGroups() const {

    return static_cast< unsigned int >( this->NGRP() );
  }

  /**
   *  @brief Return the number of down-scatter groups
   */
  unsigned int NDS() const { return this->numberSuperDiagonals(); }

  /**
   *  @brief Return the number of down-scatter groups
   */
  unsigned int numberDownScatterGroups() const { return this->NDS(); }


  /**
   *  @brief Return the number of up-scatter groups
   */
  unsigned int NUS() const { return this->numberSubDiagonals(); }

  /**
   *  @brief Return the number of up-scatter groups
   */
  unsigned int numberUpScatterGroups() const { return this->NUS(); }


  /**
   *  @brief Return the length of the XSS block
   */
  unsigned int blockLength() const { 
    
    return (this->NGRP() * (1 + this->NUS() + this->NDS())) - ((this->NUS() * (1+this->NDS())) + (this->NDS() * (1+this->NDS() ) ) ) / 2; 
  }

  /**
   *  @brief Return the P0 matrix as a 1-D array
   */
  auto P0MatrixList() const {
    
    return this->XSS( );
  }

  /**
   *  @brief Return the number of up-scatter groups for a specific
   *         incident energy group
   *
   *  @param[in] group    the incident group index (one-based)
   */
  unsigned int groupDownScatterGroups( unsigned int group ) const {

    return this->rowEnd( group ) - group;
  }

  /**
   *  @brief Return the number of down-scatter groups for a 
   *         specific incident energy groups
   *
   *  @param[in] group     the incident group index (one-based)
   */
  unsigned int groupUpScatterGroups( unsigned int group ) const {

    return  group - this->rowStart( group ) ;
  }

  /**
   *  @brief Return the value by the incident and outgoing group
   *         indices.
   *
   *  The function will return zero if:
   *    - the element isn't part of the list (the row and column 
   *      correspond to an element outside the given bands)
   *    - if the element is outside the bounds of the matrix
   *
   *  @param[in] incidentGroup   the incident group index (one-based)
   *  @param[in] outgoingGroup   the outgoing group index (one-based)
   */
  double P0Value( unsigned int incidentGroup, unsigned int outgoingGroup ) const {
    
    return this->matrixValue( incidentGroup, outgoingGroup ) ; 
  }

  /**
   *  @brief Return the row of the matrix for a specific
   *         incident group
   *
   *  If the row is out of bounds, an array of all
   *  zeros will be returned
   *
   *  @param[in] incidentGroup   the incident group index (one-based)
   */
   auto incidentRow( unsigned int incidentGroup ) const {

      return this->matrixRow( incidentGroup );
    }
  
  /**
   *  @brief Return the P0 matrix
   *
   */
   auto P0Matrix( ) const {

      return this->matrix();    
    }


  using SquareBandMatrixData::empty;
  using SquareBandMatrixData::name;
  using SquareBandMatrixData::length;
  using SquareBandMatrixData::XSS;
  using SquareBandMatrixData::begin;
  using SquareBandMatrixData::end;
};

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
