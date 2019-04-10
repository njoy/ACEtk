struct CrossSection{
  Table::Slice energyGrid;
  details::verify::Positive< std::vector< double > > values;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder.hpp"
  void ACEify( Table::Data& tData ){
    tData.XSS() |= ranges::action::push_back( values );
  }
};
