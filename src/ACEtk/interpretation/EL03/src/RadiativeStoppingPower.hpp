class RadiativeStoppingPower {
  const Table& table;

  auto normalizedRadiativeStoppingPower() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 2 ) + length;
    return this->table.data.XSS( start, length ) | ranges::view::reverse;
  }
  
  auto electronElectronBremsstrahlungCorrection() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 2 ) + 2 * length;
    return this->table.data.XSS( start, length ) | ranges::view::reverse;
  }
  
public:
  RadiativeStoppingPower( const Table& table ) : table( table ){}
    
  auto energyGrid() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 2 );
    return
      this->table.data.XSS( start, length )
      | ranges::view::reverse
      | ranges::view::transform( []( auto&& entry )
                                 { return entry * mega(electronVolt); } );
  }

  auto values() const {
    constexpr Quantity< Mega<ElectronVolt> >
      massEquivalent = constant::electronMass
                       * constant::lightSpeed
                       * constant::lightSpeed;
    
    auto totalEnergy =
      this->energyGrid()
      | ranges::view::transform( [ massEquivalent ]( auto&& entry )
				 { return entry + massEquivalent; } );

    constexpr auto multiplier = constant::classicalElectronRadius
                                * constant::classicalElectronRadius
                                * constant::fineStructure;

    auto correctedBetheHeitler =
      [ m = multiplier, z = Z( this->table ) ]
      ( auto&& correction, auto&& normalized, auto&& totalEnergy )
      { return m * z * normalized * totalEnergy * ( z + correction ); };

    return
      ranges::view::zip_with( correctedBetheHeitler,
                              this->electronElectronBremsstrahlungCorrection(),
                              this->normalizedRadiativeStoppingPower(),
                              totalEnergy );
  }
};
