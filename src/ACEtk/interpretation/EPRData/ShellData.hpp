class ShellData {
  const Table& table;
  
  auto dataPointers() const {
    const auto length = this->table.data.NXS( 5 );
    const auto start  = this->table.data.JXS( 9 );
    return this->table.data.XSS( start, length );
  }
  
public:
  ShellData( const Table& table ) : table(table) {}

  auto electronPopulations() const {
    const auto length = this->table.data.NXS( 5 );
    const auto start  = this->table.data.JXS( 6 );
    return this->table.data.XSS( start, length );
  }

  auto bindingEnergies() const {
    const auto length = this->table.data.NXS( 5 );
    const auto start  = this->table.data.JXS( 7 );
    return this->table.data.XSS( start, length )
      | ranges::view::transform( []( const auto entry )
				 { return entry * electronVolt; } );
  }
  
  auto probabilities() const {
    const auto length = this->table.data.NXS( 5 );
    const auto start  = this->table.data.JXS( 8 );
    return this->table.data.XSS( start, length );
  }
  
  auto shellValues() const {
    return ranges::view::zip( this->electronPopulations(),
			      this->bindingEnergies(),
			      this->probabilities() );
  }
  
  auto dopplerData() const {
    const auto numShell = this->table.data.NXS( 5 );
    const auto length = numShell*94;
    const auto start = this->table.data.JXS( 10 );
    return this->table.data.XSS( start, length )
      | ranges::view::chunk( 94 );
  }
};
