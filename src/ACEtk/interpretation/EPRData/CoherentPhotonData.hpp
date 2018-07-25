class CoherentPhotonData {
  const Table& table;

public:
  CoherentPhotonData( const Table& table ) : table(table) {}

  auto energyGrid() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 1 );
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry) * mega(electronVolt); } );
  }

  auto coherentScatteringXS() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 1 ) + 2*length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry ){ return exp(entry) * barn; } );
  }

  auto independentVariableForFormFactors() const {
    const auto length = ( this->table.data.JXS( 4 ) - this->table.data.JXS( 3 ) )/3;
    const auto start  = this->table.data.JXS( 3 );
    return this->table.data.XSS( start, length );
  }

  auto cumulativeFormFactors() const {
    const auto length = ( this->table.data.JXS( 4 ) - this->table.data.JXS( 3 ) )/3;
    const auto start  = this->table.data.JXS( 3 ) + length;
    return this->table.data.XSS( start, length );
  }

  auto differentialFormFactors() const {
    const auto length = ( this->table.data.JXS( 4 ) - this->table.data.JXS( 3 ) )/3;
    const auto start  = this->table.data.JXS( 3 ) + 2*length;
    return this->table.data.XSS( start, length );
  }
};
