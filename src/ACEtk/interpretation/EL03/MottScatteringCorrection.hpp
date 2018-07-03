class MottScatteringCorrection {
  const Table& table;

  template<int N>
  auto h() const {
    const auto length = this->table.data.NXS( 4 ) ;
    const auto start  = this->table.data.JXS( 3 ) + N * length;
    return this->table.data.XSS( start, length ) | ranges::view::reverse;
  }
  
public:
  MottScatteringCorrection( const Table& table ) : table(table) {}

  auto energyGrid() const {
    const auto length = this->table.data.NXS( 4 );
    const auto start  = this->table.data.JXS( 3 );
    return
      this->table.data.XSS( start, length )
      | ranges::view::reverse
      | ranges::view::transform ( [] ( auto && entry )
				  { return entry * mega(electronVolt); } );
  }

  auto values() const {
    
      return ranges::view::zip( this->h<1>(),
				this->h<2>(),
				this->h<3>(),
				this->h<4>(),
				this->h<5>() );
  }
  
};
