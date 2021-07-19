class AtomicLevels {
  const Table& table;

  auto rawOccupationNumbers() const {
    const auto length = this->table.data().NXS( 11 );
    const auto start  = this->table.data().JXS( 11 );
    return this->table.data().XSS( start, length );
  }

public:
  AtomicLevels( const Table& table ) : table( table ) {}

  auto occupationNumbers() const {
    return this->rawOccupationNumbers()
      | ranges::view::transform( []( const auto x )
				 { return std::abs(x); } );
  }

  auto isLevelConductive() const {
    return this->rawOccupationNumbers()
      | ranges::view::transform( []( const auto entry )
				 { return entry < 0; } );
  }

  auto bindingEnergies() const {
    const auto length = this->table.data().NXS( 11 );
    const auto start  = this->table.data().JXS( 11 ) + length;
    return this->table.data().XSS( start, length )
      | ranges::view::transform( []( const auto entry )
				 { return entry * electronVolt; } );
  }

  auto values() const {
    return ranges::view::zip( this->occupationNumbers(),
			      this->isLevelConductive(),
			      this->bindingEnergies() );
  }

};
