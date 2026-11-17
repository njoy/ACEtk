#ifndef NJOY_ACETK_ELECTRON_OSCILLATORBLOCK
#define NJOY_ACETK_ELECTRON_OSCILLATORBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron CRB block with the oscillator descriptions
 *
 *  This block is part of the el03 format.
 *
 *  The OscillatorBlock class contains 2 arrays of the
 *  same length:
 *    - The level occupation numbers
 *    - The level binding energies
 *
 *  The size NOSC of each (the total number of oscillator points) is stored
 *  in NXS(11).
 */
class OscillatorBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */

  OscillatorBlock() = default;

  OscillatorBlock( const OscillatorBlock& ) = default;
  OscillatorBlock( OscillatorBlock&& ) = default;

  OscillatorBlock& operator=( const OscillatorBlock& ) = default;
  OscillatorBlock& operator=( OscillatorBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] occupationnumbers    The occupation numbers of each subshell
   *  @param[in] bindingenergies      The binding energies of each subshell
   */
  OscillatorBlock( std::vector< double > occupationnumbers,
                   std::vector< double > bindingenergies ) :
    ArrayData( "OSC",
               std::move( occupationnumbers ), std::move( bindingenergies ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the OSC block in the XSS array
   *  @param[in] end     the end iterator of the OSC block in the XSS array
   *  @param[in] nosc    the number of oscillators
   */
  OscillatorBlock( Iterator begin, Iterator end, unsigned int nosc ) :
    ArrayData( "OSC", begin, end, nosc, 2 ) {}
  
  /* methods */
  
  /**
   *  @brief Return the number of oscillators
   */
  unsigned int NOSC() const { return this->N(); }
  
  /**
   *  @brief Return the number of oscillators
   */
  unsigned int numberOscillators() const { return this->NOSC(); }
  
  /**
   *  @brief Return the occupation numbers of each level
   *
   *  n < 0 at the last (highest) level signifies a conductor
   */
  auto occupationNumbers() const { return this->darray( 1 ); }
  
  /**
   *  @brief Return the binding energies of each level
   */
  auto bindingEnergies() const { return this->darray( 2 ); }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using OSC = OscillatorBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
