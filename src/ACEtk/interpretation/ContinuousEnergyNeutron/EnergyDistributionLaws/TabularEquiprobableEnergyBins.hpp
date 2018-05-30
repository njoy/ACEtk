
class TabularEquiprobableEnergyBins {
  template< typename T >
  static auto make( T oEnergies, int NE, int NET ){
    return oEnergies 
        | ranges::view::chunk( NET )
        | ranges::view::take_exactly( NE );
  }
  using EOut_t = decltype(std::declval< Table::Slice >() 
                       | ranges::view::chunk(1)
                       | ranges::view::take_exactly(1) );

  ENDFInterpolationParameters interpolationParameters_;
  Table::Slice incidentEnergies_;
  EOut_t outgoingEnergyTables_;
  // ranges::iterator_range<double> outgoingEnergyTables_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/TabularEquiprobableEnergyBins/src/ctor.hpp"


  auto interpolationParameters() const { return interpolationParameters_; }
  auto incidentEnergies() const { return incidentEnergies_; }
  auto outgoingEnergyTables() const { return outgoingEnergyTables_; }
};

typedef TabularEquiprobableEnergyBins Law1;
