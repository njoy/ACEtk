class BindingEnergy {
  const Table& table;

public:
  BindingEnergy( const Table& table ) : table( table ){}
    
  auto values() const {
    const auto length = this->table.data.NXS( 11 );
    const auto start  = this->table.data.JXS( 11 ) + length;
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( const auto entry )
				 { return entry * electronVolt; } );
  }
};
