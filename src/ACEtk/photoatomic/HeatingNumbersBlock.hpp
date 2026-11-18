#ifndef NJOY_ACETK_PHOTOATOMIC_HEATINGNUMBERSBLOCK
#define NJOY_ACETK_PHOTOATOMIC_HEATINGNUMBERSBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic LHNM block with the heating numbers
 *
 *  The HeatingNumbersBlock class contains the heating numbers. The size of the
 *  array is stored in NXS(3) and the corresponding energy points can be found
 *  in the ESZG block.
 */
class HeatingNumbersBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  HeatingNumbersBlock() = default;

  HeatingNumbersBlock( const HeatingNumbersBlock& ) = default;
  HeatingNumbersBlock( HeatingNumbersBlock&& ) = default;

  HeatingNumbersBlock& operator=( const HeatingNumbersBlock& ) = default;
  HeatingNumbersBlock& operator=( HeatingNumbersBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] heating    the heating numbers
   */
  HeatingNumbersBlock( std::vector< double > heating ) :
    ArrayData( "LHNM",
               std::vector< std::vector< double > >{ std::move( heating ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
   *  @param[in] end     the end iterator of the ESZG block in the XSS array
   *  @param[in] nes     the number of energy points
   */
  HeatingNumbersBlock( Iterator begin, Iterator end, unsigned int nes ) :
    ArrayData( "LHNM", begin, end, nes, 1 ) {}

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the heating numbers
   */
  auto heating() const { return this->darray( 1 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using LHNM = HeatingNumbersBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
