class Bremsstrahlung {
  const Table& table;


public:
  Bremsstrahlung( const Table& table ) : table( table ) {}
  
  auto electronEnergy() const {
    const auto length = this->table.data.NXS( 5 );
    const auto start  = this->table.data.JXS( 5 );
    return this->table.data.XSS( start, length )
      | ranges::view::transform( [](auto&& entry )
				 { return entry * mega(electronVolt); } );
  }

  auto photonElectronEnergyRatio() const {
    const auto length = this->table.data.NXS( 6 );
    const auto start  = this->table.data.JXS( 5 ) + this->table.data.NXS( 5 );
    return this->table.data.XSS( start, length );
  }

  auto values() const {
    const auto length = this->table.data.NXS( 5 )*this->table.data.NXS( 6 );
    const auto start  = this->table.data.JXS( 5 ) + this->table.data.NXS( 5 )
                                                  + this->table.data.NXS( 6 );
    return this->table.data.XSS( start, length )
           | ranges::view::chunk( this->table.data.NXS( 5 ) );
  }

  auto photonElectronRatioValuesSpectrumCalculation() const {
    const auto length = this->table.data.NXS( 9 );
    const auto start  = this->table.data.JXS( 9 );
    return this->table.data.XSS( start, length );
  }

  auto photonElectronRatioValuesAngularDistribution() const {
    const auto length = this->table.data.NXS( 10 );
    const auto start  = this->table.data.JXS( 10 );
    return this->table.data.XSS( start, length );
  }
  
};
