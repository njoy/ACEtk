class Production {
  Slice electronEnergySlice;
  Slice energyRatioSlice;
  Slice crossSectionSlice;
    
public:
  Production( Slice electronEnergySlice,
	      Slice energyRatioSlice,
	      Slice crossSectionSlice ) :
    electronEnergySlice( electronEnergySlice ),
    energyRatioSlice( energyRatioSlice ),
    crossSectionSlice( crossSectionSlice ){}

  auto electronEnergies() const {
    return this->electronEnergySlice
      | range::view::transform( scaleBy( MeV ) );
  }

  auto photonEnergies() const {
    auto expand = [ energyRatioSlice ]( auto energy ){
      return energyRatioSlice | range::view::transform( scaleBy( energy ) );
    };
      
    return this->electronEnergies() | ranges::view::transform( expand );
  }

    
  auto crossSections() const {
    return this->crossSectionSlice
      | range::view::transform( scaleBy( cm * cm / MeV ) )
      | range::view::chunk( ranges::distance( this->energyRatioSlice ) );
  }
};
