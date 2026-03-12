#ifndef NJOY_ACETK_MULTIGROUP_EDITCROSSSECTIONBLOCK
#define NJOY_ACETK_MULTIGROUP_EDITCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief Edit Cross Section Block
 *
 *  The EditCrossSectionBlock class contains the edit cross section values
 *  in the XSED block. The number of edit reactions is in NXS(4) and the
 *  number of groups is NXS(5). The order of the edit cross sections is the
 *  same as the order of the edit reaction numbers in the MTED block.
 *  
 */
class EditCrossSectionBlock : protected base::ColumnData {

  /* auxiliary functions */
  // #include "ACEtk/multigroup/EditCrossSectionBlock/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/multigroup/EditCrossSectionBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of energy groups
   */
  std::size_t NGRP() const { return this->N(); }

  /**
   *  @brief Return the number of energy groups
   */
  std::size_t numberEnergyGroups() const { return this->NGRP(); }

  /**
   *  @brief Return the number of edit reactions
   */
  std::size_t NEDIT() const { return this->NC(); }

  /**
   *  @brief Return the number of edit reactions
   */
  std::size_t numberEditReactions() const { return this->NEDIT(); }

  /**
   *  @brief Return the cross section at a specific index
   *
   *  @param[in] index     the edit reaction index (one-based)
   */
  auto XS( unsigned int index ) const { return this->column( index ); }

  /**
   *  @brief Return the cross section at a specific index
   *
   *  @param[in] index     the edit reaction index (one-based)
   */
  auto editCrossSection( unsigned int index ) const { return this->XS( index ); }


  using Base::empty;
  using ColumnData::name;
  using ColumnData::length;
  using ColumnData::XSS;
  using ColumnData::begin;
  using ColumnData::end;

};

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif