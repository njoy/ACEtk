class ESZG {
  std::reference_wrapper<const Table> table;  

public:

  ESZG( const Table& table ) : table( table ) {}

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
      | ranges::view::transform( []( auto&& entry ){ return exp(entry) * barn; } );
  }

  auto coherentScatteringXS() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 ) + 2*length;
    return this->table.get().data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry ){ return exp(entry) * barn; } );
  }

  auto photoelectricXS() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 ) + 3*length;
    return this->table.get().data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry ) { return exp(entry); } )
      | ranges::view::replace( 1.000000000000E+00, 0.000000000000E+00 )
      | ranges::view::transform( []( auto&& entry ) { return entry * barn; } );
  }

  auto pairProductionXS() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 ) + 4*length;
    return this->table.get().data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry ){ return exp(entry); } )
      | ranges::view::replace( 1.000000000000E+00, 0.000000000000E+00 )
      | ranges::view::transform( []( auto&& entry ) { return entry * barn; } );
  }
};
