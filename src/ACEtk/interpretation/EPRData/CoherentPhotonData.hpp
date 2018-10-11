class CoherentPhotonData {
  std::reference_wrapper<const Table> table;

public:
  CoherentPhotonData( const Table& table ) : table(table) {}

  auto energies() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 );
    return this->table.get().data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry) * mega(electronVolt); } );
  }

  auto coherentScatteringXS() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 ) + 2*length;
    return this->table.get().data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry ){ return exp(entry) * barn; } );
  }

  auto independentVariableForFormFactors() const {
    const auto length = ( this->table.get().data.JXS( 4 ) - this->table.get().data.JXS( 3 ) )/3;
    const auto start  = this->table.get().data.JXS( 3 );
    return this->table.get().data.XSS( start, length );
  }

  auto cumulativeFormFactors() const {
    const auto length = ( this->table.get().data.JXS( 4 ) - this->table.get().data.JXS( 3 ) )/3;
    const auto start  = this->table.get().data.JXS( 3 ) + length;
    return this->table.get().data.XSS( start, length );
  }

  auto differentialFormFactors() const {
    const auto length = ( this->table.get().data.JXS( 4 ) - this->table.get().data.JXS( 3 ) )/3;
    const auto start  = this->table.get().data.JXS( 3 ) + 2*length;
    return this->table.get().data.XSS( start, length );
  }
};
