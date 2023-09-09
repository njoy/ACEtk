#ifndef NJOY_ACETK_PHOTOATOMICTABLE
#define NJOY_ACETK_PHOTOATOMICTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/PhotoatomicPrincipalCrossSectionBlock.hpp"
#include "ACEtk/block/IncoherentScatteringFunctionBlock.hpp"
#include "ACEtk/block/CoherentFormFactorBlock.hpp"
#include "ACEtk/block/PhotoatomicFluorescenceDataBlock.hpp"
#include "ACEtk/block/PhotoatomicHeatingNumbersBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronShellBlock.hpp"
#include "ACEtk/block/PhotoatomicComptonProfileBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronSubshellBlock.hpp"
#include "ACEtk/block/PhotoelectricCrossSectionBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronCrossSectionBlock.hpp"

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
  block::ESZG eszg_;
  block::JINC jinc_;
  block::JCOH jcoh_;
  std::optional< block::JFLO > jflo_;
  block::LHNM lhnm_;
  std::optional< block::EPS > eps_;
  std::optional< block::SWD > swd_;
  std::optional< block::SUBSH > subsh_;
  std::optional< block::SPHEL > sphel_;

  std::optional< block::ESZE > esze_;

  /* auxiliary functions */
  #include "ACEtk/PhotoatomicTable/src/generateBlocks.hpp"
  #include "ACEtk/PhotoatomicTable/src/generateData.hpp"
  #include "ACEtk/PhotoatomicTable/src/verifyType.hpp"

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
   *  @brief Return the EPR data format flag (0 for old format, 1 for EPR data
   *         from 2012 and 3 for EPR data from 2014)
   */
  unsigned int NEPR() const { return this->data().NXS(6); }

  /**
   *  @brief Return the EPR data format flag (0 for old format, 1 for EPR data
   *         from 2012 and 3 for EPR data from 2014)
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
  unsigned int numberElectronEnergies() const { return this->NE(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the principal cross section block
   */
  const block::ESZG& ESZG() const { return this->eszg_; }

  /**
   *  @brief Return the principal cross section block
   */
  const block::ESZG& principalCrossSectionBlock() const { return this->ESZG(); }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const block::JINC& JINC() const { return this->jinc_; }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const block::JINC& incoherentScatteringFunctionBlock() const {

    return this->JINC();
  }

  /**
   *  @brief Return the coherent form factor block
   */
  const block::JCOH& JCOH() const { return this->jcoh_; }

  /**
   *  @brief Return the coherent form factor block
   */
  const block::JCOH& coherentFormFactorBlock() const { return this->JCOH(); }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< block::JFLO >& JFLO() const { return this->jflo_; }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< block::JFLO >& fluorescenceDataBlock() const {

    return this->JFLO();
  }

  /**
   *  @brief Return the heating numbers block
   */
  const block::LHNM& LHNM() const { return this->lhnm_; }

  /**
   *  @brief Return the heating numbers block
   */
  const block::LHNM& heatingNumbersBlock() const { return this->LHNM(); }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< block::EPS >& EPS() const { return this->eps_; }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< block::EPS >& electronShellBlock() const {

    return this->EPS();
  }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< block::SWD >& SWD() const { return this->swd_; }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< block::SWD >& comptonProfileBlock() const {

    return this->SWD();
  }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< block::SUBSH >& SUBSH() const { return this->subsh_; }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< block::SUBSH >& electronSubshellBlock() const {

    return this->SUBSH();
  }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::SPHEL >& SPHEL() const { return this->sphel_; }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::SPHEL >& photoelectricCrossSectionBlock() const {

    return this->SPHEL();
  }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::ESZE >& ESZE() const { return this->esze_; }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::ESZE >& electronCrossSectionBlock() const {

    return this->ESZE();
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
