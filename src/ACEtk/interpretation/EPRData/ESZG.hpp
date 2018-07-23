class ESZG {
  const Table& table;

public:

  ESZG( const Table& table ) : table( table ) {}

  auto photonEnergy() const {
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
				 { return exp (entry); } );
  }

  auto coherentScatteringXS() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 1 ) + 2*length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry); } );
  }

  auto totalPhotoelectricXS() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 1 ) + 3*length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry); } );
  }

  auto pairProductionXS() const {
    const auto length = this->table.data.NXS( 3 );
    const auto start  = this->table.data.JXS( 1 ) + 4*length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( auto&& entry )
				 { return exp (entry); } );
  }

};
