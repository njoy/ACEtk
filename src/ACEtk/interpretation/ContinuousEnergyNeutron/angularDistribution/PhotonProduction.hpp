class PhotonProduction {

protected:
 Slice energyGrid_;
 Slice cosineBins_;


public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/angularDistribution/PhotonProduction/src/ctor.hpp"

 auto energyGrid() const{ return energyGrid_; }
 auto cosineBins() const{ 
   return cosineBins_
      | ranges::view::chunk( energyGrid_.size() );
 }

};
