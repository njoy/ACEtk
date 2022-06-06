#ifndef NJOY_ACETK_PHOTOATOMICTABLE
#define NJOY_ACETK_PHOTOATOMICTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/PhotoAtomicPrincipalCrossSectionBlock.hpp"
#include "ACEtk/block/IncoherentScatteringFunctionBlock.hpp"
#include "ACEtk/block/CoherentFormFactorBlock.hpp"
#include "ACEtk/block/PhotoAtomicHeatingNumbersBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The photoatomic ACE table
 *
 *  The PhotoAtomicTable class represents the ACE table for the photoatomic data.
 */
class PhotoAtomicTable : protected Table {

  /* fields */
  block::ESZG eszg_;
  block::JINC jinc_;
  block::JCOH jcoh_;
  block::LHNM lhnm_;

  /* auxiliary functions */
  #include "ACEtk/PhotoAtomicTable/src/generateBlocks.hpp"
  #include "ACEtk/PhotoAtomicTable/src/generateData.hpp"

public:

  #include "ACEtk/PhotoAtomicTable/src/ctor.hpp"

  using Table::header;
  using Table::data;
  using Table::print;

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const { return this->header().ZAID(); }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const { return this->header().AWR(); }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->header().atomicWeightRatio(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const { return this->header().TEMP(); }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->header().temperature(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const { return this->header().date(); }

  /**
   *  @brief Return the title
   */
  const std::string& title() const { return this->header().title(); }

  /**
   *  @brief Return the material
   */
  const std::string& material() const { return this->header().material(); }

  // NXS information

  /**
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS(1); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

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
  const block::JINC& incoherentScatteringFunctionBlock() const { return this->JINC(); }

  /**
   *  @brief Return the coherent form factor block
   */
  const block::JCOH& JCOH() const { return this->jcoh_; }

  /**
   *  @brief Return the coherent form factor block
   */
  const block::JCOH& coherentFormFactorBlock() const { return this->JCOH(); }

  /**
   *  @brief Return the heating numbers block
   */
  const block::LHNM& LHNM() const { return this->lhnm_; }

  /**
   *  @brief Return the heating numbers block
   */
  const block::LHNM& heatingNumbersBlock() const { return this->LHNM(); }
};

} // ACEtk namespace
} // njoy namespace

#endif
