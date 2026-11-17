#ifndef NJOY_ACETK_MULTIGROUP_NUMBERSECONDARYANGULARVARIABLESBLOCK
#define NJOY_ACETK_MULTIGROUP_NUMBERSECONDARYANGULARVARIABLESBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup NLEG2 block with the number of angular distribution variables
 *
 *  The number of particle types (NSEC) is stored in NXS(8).
 */
class NumberSecondaryAngularVariablesBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  NumberSecondaryAngularVariablesBlock() = default;

  NumberSecondaryAngularVariablesBlock( const NumberSecondaryAngularVariablesBlock& ) = default;
  NumberSecondaryAngularVariablesBlock( NumberSecondaryAngularVariablesBlock&& ) = default;

  NumberSecondaryAngularVariablesBlock& operator=( const NumberSecondaryAngularVariablesBlock& ) = default;
  NumberSecondaryAngularVariablesBlock& operator=( NumberSecondaryAngularVariablesBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] numbers    the number of variables for each particle
   */
  NumberSecondaryAngularVariablesBlock( std::vector< unsigned int > numbers ) :
    ArrayData( "NLEG2",
               std::vector< std::vector< unsigned int > >{ std::move( numbers ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the NLEG2 block in the XSS array
   *  @param[in] end     the end iterator of the NLEG2 block in the XSS array
   *  @param[in] nsec    the number of secondary particles
   */
  NumberSecondaryAngularVariablesBlock( Iterator begin, Iterator end, unsigned int nsec ) :
    ArrayData( "NLEG2", begin, end, nsec, 1 ) {}

  /* methods */

  /**
   *  @brief Return the number of secondary particles
   */
  unsigned int NSEC() const { return this->N(); }

  /**
   *  @brief Return the number of secondary particles 
   */
  unsigned int numberSecondaryParticles() const {

    return this->NSEC();
  }

  /**
   *  @brief Return the number of angular distribution variables for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int NLEG2( std::size_t index ) const { return this->ivalue( 1, index ); }

  /**
   *  @brief Return the number of angular distribution variables for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int numberAngularDistributionVariables( std::size_t index ) const {

    return this->NLEG2( index );
  }

  /**
   *  @brief Return the list of number of angular distribution variables
   */
  auto NLEG2s() const { return this->iarray( 1 ); }

  /**
   *  @brief Return the list of number of angular distribution variables
   */
  auto numberAngularDistributionVariablesList() const { return this->NLEG2s(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using NLEG2 = NumberSecondaryAngularVariablesBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
