class RileyCrossSections {
  const Table& table;

  auto data() const {
    constexpr int length = 126;
    const auto start  = this->table.data.JXS( 4 );
    return this->table.data.XSS( start, length );
  }
  
public:
  RileyCrossSections( const Table& table ) : table(table) {}

  auto energyGrid() const {
    constexpr int num_params = 14;
    constexpr int length = 126;
    const auto start  = this->table.data.JXS( 4 );
    return
      this->table.data.XSS( start, length )
      | ranges::view::stride( num_params )
      | ranges::view::reverse
      | ranges::view::transform ( [] ( auto && entry )
				  { return entry * mega(electronVolt); } );
  }

  auto values() const {
    constexpr int num_params = 14;
    return  this->data() | ranges::view::reverse
      | ranges::view::chunk( num_params )
      | ranges::view::transform( ranges::view::reverse )
      | ranges::view::transform( ranges::view::drop_exactly(1) );
  }

};
