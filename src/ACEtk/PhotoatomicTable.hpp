#ifndef NJOY_ACETK_PHOTOATOMICTABLE
#define NJOY_ACETK_PHOTOATOMICTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/photoatomic/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock.hpp"
#include "ACEtk/photoatomic/CoherentFormFactorBlock.hpp"
#include "ACEtk/photoatomic/FluorescenceDataBlock.hpp"
#include "ACEtk/photoatomic/HeatingNumbersBlock.hpp"
#include "ACEtk/photoatomic/ComptonProfileBlock.hpp"
#include "ACEtk/photoatomic/PhotoelectricCrossSectionBlock.hpp"
#include "ACEtk/electron/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/electron/ElasticCrossSectionBlock.hpp"
#include "ACEtk/electron/ElectronShellBlock.hpp"
#include "ACEtk/electron/ElectronSubshellBlock.hpp"
#include "ACEtk/electron/SubshellTransitionDataBlock.hpp"
#include "ACEtk/electron/ElasticAngularDistributionBlock.hpp"
#include "ACEtk/electron/EnergyDistributionBlock.hpp"
#include "ACEtk/electron/ExcitationBlock.hpp"
#include "ACEtk/electron/BremsstrahlungBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The photoatomic ACE table
 *
 *  The PhotoatomicTable class represents the ACE table for the photoatomic data.
 */
class PhotoatomicTable : protected Table {

  /* fields */
  photoatomic::ESZG eszg_;
  photoatomic::JINC jinc_;
  photoatomic::JCOH jcoh_;
  std::optional< photoatomic::JFLO > jflo_;
  photoatomic::LHNM lhnm_;
  std::optional< electron::EPS > eps_;
  std::optional< photoatomic::SWD > swd_;
  std::optional< electron::SUBSH > subsh_;
  std::optional< photoatomic::SPHEL > sphel_;
  std::optional< electron::XPROB > xprob_;
  std::optional< electron::ESZE > esze_;
  std::optional< electron::EXCIT > excit_;
  std::optional< electron::ELAS > elas_;
  std::vector< electron::EION > eion_;
  std::optional< electron::BREME > breme_;
  std::optional< electron::BREML > breml_;
  std::optional< electron::SELAS > selas_;

  /* auxiliary functions */
  #include "ACEtk/PhotoatomicTable/src/generateBlocks.hpp"
  #include "ACEtk/PhotoatomicTable/src/generateData.hpp"
  #include "ACEtk/PhotoatomicTable/src/verifyType.hpp"
  #include "ACEtk/PhotoatomicTable/src/verifySubshellIndex.hpp"

public:

  #include "ACEtk/PhotoatomicTable/src/ctor.hpp"

