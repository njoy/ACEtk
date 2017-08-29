class AtomicLevels {
  const Table& table;
  
  auto bindingEnergies() const {
    const auto length = this->table.data.NXS( 11 );
    const auto start  = this->table.data.JXS( 11 ) + length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( const auto entry )
				 { return entry * electronVolt; } );
  }

  auto occupationNumbers() const {
    const auto length = this->table.data.NXS( 11 );
    const auto start  = this->table.data.JXS( 11 );
    return this->table.data.XSS( start, length );
  }

  auto isLevelConductive() const {
    return this->occupationNumbers() |
      ranges::view::transform( []( const auto entry ) { return entry < 0; } );
  }  
  
public:
  AtomicLevels( const Table& table ) : table( table ) {}

  auto values() const {
    auto absEntry = []( const auto entry ){ return std::abs(entry); };
    return
      ranges::view::zip( this->occupationNumbers()
			 | ranges::view::transform( absEntry ), 
			 this->isLevelConductive(),
			 this->bindingEnergies() );
  }
    
};
