class GammaProduction {

protected:
  Slice crossSection_;
  Slice outgoingEnergyGrid_;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/GammaProduction/src/ctor.hpp"

  auto crossSection() const{ return crossSection_; }
  auto outgoingEnergyGrid() const{ 
    return outgoingEnergyGrid_
      | ranges::view::chunk( 20 ); 
  }
  // auto outgoingEnergyGrid( int index ) const{ 
  //   return outgoingEnergyGrid_ 
  //     | ranges::view::drop_exactly( 20*index )
  //     | ranges::view::take_exactly( 20 );
  // }

};
