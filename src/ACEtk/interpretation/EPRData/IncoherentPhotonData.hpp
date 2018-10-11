class IncoherentPhotonData {
  std::reference_wrapper<const Table> table;

public:
  IncoherentPhotonData( const Table& table ) : table(table) {}
  
  auto energies() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 );
    return this->table.get().data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry) * mega(electronVolt); } );
  }
  
  auto incoherentScatteringXS() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 ) + length;
    return this->table.get().data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry) * barn; } );
  }

  auto independantVariableForFormFactor() const {
    const auto length = ( this->table.get().data.JXS( 3 ) - this->table.get().data.JXS( 2 ) )/2;
    const auto start  = this->table.get().data.JXS( 2 );
    return this->table.get().data.XSS( start, length );
  }
  
  auto incoherentFormFactor() const {
    const auto length = ( this->table.get().data.JXS( 3 ) - this->table.get().data.JXS( 2 ) )/2;
    const auto start  = this->table.get().data.JXS( 2 ) + length;
    return this->table.get().data.XSS( start, length );
  }


};
