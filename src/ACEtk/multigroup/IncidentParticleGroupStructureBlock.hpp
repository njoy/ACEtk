#ifndef NJOY_ACETK_MULTIGROUP_INCIDENTPARTICLEGROUPSTRUCTUREBLOCK
#define NJOY_ACETK_MULTIGROUP_INCIDENTPARTICLEGROUPSTRUCTUREBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup energy ERG block with the incident particle group structure
 *
 *  The IncidentParticleGroupStructureBlock class contains 2 arrays of the same length:
 *    - the mean energies of each group (in MeV)
 *    - the widths of each group (in MeV)
 *
 *  The size of each (the total number of energy groups) is stored in NXS(5).
 */
class IncidentParticleGroupStructureBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/multigroup/IncidentParticleGroupStructureBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int NGRP() const { return this->N(); }

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int numberEnergyGroups() const { return this->NGRP(); }

  /**
   *  @brief Return the centers of the energy groups in MeV
   */
  auto ECENT() const { return this->darray( 1 ); }

  /**
   *  @brief Return the centers of the energy groups in MeV
   */
  auto groupCenters() const { return this->ECENT(); }


  /**
   *  @brief Return the widths of the energy groups in MeV
   */
  auto EWID() const { return this->darray( 2 ); }

  /**
   *  @brief Return the widths of the energy groups in MeV
   */
  auto groupWidths() const { return this->EWID(); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ERG = IncidentParticleGroupStructureBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
