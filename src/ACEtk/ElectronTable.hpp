#ifndef NJOY_ACETK_ELECTRONTABLE
#define NJOY_ACETK_ELECTRONTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/electron/BremsstrahlungCorrectionFactorBlock.hpp"
#include "ACEtk/electron/BremsstrahlungHighFrequencyBlock.hpp"
#include "ACEtk/electron/BremsstrahlungProductionBlock.hpp"
#include "ACEtk/electron/MottScatteringCorrectionBlock.hpp"
#include "ACEtk/electron/OscillatorBlock.hpp"
#include "ACEtk/electron/RadiationStoppingPowerBlock.hpp"
#include "ACEtk/electron/RileyCrossSectionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The electron ACE table
 *
 *  The ElectronTable class represents the ACE table for the electron data.
 */
class ElectronTable : protected Table {
  
  /* fields */
  electron::RAD rad_;
  electron::MOT mot_;
  electron::RLY rly_;
  std::optional< electron::XSB > xsb_;
  std::optional< electron::CRB > crb_;
  std::optional< electron::HFB > hfb_;
  std::optional< electron::OSC > osc_;
  
  /* auxiliary functions */
  // generateBlocks
  // generateData
  // verifyType
  
public:

  // ctor
  
  using Table::header;
  using Table::data;
  using Table::print;
  
  /* functions */
  
};

} // ACEtk namespace
} // njoy namespace

#endif