struct Polynomial{

  std::vector< double > coefficients;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder.hpp"

  auto ACEify(){
    return ranges::view::concat( 
        ranges::view::single( 1 ), this->coefficients );
  }
};
