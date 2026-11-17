#ifndef NJOY_ACETK_MULTIGROUP_RECTANGULARP0DATA
#define NJOY_ACETK_MULTIGROUP_RECTANGULARP0DATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/RectangularMatrixData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief P0 Block for outgoing particles that are not the incident particle
 *
 *  The RectangularP0Data class contains the P0 block for the outgoing
 *  particle when it is not the incident particle. 
 *
 */
class RectangularP0Data : protected base::RectangularMatrixData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  RectangularP0Data() = default;

  RectangularP0Data( const RectangularP0Data& ) = default;
  RectangularP0Data( RectangularP0Data&& ) = default;

  RectangularP0Data& operator=( const RectangularP0Data& ) = default;
  RectangularP0Data& operator=( RectangularP0Data&& ) = default;


  /**
   *  @brief Constructor
  *
  *  Note: Any non-zero values in the matrix outside of the defined
  *  bands will be lost in the construction of the RectangularP0Data 
  *  object. 
   *
  *  @param[in] matrix     the two-dimensional matrix data values
  */
  RectangularP0Data( std::vector< std::vector< double > >&& matrix ) :
    RectangularMatrixData( "RectangularP0Data", std::move( matrix ) ) {}

  /**
  *  @brief Constructor
  *
  *  @param[in] begin      the begin iterator of the P0 data in the XSS array
  *  @param[in] end        the end iterator of the P0 data in the XSS array
  *  @param[in] nrows      the number of rows and row labels
  *  @param[in] ncols      the number of columns and column labels
  */
  RectangularP0Data( Iterator begin,
              Iterator end,
              unsigned int nrows,
              unsigned int ncols ) :
  RectangularMatrixData( "RectangularP0Data", begin, end, nrows, ncols ) {}

  /**
   *  @brief Return the number of incident energy groups
   */
  unsigned int NGRP() const {

    return static_cast< unsigned int >( this->M() );
  }

  /**
   *  @brief Return the number of incident energy groups
   */
  unsigned int numberIncidentEnergyGroups() const {

    return static_cast< unsigned int >( this->NGRP() );
  }

  /**
   *  @brief Return the number of outgoing energy groups
   */
  unsigned int NERG() const {

    return static_cast< unsigned int >( this->N() );
  }

  /**
   *  @brief Return the number of outgoing energy groups
   */
  unsigned int numberOutgoingEnergyGroups() const {

    return static_cast< unsigned int >( this->NERG() );
  }

  /**
   *  @brief Return the length of the XSS block
   */
  unsigned int blockLength() const { 
    
    return this->NGRP() * this->NERG(); 
  }

  /**
   *  @brief Return the P0 matrix as a 1-D array
   */
  auto P0MatrixList() const {
    
    return this->dmatrix( );
  }


  /**
   *  @brief Return the value by the incident and outgoing group
   *         indices.
   *
   *
   *  @param[in] incidentGroup   the incident group index (one-based)
   *  @param[in] outgoingGroup   the outgoing group index (one-based)
   */
  double P0Value( unsigned int incidentGroup, unsigned int outgoingGroup ) const {
    
    return this->dvalue( incidentGroup, outgoingGroup ) ; 
  }

  /**
   *  @brief Return the row of the matrix for a specific
   *         incident group
   *
   *
   *  @param[in] incidentGroup   the incident group index (one-based)
   */
   auto incidentRow( unsigned int incidentGroup ) const {

      return this->drow( incidentGroup );
    }

  /**
   *  @brief Return the column of the matrix for a specific
   *         outgoing group
   *
   *
   *  @param[in] outgoingGroup   the outgoing group index (one-based)
   */
   auto outgoingColumn( unsigned int outgoingGroup ) const {

      return this->dcolumn( outgoingGroup );
    }
  
  /**
   *  @brief Return the P0 matrix
   *
   */
   auto P0Matrix( ) const {

      return this->matrix();    
    }


  using RectangularMatrixData::empty;
  using RectangularMatrixData::name;
  using RectangularMatrixData::length;
  using RectangularMatrixData::XSS;
  using RectangularMatrixData::begin;
  using RectangularMatrixData::end;
};

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
