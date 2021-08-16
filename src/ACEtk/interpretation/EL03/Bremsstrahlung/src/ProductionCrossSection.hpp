class ProductionCrossSection{
  const Table& table;

public:
  ProductionCrossSection( const Table& table ) : table( table ) {}
  
  auto electron_energies() const {
    const auto length = this->table.data().NXS( 5 );
    const auto start  = this->table.data().JXS( 5 );
    return this->table.data().XSS( start, length )
      | ranges::view::transform( [](auto&& entry )
				 { return entry * mega(electronVolt); } );
  }

  auto photonElectronEnergyRatio() const {
    const auto length = this->table.data().NXS( 6 );
    const auto start  = this->table.data().JXS( 5 ) + this->table.data().NXS( 5 );
    return this->table.data().XSS( start, length );
  }

  auto values() const {
    const auto length = this->table.data().NXS( 5 ) * this->table.data().NXS( 6 );
    const auto start  = this->table.data().JXS( 5 ) + this->table.data().NXS( 5 )
                                                  + this->table.data().NXS( 6 );

    const auto units = [](auto&& entry) { return entry * centi(meter)
					  * centi(meter) / mega(electronVolt); };

    return this->table.data().XSS( start, length )
      | ranges::view::transform( units )
      | ranges::view::chunk( this->table.data().NXS( 5 ) );
  }
};