  using Table::header;
  using Table::data;
  using Table::print;

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.ZAID(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.AWR(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->AWR(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.TEMP(); },
                       this->header() );
  }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->TEMP(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.date(); },
                       this->header() );
  }

  // NXS information

  /**
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS(1); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int Z() const { return this->data().NXS(2); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int NFLO() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int numberFluorescenceEdges() const { return this->NFLO(); }

  /**
   *  @brief Return the number of electron shells (for Compton Doppler broadening)
   */
  unsigned int NSH() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of electron shells (for Compton Doppler broadening)
   */
  unsigned int numberElectronShells() const { return this->NSH(); }

  /**
   *  @brief Return the EPR data format flag (0 for the old mcplib format, 1 for
   *         EPR data from 2012 and 3 for EPR data from 2014 and above)
   */
  unsigned int NEPR() const { return this->data().NXS(6); }

  /**
   *  @brief Return the EPR data format flag (0 for the old mcplib format, 1 for
   *         EPR data from 2012 and 3 for EPR data from 2014 and above)
   */
  unsigned int electronPhotonRelaxationFormat() const { return this->NEPR(); }

  /**
   *  @brief Return the number of electron subshells (for photoelectric and electron
   *         impact ionization)
   */
  unsigned int NSSH() const { return this->data().NXS(7); }

  /**
   *  @brief Return the number of electron subshells (for photoelectric and electron
   *         impact ionization)
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int NE() const { return this->data().NXS(8); }

  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int numberElectronEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the number of electron excitation energy points
   */
  unsigned int NXL() const { return this->data().NXS(9); }

  /**
   *  @brief Return the number of electron excitation energy points
   */
  unsigned int numberElectronExcitationEnergyPoints() const {

    return this->NXL();
  }

  /**
   *  @brief Return the number of energy points with electron elastic angular
   *         distributions
   */
  unsigned int NA() const { return this->data().NXS(10); }

  /**
   *  @brief Return the number of energy points with electron elastic angular
   *         distributions
   */
  unsigned int numberElectronElasticEnergyPoints() const { return this->NA(); }

  /**
   *  @brief Return the number of energy points with Bremsstrahlung photon
   *         energy distributions
   */
  unsigned int NB() const { return this->data().NXS(11); }

  /**
  *  @brief Return the number of energy points with Bremsstrahlung photon
  *         energy distributions
   */
  unsigned int numberPhotonBremsstrahlungEnergyPoints() const {

    return this->NB();
  }

  /**
   *  @brief Return the number of electron Bremsstrahlung energy points
   */
  unsigned int NBL() const { return this->data().NXS(12); }

  /**
   *  @brief Return the number of electron Bremsstrahlung energy points
   */
  unsigned int numberElectronBremsstrahlungEnergyPoints() const {

    return this->NBL();
  }

  /**
   *  @brief Return the number of momentum values in the JINC block (NEPR > 1)
   */
  unsigned int NINC() const { return this->data().NXS(13); }

  /**
   *  @brief Return the number of momentum values in the JINC block (NEPR > 1)
   */
  unsigned int numberIncoherentMomentumValues() const { return this->NINC(); }

  /**
   *  @brief Return the number of momentum values in the JCOH block (NEPR > 1)
   */
  unsigned int NCOH() const { return this->data().NXS(14); }

  /**
   *  @brief Return the number of momentum values in the JCOH block (NEPR > 1)
   */
  unsigned int numberCoherentMomentumValues() const { return this->NCOH(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the principal cross section block
   */
  const photoatomic::ESZG& ESZG() const { return this->eszg_; }

  /**
   *  @brief Return the principal cross section block
   */
  const photoatomic::ESZG& principalCrossSectionBlock() const {

    return this->ESZG();
  }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const photoatomic::JINC& JINC() const { return this->jinc_; }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const photoatomic::JINC& incoherentScatteringFunctionBlock() const {

    return this->JINC();
  }

  /**
   *  @brief Return the coherent form factor block
   */
  const photoatomic::JCOH& JCOH() const { return this->jcoh_; }

  /**
   *  @brief Return the coherent form factor block
   */
  const photoatomic::JCOH& coherentFormFactorBlock() const {

    return this->JCOH();
  }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< photoatomic::JFLO >& JFLO() const { return this->jflo_; }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< photoatomic::JFLO >& fluorescenceDataBlock() const {

    return this->JFLO();
  }

  /**
   *  @brief Return the heating numbers block
   */
  const photoatomic::LHNM& LHNM() const { return this->lhnm_; }

  /**
   *  @brief Return the heating numbers block
   */
  const photoatomic::LHNM& heatingNumbersBlock() const { return this->LHNM(); }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< electron::EPS >& EPS() const { return this->eps_; }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< electron::EPS >& electronShellBlock() const {

    return this->EPS();
  }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< photoatomic::SWD >& SWD() const { return this->swd_; }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< photoatomic::SWD >& comptonProfileBlock() const {

    return this->SWD();
  }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< electron::SUBSH >& SUBSH() const { return this->subsh_; }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< electron::SUBSH >& electronSubshellBlock() const {

    return this->SUBSH();
  }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< photoatomic::SPHEL >& SPHEL() const {

    return this->sphel_;
  }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< photoatomic::SPHEL >& photoelectricCrossSectionBlock() const {

    return this->SPHEL();
  }

  /**
   *  @brief Return the subshell transition data block for eprdata (NEPR > 0)
   */
  const std::optional< electron::XPROB >& XPROB() const { return this->xprob_; }

  /**
   *  @brief Return the subshell transition data block for eprdata (NEPR > 0)
   */
  const std::optional< electron::XPROB >& subshellTransitionDataBlock() const {

    return this->XPROB();
  }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< electron::ESZE >& ESZE() const { return this->esze_; }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< electron::ESZE >& electronCrossSectionBlock() const {

    return this->ESZE();
  }

  /**
   *  @brief Return the electron excitation energy loss block for eprdata (NEPR > 0)
   */
  const std::optional< electron::EXCIT >& EXCIT() const { return this->excit_; }

  /**
   *  @brief Return the electron excitation energy loss block for eprdata (NEPR > 0)
   */
  const std::optional< electron::EXCIT >& electronExcitationEnergyLossBlock() const {

    return this->EXCIT();
  }

  /**
   *  @brief Return the electron elastic angular distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electron::ELAS >& ELAS() const { return this->elas_; }

  /**
   *  @brief Return the electron elastic angular distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electron::ELAS >& electronElasticAngularDistributionBlock() const {

    return this->ELAS();
  }

  /**
   *  @brief Return the knock-on electron energy distribution block for a subshell
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const electron::EION& EION( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifySubshellIndex( index );
    #endif
    return this->eion_[ index - 1 ];
  }

  /**
   *  @brief Return the knock-on electron energy distribution block for a subshell
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const electron::EION& electroionisationEnergyDistributionBlock( std::size_t index ) const {

    return this->EION( index );
  }

  /**
   *  @brief Return the Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electron::BREME >& BREME() const { return this->breme_; }

  /**
   *  @brief Return the Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electron::BREME >& bremsstrahlungEnergyDistributionBlock() const {

    return this->BREME();
  }

  /**
   *  @brief Return the electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
   */
  const std::optional< electron::BREML >& BREML() const { return this->breml_; }

  /**
   *  @brief Return the electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
   */
  const std::optional< electron::BREML >& electronEnergyAfterBremsstrahlungBlock() const {

    return this->BREML();
  }

  /**
   *  @brief Return the additional elastic cross section block for eprdata (NEPR = 3)
   */
  const std::optional< electron::SELAS >& SELAS() const { return this->selas_; }

  /**
   *  @brief Return the additional elastic cross section block for eprdata (NEPR = 3)
   */
  const std::optional< electron::SELAS >& electronElasticCrossSectionBlock() const {

    return this->SELAS();
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
