#ifndef NJOY_ACETK_THERMALSCATTERINGTABLE
#define NJOY_ACETK_THERMALSCATTERINGTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/thermal/CrossSectionBlock.hpp"
#include "ACEtk/thermal/InelasticAngularDistributionBlock.hpp"
#include "ACEtk/thermal/ElasticAngularDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The thermal scattering ACE table
 *
 *  The ThermalScatteringTable class represents the ACE table for the thermal
 *  scattering data.
 */
class ThermalScatteringTable : protected Table {

  /* fields */
  block::ITIE itie_;
  block::ITXE itxe_;
  std::optional< block::ITCE > itce_;
  std::optional< block::ITCA > itca_;
  std::optional< block::ITCEI> itcei_;
  std::optional< block::ITCAI> itcai_;

  /* auxiliary functions */
  #include "ACEtk/ThermalScatteringTable/src/generateBlocks.hpp"
  #include "ACEtk/ThermalScatteringTable/src/generateData.hpp"
  #include "ACEtk/ThermalScatteringTable/src/verifyType.hpp"

public:

  #include "ACEtk/ThermalScatteringTable/src/ctor.hpp"

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
   *  @brief Return the inelastic scattering mode
   */
  unsigned int IDPNI() const { return this->data().NXS(2); }

  /**
   *  @brief Return the inelastic scattering mode
   */
  unsigned int inelasticScatteringMode() const { return this->IDPNI(); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   *
   *  For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
   *  for IFENG = 2 this will be equal to NC + 1
   */
  unsigned int NIL() const { return this->data().NXS(3); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   *
   *  For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
   *  for IFENG = 2 this will be equal to NC + 1
   */
  unsigned int inelasticDimensioningParameter() const { return this->NIL(); }

  /**
   *  @brief Return the number of inelastic outgoing energies
   */
  unsigned int NIEB() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of inelastic outgoing energies
   */
  unsigned int numberInelasticOutgoingEnergies() const { return this->NIEB(); }

  /**
   *  @brief Return the elastic scattering mode
   */
  unsigned int IDPNC() const { return this->data().NXS(5); }

  /**
   *  @brief Return the elastic scattering mode
   */
  unsigned int elasticScatteringMode() const { return this->IDPNC(); }

  /**
   *  @brief Return the first elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int NCL() const { return this->data().NXS(6); }

  /**
   *  @brief Return the first elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int firstElasticDimensioningParameter() const { return this->NCL(); }

  /**
   *  @brief Return the second elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int NCLI() const { return this->data().NXS(8); }

  /**
   *  @brief Return the second elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int secondElasticDimensioningParameter() const { return this->NCLI(); }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int IFENG() const { return this->data().NXS(7); }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int secondaryEnergyMode() const { return this->IFENG(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the inelastic thermal scattering cross section block
   */
  const block::ITIE& ITIE() const { return this->itie_; }

  /**
   *  @brief Return the inelastic thermal scattering cross section block
   */
  const block::ITIE& inelasticCrossSectionBlock() const {

    return this->ITIE();
  }

  /**
   *  @brief Return the inelastic thermal scattering angular distribution block
   */
  const block::ITXE& ITXE() const { return this->itxe_; }

  /**
   *  @brief Return the inelastic thermal scattering angular distribution block
   */
  const block::ITXE& inelasticAngularDistributionBlock() const {

    return this->ITXE();
  }

  /**
   *  @brief Return the coherent elastic thermal scattering cross section block
   */
  const std::optional< block::ITCE >& ITCE() const { return this->itce_; }

  /**
   *  @brief Return the coherent elastic thermal scattering cross section block
   */
  const std::optional< block::ITCE >& coherentElasticCrossSectionBlock() const {

    return this->ITCE();
  }

  /**
   *  @brief Return the coherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< block::ITCA >& ITCA() const { return this->itca_; }

  /**
   *  @brief Return the coherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< block::ITCA >& coherentElasticAngularDistributionBlock() const {

    return this->ITCA();
  }

  /**
   *  @brief Return the incoherent elastic thermal scattering cross section block
   */
  const std::optional< block::ITCEI >& ITCEI() const { return this->itcei_; }

  /**
   *  @brief Return the incoherent elastic thermal scattering cross section block
   */
  const std::optional< block::ITCEI >& incoherentElasticCrossSectionBlock() const {

    return this->ITCEI();
  }

  /**
   *  @brief Return the incoherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< block::ITCAI >& ITCAI() const { return this->itcai_; }

  /**
   *  @brief Return the incoherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< block::ITCAI >& incoherentElasticAngularDistributionBlock() const {

    return this->ITCAI();
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
