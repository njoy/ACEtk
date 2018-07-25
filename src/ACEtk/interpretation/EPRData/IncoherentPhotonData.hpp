class IncoherentPhotonData {
  const Table& table;

public:
  IncoherentPhotonData( const Table& table ) : table(table) {}
  
  auto energyGrid() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 1 );
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry) * mega(electronVolt); } );
  }
  
  auto incoherentScatteringXS() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 1 ) + length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry) * barn; } );
  }

  auto independantVariableForFormFactor() const {
    const auto length = ( this->table.data.JXS( 3 ) - this->table.data.JXS( 2 ) )/2;
    const auto start  = this->table.data.JXS( 2 );
    return this->table.data.XSS( start, length );
  }
  
  auto incoherentFormFactor() const {
    const auto length = ( this->table.data.JXS( 3 ) - this->table.data.JXS( 2 ) )/2;
    const auto start  = this->table.data.JXS( 2 ) + length;
    return this->table.data.XSS( start, length );
  }


};
