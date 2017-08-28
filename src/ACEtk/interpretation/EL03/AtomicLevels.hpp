class AtomicLevels {
  const Table& table;
  bool conductor = false;
  
  auto bindingEnergie() const {
    const auto length = this->table.data.NXS( 11 );
    const auto start  = this->table.data.JXS( 11 ) + length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( const auto entry )
				 { return entry * electronVolt; } );
  }

  auto occupationNumber() const {
    const auto length = this->table.data.NXS( 11 );
    const auto start  = this->table.data.JXS( 11 );
    return this->table.data.XSS( start, length );
  }
  
public:
  AtomicLevels( const Table& table )
    : table( table ),
      conductor( ranges::view::any_of( this->occupationNumber(),
				       []( const auto entry ){ return entry < 0; } ) )
  {}

  bool isConductive(){ return conductor; }
      
  auto values() const {
    return ranges::view::zip( this->occupationNumber(),
			      this->bindingEnergy() );
  }
    
};
