#ifndef NJOY_ACETK_ELECTRON_RILEYCROSSSECTIONBLOCK
#define NJOY_ACETK_ELECTRON_RILEYCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron RLY block with the Riley cross section data
 *
 *  This block is part of el and el03 formats.
 *
 *  The RileyCrossSectionBlock class contains 9 arrays of the same length.
 *  Each array contains an energy value from 1 to 256 keV followed by the
 *  set of Riley scattering cross section parameters at that energy.
 *
 *  The size of each Riley set array is 14 (1 energy + 13 parameters).
 *  This size value is hard-coded and is not stored in the NXS array.
 */
class RileyCrossSectionBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  #include "ACEtk/electron/RileyCrossSectionBlock/src/verifyRileyIndex.hpp"
  
public:

  /* constructor */
  #include "ACEtk/electron/RileyCrossSectionBlock/src/ctor.hpp"
  
  /* methods */
  
  /**
   *  @brief Return the number of Riley cross section parameter sets
   */
  static constexpr unsigned int NRLY() const { return 9; }
  
  /**
   *  @brief Return the number of Riley cross section parameter sets
   */
  static constexpr unsigned int numberEnergyPoints() const { return this->NRLY(); }
  
  /**
   *  @brief Return the length of a Riley cross section parameter set
   *
   *  This includes the energy value for the paremeter set, which is
   *  listed as the first parameter.
   */
  static constexpr unsigned int parameterSetLength() const { return 14; }
  
  /**
   *  @brief Return the energy of a Riley cross section parameter set
   *
   *  @param[in] index    the index (1 to 9, one-based)
   */
  auto energy( std::size_t index ) const {
    
    #ifndef NDEBUG
    verifyRileyIndex( index );
    #endif
    return this->dvalue(index, 1);
  }
  
  /**
   *  @brief Return 
   *
   *  @param[in] index    the index (1 to 9, one-based)
   */
  auto parameterSet( std::size_t index ) const {
    
    #ifndef NDEBUG
    verifyRileyIndex( index );
    #endif
    return this->darray(index);
  }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using RLY = RileyCrossSectionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
